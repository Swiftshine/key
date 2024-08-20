#include "gflMemoryBase.h"

using namespace gfl;

void MemoryBase::Reset() {
    mHeaps[0] = NULL;
    mHeaps[1] = NULL;
    mHeaps[2] = NULL;
    mHeaps[3] = NULL;
    mHeaps[4] = NULL;
    mHeaps[5] = NULL;
    mHeaps[6] = NULL;
    mHeaps[7] = NULL;
    mHeaps[8] = NULL;
    mHeaps[9] = NULL;
    mHeaps[0xA] = NULL;
    mHeaps[0xB] = NULL;
    mHeaps[0xC] = NULL;
    mHeaps[0xD] = NULL;
    mHeaps[0xE] = NULL;
    mHeaps[0xF] = NULL;
    mHeaps[0x10] = NULL;
    mHeaps[0x11] = NULL;
    mHeaps[0x12] = NULL;
    mHeaps[0x13] = NULL;
    mHeaps[0x14] = NULL;
    mHeaps[0x15] = NULL;
    mHeaps[0x16] = NULL;
    mHeaps[0x17] = NULL;
}

void MemoryBase::ReplaceHeap(Heap* other) {
    mHeaps[other->mHeapID] = other;
}

Heap* MemoryBase::GetHeapByAddress(void* address) {
    for (uint i = 0; i < GFL_MEMORYBASE_HEAP_COUNT; i++) {
        if (mHeaps[i] && mHeaps[i]->WithinRange(address)) {
            return mHeaps[i];
        }
    }
    
    return NULL;
}

u8 MemoryBase::GetHeapIDByAddress(void* address) {
    for (uint i = 0; i < GFL_MEMORYBASE_HEAP_COUNT; i++) {
        if (mHeaps[i] && mHeaps[i]->WithinRange(address)) {
            return i & 0xFF;
        }
    }

    return 0;
}

void MemoryBase::Free(void* address) {
    Heap* heap = FindContainingHeap(mHeaps, address);
    if (heap) {
        heap->Free(address);
    }
}


Heap* MemoryBase::GetHeapByID(uint heapID) {
    return mHeaps[heapID & 0xFF];
}
