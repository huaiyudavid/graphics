

#include <algorithm>

#include "Utilities.h"

void swapEndianness(uint32_t *var, std::streamsize numBytes) {
    unsigned char *tmp = (unsigned char *)var;
    for (std::streamsize i = 0; i < numBytes/2; i++) {
        std::swap(tmp[i], tmp[numBytes - 1 - i]);
    }
}

int is_big_endian()
{
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1;
}

void readEndian(std::ifstream &file, char *var, std::streamsize numBytes, bool swap) {
    file.read(var, numBytes);
    if (swap) {
        swapEndianness((uint32_t *)var, numBytes);
    }
}
