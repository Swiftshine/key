#include "gflChecksum.h"

u32 gfl::GetChecksum(const char* str) {
    if (!str) {
        return 0;
    }

    u32 result = 0;

    while (*str) {
        result = *str + result * 137;
        str++;
    }

    return result;
}
