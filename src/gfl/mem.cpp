#include <gfl/mem.h>

char* gfl::mem::memcpy(char* dst, u32 len, char* src) {
    if (!len) {
        return dst;
    }

    memset(dst, '\0', len);
    if (dst && src) {
        for (int i = 0; i < len - 1 && src[i]; i++) {
            dst[i] = src[i];
        }
    }
    return dst;
}
