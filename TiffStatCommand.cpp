#include <fstream>
#include <iostream>
#include "TiffStatCommand.h"
#include "Utilities.h"

TiffStatCommand::TiffStatCommand(std::string& file): name("tiffstat"), filename(file) {
    for (size_t i = 0; i < 33433; i++) {
        tagnames[i] = "";
    }
    tagnames[254] = "NewSubfileType";
    tagnames[255] = "SubfileType";
    tagnames[256] = "ImageWidth";
    tagnames[257] = "ImageLength";
    tagnames[258] = "BitsPerSample";
    tagnames[259] = "Compression";
    tagnames[262] = "PhotometricInterpretation";
    tagnames[263] = "Threshholding";
    tagnames[264] = "CellWidth";
    tagnames[265] = "CellLength";
    tagnames[266] = "FillOrder";
    tagnames[269] = "DocumentName";
    tagnames[270] = "ImageDescription";
    tagnames[271] = "Make";
    tagnames[272] = "Model";
    tagnames[273] = "StripOffsets";
    tagnames[274] = "Orientation";
    tagnames[277] = "SamplesPerPixel";
    tagnames[278] = "RowsPerStrip";
    tagnames[279] = "StripByteCounts";
    tagnames[280] = "MinSampleValue";
    tagnames[281] = "MaxSampleValue";
    tagnames[282] = "XResolution";
    tagnames[283] = "YResolution";
    tagnames[284] = "PlanarConfiguration";
    tagnames[285] = "PageName";
    tagnames[286] = "XPosition";
    tagnames[287] = "YPosition";
    tagnames[288] = "FreeOffsets";
    tagnames[289] = "FreeByteCounts";
    tagnames[290] = "GrayResponseUnit";
    tagnames[291] = "GrayResponseCurve";
    tagnames[292] = "T4Options";
    tagnames[293] = "T6Options";
    tagnames[296] = "ResolutionUnit";
    tagnames[297] = "PageNumber";
    tagnames[301] = "TransferFunction";
    tagnames[305] = "Software";
    tagnames[306] = "DateTime";
    tagnames[315] = "Artist";
    tagnames[316] = "HostComputer";
    tagnames[317] = "Predictor";
    tagnames[318] = "WhitePoint";
    tagnames[319] = "PrimaryChromaticities";
    tagnames[320] = "ColorMap";
    tagnames[321] = "HalftoneHints";
    tagnames[322] = "TileWidth";
    tagnames[323] = "TileLength";
    tagnames[324] = "TileOffsets";
    tagnames[325] = "TileByteCounts";
    tagnames[332] = "InkSet";
    tagnames[333] = "InkNames";
    tagnames[334] = "NumberOfInks";
    tagnames[336] = "DotRange";
    tagnames[337] = "TargetPrinter";
    tagnames[338] = "ExtraSamples";
    tagnames[339] = "SampleFormat";
    tagnames[340] = "SMinSampleValue";
    tagnames[341] = "SMaxSampleValue";
    tagnames[342] = "TransferRange";
    tagnames[512] = "JPEGProc";
    tagnames[513] = "JPEGInterchangeFormat";
    tagnames[514] = "JPEGInterchangeFormatLngth";
    tagnames[515] = "JPEGRestartInterval";
    tagnames[517] = "JPEGLosslessPredictors";
    tagnames[518] = "JPEGPointTransforms";
    tagnames[519] = "JPEGQTables";
    tagnames[520] = "JPEGDCTables";
    tagnames[521] = "JPEGACTables";
    tagnames[529] = "YCbCrCoefficients";
    tagnames[530] = "YCbCrSubSampling";
    tagnames[531] = "YCbCrPositioning";
    tagnames[532] = "ReferenceBlackWhite";
    tagnames[33432] = "Copyright";
}


