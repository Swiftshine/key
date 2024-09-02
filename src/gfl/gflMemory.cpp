#include "gflMemory.h"

gfl::Memory ActiveInstance;

gfl::Memory* gfl::Memory::InitInstance() {
    if (nullptr == Instance()) {
        gfl::Heap::CreateHeap(ActiveInstance.GetLIB1Heap());
        gfl::Heap::CreateHeap(ActiveInstance.GetLIB2Heap());
        gfl::Heap::CreateHeap(ActiveInstance.GetStringHeap());
        gfl::Heap::CreateHeap(ActiveInstance.GetEtcHeap());
        gfl::Heap::CreateHeap(ActiveInstance.GetSoundHeap());
        ActiveInstance.SetupHeaps();
        sInstance = &ActiveInstance;
    }
    return Instance();
}

OSMutex* gfl::Memory::ValidateHeapMutex(u8 searchID, OSMutex* mutex, u8 maxID) {
    if (searchID <= maxID) {
        return mutex;
    }
    
    return nullptr;
}