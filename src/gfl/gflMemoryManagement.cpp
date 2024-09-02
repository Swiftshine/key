#include "gflMemoryManagement.h"
#include "gflMemory.h"

void* gfl::Alloc(u8 heapID, size_t size, uint align) {
    gfl::Memory::CheckInit();
    return gfl::Memory::TryGetInstance()->GetHeapByID(heapID)->Alloc(size, align);
}

void* gfl::Alloc(Heap* heap, size_t size, uint align) {
    gfl::Memory::CheckInit();
    gfl::Memory::TryGetInstance();
    return heap->Alloc(size, align);
}

void gfl::Free(void* data) {
    gfl::Memory::CheckInit();
    OSMutex* mx = gfl::Memory::GetCurrentMutex();
    OSLockMutex(mx);
    gfl::Memory::TryGetInstance()->Free(data);
    OSUnlockMutex(mx);
}