void TiffStatCommand::execute() {
    std::cout << toString() << ":" << std::endl;
    std::ifstream imfile;
    imfile.open (filename, std::ios::binary );
    if (imfile.is_open()) {
        try {
            bool swap = false;
            bool isBigEndian = false;

            uint16_t endianness; // 2 byte quantity
            uint16_t magicno; // 2 byte quantity
            uint32_t ifdaddress; // 4 byte quantity
            uint16_t ifdcount; // 2 byte quantity

            imfile.seekg (0, std::ios::beg); //not strictly necessary, but a good idea

            // match endianness
            imfile.read ((char *)&endianness, 2);
            if (endianness == 0x4d4d) {
                isBigEndian = true;
            } else if (endianness != 0x4949) {
                std::cout << "Error: Invalid TIFF format - cannot determine endianness" << std::endl;
                imfile.close();
                return;
            }
            if (isBigEndian != is_big_endian()) {
                swap = true;
            }

            std::cout << "Endian: 0x" << std:: hex << endianness << "\n";

            readEndian(imfile, (char *)&magicno, 2, swap);
            if (magicno != 42) {
                std::cout << "Error: Not a TIFF file, magic number incorrect" << std::endl;
                imfile.close();
                return;
            }

            std::cout << "Magic: " << std::dec << magicno << "\n";

            readEndian(imfile, (char *)&ifdaddress, 4, swap);

            std::cout << "Directory 0: offset 0x" << std::hex << ifdaddress << " next 0" << std::endl;

            // go to IFD position
            imfile.seekg(ifdaddress, std::ios::beg);
            readEndian(imfile, (char *)&ifdcount, 2, swap);

            for (uint16_t i = 0; i < ifdcount; i++) {
                uint16_t tag;
                uint16_t type;
                uint32_t count;
                readEndian(imfile, (char *)&tag, 2, swap);

                if (tag > 33432 || tagnames[tag] == "") {
                    std::cout << "CustomTag (" << std::hex << tag << ") ";
                }

                std::cout << tagnames[tag] << " (" << std::dec << tag << ") ";

                readEndian(imfile, (char *)&type, 2, swap);
                readEndian(imfile, (char *)&count, 4, swap);

                if ((type < 3 && count < 5) || (type == 3 && count < 3) || (type == 4 && count == 1)) { // values fit in the offset slot
                    if (type == 1) {
                        std::cout << "BYTE (1) " << count << "< ";
                        uint8_t value;
                        for (uint32_t j = 0; j < count; j++) {
                            readEndian(imfile, (char *)&value, 1, swap);
                            std::cout << value << " ";
                        }
                        std::cout << ">" << std::endl;
                        uint32_t junk;
                        readEndian(imfile, (char *)&junk, 4 - count, swap);
                    } else if (type == 2) {
                        std::cout << "ASCII (2) " << count << "< ";
                        char values[4];
                        readEndian(imfile, values, count, swap);
                        std::cout << values << " >" << std::endl;
                        uint32_t junk;
                        readEndian(imfile, (char *)&junk, 4 - count, swap);
                    } else if (type == 3) {
                        std::cout << "SHORT (3) " << count << "< ";
                        uint16_t value;
                        for (uint32_t j = 0; j < count; j++) {
                            readEndian(imfile, (char *)&value, 2, swap);
                            std::cout << value << " ";
                        }
                        std::cout << ">" << std::endl;
                        uint32_t junk;
                        readEndian(imfile, (char *)&junk, 4 - 2*count, swap);
                    } else if (type == 4) {
                        uint32_t value;
                        readEndian(imfile, (char *)&value, 4, swap);
                        std::cout << "LONG (4) 1< " << value << " >" << std::endl;
                    }
                } else {    // values don't fit in the offset slot
                    uint32_t offset;
                    readEndian(imfile, (char *)&offset, 4, swap);
                    std::streampos prevPos = imfile.tellg();
                    imfile.seekg(offset, std::ios::beg);
                    if (type == 1) {
                        std::cout << "BYTE (1) " << count << "< ";
                        uint8_t value;
                        for (uint32_t j = 0; j < count; j++) {
                            readEndian(imfile, (char *)&value, 1, swap);
                            std::cout << value << " ";
                        }
                        std::cout << ">" << std::endl;
                    } else if (type == 2) {
                        std::cout << "ASCII (2) " << count << "< ";
                        char *values = new char[count];
                        readEndian(imfile, values, count, swap);
                        std::cout << values << " >" << std::endl;
                        delete[] values;
                    } else if (type == 3) {
                        std::cout << "SHORT (3) " << count << "< ";
                        uint16_t value;
                        for (uint32_t j = 0; j < count; j++) {
                            readEndian(imfile, (char *)&value, 2, swap);
                            std::cout << value << " ";
                        }
                        std::cout << ">" << std::endl;
                    } else if (type == 4) {
                        std::cout << "LONG (4) " << count << "< ";
                        uint32_t value;
                        for (uint32_t j = 0; j < count; j++) {
                            readEndian(imfile, (char *)&value, 4, swap);
                            std::cout << value << " ";
                        }
                        std::cout << ">" << std::endl;
                    } else if (type == 5) {
                        std::cout << "RATIONAL (5) " << count << "< ";
                        uint32_t numer;
                        uint32_t denom;
                        for (uint32_t j = 0; j < count; j++) {
                            readEndian(imfile, (char *)&numer, 4, swap);
                            readEndian(imfile, (char *)&denom, 4, swap);
                            std::cout << numer/denom << " ";
                        }
                        std::cout << ">" << std::endl;
                    }
                    imfile.seekg(prevPos, std::ios::beg);
                }

            }
            imfile.close();
        } catch (std::exception ex) {
            imfile.close();
            std::cout << "Error: unable to read file as TIFF format" << std::endl;
        }
    } else {
        std::cout << "Error: invalid file name \"" << filename << "\"" << std::endl;
    }
}

std::string TiffStatCommand::toString() const {
    return name + " \"" + filename + "\"";
}




