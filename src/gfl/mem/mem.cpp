#include <gfl/mem/mem.h>

void* operator new(size_t size) {
    return gfl::mem::Alloc(gfl::mem::HeapID::Etc, size, 4);
}

void* operator new (size_t size, u8 heapID) {
    return gfl::mem::Alloc(heapID, size, 4);
}


char* gfl::mem::Memcpy(char* dst, u32 len, char* src) {
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
