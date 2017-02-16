#ifndef UTILITIES_H
#define UTILITIES_H

#include <fstream>

/**
 * @brief swaps the endianness of the given input
 * @param var
 * @param numBytes
 * @pre   numBytes must be an even number
 */
void swapEndianness(uint32_t *var, std::streamsize numBytes);

/**
 * @brief checks if the architecture is big endian
 */
int is_big_endian();

/**
 * @brief reads a file with endianness swapping taken into account
 * @param file
 * @param var
 * @param numBytes
 * @param swap
 */
void readEndian(std::ifstream &file, char *var, std::streamsize numBytes, bool swap);

#endif // UTILITIES_H
