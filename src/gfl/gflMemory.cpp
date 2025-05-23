#include "gflMemory.h"

gfl::Memory ActiveInstance;

gfl::Memory* gfl::Memory::InitInstance() {
    
    if (sInstance == nullptr) {
        // ActiveInstance = Memory();
        // ActiveInstance.GetLIB1Heap() = Heap();
        // ActiveInstance.mEtcHeap = Heap();
        // ActiveInstance;
        // inst = new gfl::Memory();
        // ActiveInstance.mLIB1Heap = new gfl::Heap();
        // gfl::Heap::CreateHeap(ActiveInstance.GetLIB1Heap());
        // gfl::Heap::CreateHeap(ActiveInstance.GetLIB2Heap());
        // gfl::Heap::CreateHeap(ActiveInstance.GetStringHeap());
        // gfl::Heap::CreateHeap(ActiveInstance.GetEtcHeap());
        // gfl::Heap::CreateHeap(ActiveInstance.GetSoundHeap());
        // ActiveInstance.SetupHeaps();
        // sInstance = &ActiveInstance;
    }

    return sInstance;
}

OSMutex* gfl::Memory::ValidateHeapMutex(u8 searchID, OSMutex* mutex, u8 maxID) {
    if (searchID <= maxID) {
        return mutex;
    }
    
    return nullptr;
}
