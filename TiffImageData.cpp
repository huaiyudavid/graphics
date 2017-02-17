
#include "TiffImageData.h"

TiffImageData::TiffImageData(): imageWidth(0), imageLength(0), bitsPerSample{0, 0, 0}, compression(0),
                 photometric(0), stripOffsets(nullptr), numStrips(0), samplesPerPixel(0), rowsPerStrip(0),
                 stripByteCounts(nullptr), xResNumer(0), xResDenom(0), yResNumer(0), yResDenom(0),
                 resolutionUnit(0) {}

TiffImageData::~TiffImageData() {
    delete[] stripOffsets;
    delete[] stripByteCounts;
}

void TiffImageData::setStripOffsets(uint32_t values[]) {
    delete[] stripOffsets;
    stripOffsets = values;
}

void TiffImageData::setStripByteCounts(uint32_t values[]) {
    delete[] stripByteCounts;
    stripByteCounts = values;
}


