#ifndef GFL_CHECKSUM_H
#define GFL_CHECKSUM_H

#include "types.h"

namespace gfl {
    u32 GetChecksum(const char* str);

    inline u32 Checksum(const char* str) {
        u32 result = 0;

        char c = *str;
        while (0 != *str) {
            result = *str + result * 137;
            str++;
        }

        return result;
    }
}
#endif
