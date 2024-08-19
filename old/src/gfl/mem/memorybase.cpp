#include <gfl/mem/MemoryBase.h>

using namespace gfl;

void MemoryBase::Reset() {
    mpHeaps[0] = NULL;
    mpHeaps[1] = NULL;
    mpHeaps[2] = NULL;
    mpHeaps[3] = NULL;
    mpHeaps[4] = NULL;
    mpHeaps[5] = NULL;
    mpHeaps[6] = NULL;
    mpHeaps[7] = NULL;
    mpHeaps[8] = NULL;
    mpHeaps[9] = NULL;
    mpHeaps[0xA] = NULL;
    mpHeaps[0xB] = NULL;
    mpHeaps[0xC] = NULL;
    mpHeaps[0xD] = NULL;
    mpHeaps[0xE] = NULL;
    mpHeaps[0xF] = NULL;
    mpHeaps[0x10] = NULL;
    mpHeaps[0x11] = NULL;
    mpHeaps[0x12] = NULL;
    mpHeaps[0x13] = NULL;
    mpHeaps[0x14] = NULL;
    mpHeaps[0x15] = NULL;
    mpHeaps[0x16] = NULL;
    mpHeaps[0x17] = NULL;
}

void MemoryBase::ReplaceHeap(Heap* other) {
    mpHeaps[other->mHeapID] = other;
}

Heap* MemoryBase::GetHeapByAddress(void* address) {
    for (u32 i = 0; i < HEAP_COUNT; i++) {
        if (mpHeaps[i] && mpHeaps[i]->WithinRange(address)) {
            return mpHeaps[i];
        }
    }
    
    return NULL;
}

u8 MemoryBase::GetHeapIDByAddress(void* address) {
    for (u32 i = 0; i < HEAP_COUNT; i++) {
        if (mpHeaps[i] && mpHeaps[i]->WithinRange(address)) {
            return i & 0xFF;
        }
    }

    return 0;
}

void MemoryBase::Free(void* address) {
    Heap* heap = FindContainingHeap(mpHeaps, address);
    if (heap) {
        heap->Free(address);
    }
}


Heap* MemoryBase::GetHeapByID(u32 heapID) {
    return mpHeaps[heapID & 0xFF];
}
