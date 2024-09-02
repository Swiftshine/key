#include "gflMemory.h"

OSMutex* gfl::Memory::ValidateHeapMutex(u8 searchID, OSMutex* mutex, u8 maxID) {
    if (searchID <= maxID) {
        return mutex;
    }
    
    return nullptr;
}