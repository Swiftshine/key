#include "gflAlloc.h"

void* operator new(size_t size) {
    return gfl::Alloc(gfl::HeapID::ETC, size, 4);
}

void* operator new(size_t size, u8 heapID) {
    return gfl::Alloc(heapID, size, 4);
}

void operator delete(void* ptr) {
    if (nullptr == ptr) {
        return;
    }

    gfl::Free(ptr);
}