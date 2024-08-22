#ifndef GFL_CHECKSUM_H
#define GFL_CHECKSUM_H

#include "types.h"

namespace gfl {
    uint GetChecksum(const char* str);

    inline uint Checksum(const char* str) {
        uint result = 0;

        char c = *str;
        while (0 != *str) {
            result = *str + result * 137;
            str++;
        }

        return result;
    }
}
#endif