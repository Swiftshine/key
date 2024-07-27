#include <gfl/mem/MemoryBase.h>

using namespace gfl;

void MemoryBase::Reset() {
    heaps[0] = NULL;
    heaps[1] = NULL;
    heaps[2] = NULL;
    heaps[3] = NULL;
    heaps[4] = NULL;
    heaps[5] = NULL;
    heaps[6] = NULL;
    heaps[7] = NULL;
    heaps[8] = NULL;
    heaps[9] = NULL;
    heaps[0xA] = NULL;
    heaps[0xB] = NULL;
    heaps[0xC] = NULL;
    heaps[0xD] = NULL;
    heaps[0xE] = NULL;
    heaps[0xF] = NULL;
    heaps[0x10] = NULL;
    heaps[0x11] = NULL;
    heaps[0x12] = NULL;
    heaps[0x13] = NULL;
    heaps[0x14] = NULL;
    heaps[0x15] = NULL;
    heaps[0x16] = NULL;
    heaps[0x17] = NULL;
}

void MemoryBase::ReplaceHeap(Heap* other) {
    heaps[other->heapID] = other;
}

Heap* MemoryBase::GetHeapByAddress(void* address) {
    for (u32 i = 0; i < HEAP_COUNT; i++) {
        if (heaps[i] && heaps[i]->WithinRange(address)) {
            return heaps[i];
        }
    }
    
    return NULL;
}

u8 MemoryBase::GetHeapIDByAddress(void* address) {
    for (u32 i = 0; i < HEAP_COUNT; i++) {
        if (heaps[i] && heaps[i]->WithinRange(address)) {
            return i & 0xFF;
        }
    }

    return 0;
}

void MemoryBase::Free(void* address) {
    Heap* heap = FindContainingHeap(heaps, address);
    if (heap) {
        heap->Free(address);
    }
}


Heap* MemoryBase::GetHeapByID(u32 heapID) {
    return heaps[heapID & 0xFF];
}
