#include <gfl/mem/Heap.h>
#include <gfl/mem/Mem.h>

using namespace gfl;
MEMAllocatorFuncs Heap::AllocFuncs;

// yes it's "NOT INITALIZED" and not "INITIALIZED", very cool good-feel
const char Heap::DefaultName[] = "NOT INITALIZED";

void Heap::SetName(const char* newName) {
    mem::Memcpy(name, sizeof(name), const_cast<char*>(newName));
}

Heap::Heap() {
    heapID = 0;
    SetName(DefaultName);
    expHeap = NULL;
}

Heap::~Heap() {
    u32 arenaLo;
    s32 arenaHi;
    u32 bVar1;
    s32 hType;
    u32 end;
    MEMiHeapHead *exp;
  
    exp = this->expHeap;
    if (!exp) { return; }

    end = (s32)exp->end;
    MEMDestroyExpHeap(exp);
    hType = this->heapType;
    bVar1 = this->_1A;
    
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
            arenaLo = NULL;
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
            arenaHi = NULL;
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
    this->expHeap = NULL;
    this->heapType = 0;
}

void Heap::Init(size_t range, u16 optFlag, int hType) {
    s32 len;
    s32 arenaLo;
    s32 arenaHi;
    s32 heapHead;

    len = range;
    this->heapType = hType;

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
            arenaLo = NULL;
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
            arenaHi = NULL;
            break;
        }
    }

    
    if (len == -1U) {
        len = arenaHi - arenaLo;
    } else {
        arenaHi = arenaLo + len;
    }
    

    switch (hType) {
        case 1: {
            OSSetMEM1ArenaLo((void*)arenaHi);
            break;
        }
        case 2: {
            OSSetMEM2ArenaLo((void*)arenaHi);
            break;
        }
    }

    heapHead = (s32)MEMCreateExpHeapEx((void*)arenaLo, range, optFlag);
    this->_1A = false;

    Heap::AllocFuncs.freeFunc = HeapFree;
    
    this->expHeap = (MEMiHeapHead*)heapHead;
    this->allocator.funcs = &Heap::AllocFuncs;
    this->allocator.heap = (MEMiHeapHead*)heapHead;
    this->allocator.heapParam1 = 0x20; // alignment?
    this->allocator.heapParam2 = (u32)this;
    Heap::AllocFuncs.allocFunc = HeapAlloc;
    this->allocFuncs = &Heap::AllocFuncs;
    this->_34 = (MEMiHeapHead*)heapHead;
    this->flags = 0x10;
    this->self = this;
}

void* Heap::Alloc(size_t size, u32 alignment) {
    return MEMAllocFromExpHeapEx(this->expHeap, size, alignment);
}

void Heap::Free(void* address) {
    MEMFreeToExpHeap(this->expHeap, address);
}

extern "C" int MEMGetTotalFreeSizeForExpHeap(MEMiHeapHead*);

int Heap::CountFreeBlocks() {
    return MEMGetTotalFreeSizeForExpHeap(this->expHeap);
}

bool Heap::WithinRange(void* address) {
    void* end = this->expHeap->end;
    if (address >= this->expHeap && address <= end) {
        return true;
    }
    return false;
}
