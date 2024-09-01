#include "gflMemoryUtil.h"

void* gfl::Memcpy(void* dst, size_t len, void* src) {
    if (0 == len) {
        return dst;
    }

    memset(dst, 0, len);

    if (nullptr != dst && nullptr != src) {
        for (size_t i = 0; i < len - 1 && 0 != ((u8*)src)[i]; i++) {
            ((u8*)dst)[i] = ((u8*)src)[i];
        }
    }

    return dst;
}
