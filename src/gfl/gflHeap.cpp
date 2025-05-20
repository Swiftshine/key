#include "gflHeap.h"
#include "gflMemoryUtil.h"

using namespace gfl;
MEMAllocatorFuncs Heap::AllocFuncs;

// yes it's "NOT INITALIZED" and not "INITIALIZED", very cool good-feel
const char Heap::DefaultName[] = "NOT INITALIZED";

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

    SetArenaLo(start, type);

    return arenaLo;
}

inline void Heap::SetArenaLo(void* arena, int type) {
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

void Heap::SetName(const char* newName) {
    gfl::Strcpy(mHeapName, sizeof(mHeapName), newName);
}

Heap* Heap::CreateHeap(Heap* heap) {
    heap->mHeapID = 0;
    heap->SetName(DefaultName);
    heap->mExpHeap = nullptr;
    return heap;
}


Heap::~Heap() {
    u32 arenaLo;
    s32 arenaHi;
    u32 bVar1;
    s32 hType;
    u32 end;
    MEMiHeapHead *exp;
  
    exp = this->mExpHeap;
    if (!exp) { return; }

    end = (s32)exp->end;
    MEMDestroyExpHeap(exp);
    hType = this->mHeapType;
    bVar1 = this->m_1A;
    
    switch (hType) {
        case 1: {
            arenaLo = (s32)OSGetMEM1ArenaLo();
            break;
        }
        case 2: {
            arenaLo = (s32)OSGetMEM2ArenaLo();
            break;
        }
        default: {
            arenaLo = nullptr;
            break;
        }
    }
    
    switch (hType) {
        case 1: {
            arenaHi = (s32)OSGetArenaHi();
            break;
        }
        case 2: {
            arenaHi = (s32)OSGetMEM2ArenaHi();
            break;
        }
        default: {
            arenaHi = nullptr;
            break;
        }
    }



    if ((s32)bVar1 != 0) {
        if ((u32)exp == arenaHi + 1) {
            switch (hType) {
                case 1: {
                    OSSetMEM1ArenaHi((u8*)end - 1);
                    break;
                }
                case 2: {
                    OSSetMEM2ArenaHi((u8*)end - 1);
                    break;
                }
            }
        }
    } else if ((u32)end == arenaLo) {
        switch (hType) {
            case 1: {
                OSSetMEM1ArenaLo(exp);
                break;
            }
            case 2: {
                OSSetMEM2ArenaLo(exp);
                break;
            }
        }
    }
    this->mExpHeap = nullptr;
    this->mHeapType = 0;
}

void Heap::Init(size_t range, u16 optFlag, int heapType) {
    mHeapType = heapType;
    mExpHeap = MEMCreateExpHeapEx(GetArena(mHeapType, &range), range, optFlag);
    
    this->m_1A = false;

    SetMEMAllocatorParameters(&mAllocator1, 0x20, mExpHeap);
    SetMEMAllocatorParameters(&mAllocator2, 0x10, mExpHeap);
}


void* Heap::Alloc(size_t size, uint alignment) {
    return MEMAllocFromExpHeapEx(this->mExpHeap, size, alignment);
}

void Heap::Free(void* address) {
    MEMFreeToExpHeap(this->mExpHeap, address);
}

extern "C" int MEMGetTotalFreeSizeForExpHeap(MEMiHeapHead*);

uint Heap::CountFreeBlocks() {
    return MEMGetTotalFreeSizeForExpHeap(this->mExpHeap);
}

bool Heap::WithinRange(void* address) {
    void* end = this->mExpHeap->end;
    if (address >= this->mExpHeap && address <= end) {
        return true;
    }
    return false;
}
