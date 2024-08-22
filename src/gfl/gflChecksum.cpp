#include "gflChecksum.h"

uint gfl::GetChecksum(const char* str) {
    if (!str) {
        return 0;
    }

    uint result = 0;

    while (*str) {
        result = *str + result * 137;
        str++;
    }

    return result;
}