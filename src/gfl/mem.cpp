#include <gfl/mem.h>

char* gfl::mem::memcpy(char* dst, u32 len, char* src) {
    if (!len) {
        return dst;
    }

    memset(dst, '\0', len);
    if (dst && src) {
        for (u32 count = 0; count < len - 1 && (*src); count++) {
            *dst = *src;
            dst++;
            src++;
        }
    }
    return dst;
}