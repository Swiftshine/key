#include "gflHeap.h"
#include "gflMemoryUtil.h"

#pragma readonly_strings on

using namespace gfl;

inline void Heap::SetMEMAllocatorParameters(MEMAllocator* allocator, size_t alignment, MEMiHeapHead* heap) {
    AllocFuncs.allocFunc = &HeapAlloc;
    AllocFuncs.freeFunc = &HeapFree;
    
    allocator->funcs = &AllocFuncs;
    allocator->heap = heap;
    allocator->heapParam1 = alignment;
    allocator->heapParam2 = (u32)(this);
}

inline void* Heap::GetArenaHi(int type) {
    void* arena;
    
    switch (type) {
        case 1: {
            arena = OSGetArenaHi();
            break;
        }

        case 2: {
            arena = OSGetMEM2ArenaHi();
            break;
        }
        
        default: {
            arena = nullptr;
            break;
        }
    }

    return arena;
}

inline void* Heap::GetArenaLo(int type) {
    void* arena;

    switch (type) {
        case 1: {
            arena = OSGetMEM1ArenaLo();
            break;
        }
        
        case 2: {
            arena = OSGetMEM2ArenaLo();
            break;
        }
        
        default: {
            arena = nullptr;
            break;
        }
    }
    
    return arena;
}

inline void* Heap::GetArena(int type, size_t* size) {
    void* arenaLo = GetArenaLo(type);
    void* arenaHi = GetArenaHi(type);
    void* start;
    
    if (*size == 0xFFFFFFFF) { 
        *size = (u32)arenaHi - (u32)arenaLo;
        start = arenaHi;
    } else {
        arenaHi = (void*)((u32)arenaLo + *size);
        start = arenaHi;
    }
    
    SetArenaLo(type, start);
    
    return arenaLo;
}

inline void Heap::SetArenaLo(int type, void* arena) {
    switch (type) {
        case 1: {
            OSSetMEM1ArenaLo(arena);
            break;
        }

        case 2: {
            OSSetMEM2ArenaLo(arena);
            break;
        }
    }
}

inline void Heap::SetArenaHi(int type, void* arena) {
    switch (type) {
        case 1: {
            OSSetMEM1ArenaHi(arena);
            break;
        }
        
        case 2: {
            OSSetMEM2ArenaHi(arena);
            break;
        }
    }
}


inline void Heap::SetArena(int type, void* start, void* end, bool useArenaHi) {
    void* arenaLo = GetArenaLo(type);
    void* arenaHi = GetArenaHi(type);

    if (useArenaHi) {
        if ((u32)start == (u32)arenaHi + 1) {
            SetArenaHi(type, (void*)((u32)end - 1));
        }
    } else if (end == arenaLo) {
        SetArenaLo(type, start);
    }
}

void Heap::SetName(const char* newName) {
    gfl::Strcpy(mHeapName, sizeof(mHeapName), newName);
}

Heap::Heap() {
    mHeapID = 0;
    SetName("NOT INITALIZED"); // typo on the developers' part
    mExpHeap = nullptr;
}

Heap::~Heap() {
    bool useArenaHi;
    int heapType;
    void* end;

    MEMiHeapHead* expHeap = mExpHeap;

    if (expHeap != nullptr) {
        end = expHeap->end;
        MEMDestroyExpHeap(expHeap);
        useArenaHi = mUseArenaHi;
        heapType = mHeapType;
        SetArena(heapType, expHeap, end, useArenaHi);
        mExpHeap = nullptr;
        mHeapType = 0;
    }
}

void Heap::Init(size_t range, u16 optFlag, int heapType) {
    mHeapType = heapType;
    mExpHeap = MEMCreateExpHeapEx(GetArena(mHeapType, &range), range, optFlag);
    
    mUseArenaHi = false;

    SetMEMAllocatorParameters(&mAllocator1, 0x20, mExpHeap);
    SetMEMAllocatorParameters(&mAllocator2, 0x10, mExpHeap);
}

void* Heap::Alloc(size_t size, uint alignment) {
    return MEMAllocFromExpHeapEx(mExpHeap, size, alignment);
}

void Heap::Free(void* address) {
    MEMFreeToExpHeap(mExpHeap, address);
}

extern "C" int MEMGetTotalFreeSizeForExpHeap(MEMiHeapHead*);

size_t Heap::GetTotalFreeSizeForExpHeap() {
    return MEMGetTotalFreeSizeForExpHeap(mExpHeap);
}

bool Heap::WithinRange(void* address) {
    void* end = mExpHeap->end;
    if (address >= mExpHeap && address <= end) {
        return true;
    }
    return false;
}

size_t Heap::GetArenaSize(int type) {
    return (u32)GetArenaHi(type) - (u32)GetArenaLo(type);
}

void* Heap::HeapAlloc(MEMAllocator* allocator, size_t size) {
    return gfl::Alloc((Heap*)allocator->heapParam2, size, allocator->heapParam1);
}

void Heap::HeapFree(MEMAllocator* allocator, void* data) {
    gfl::Free(data);
}
