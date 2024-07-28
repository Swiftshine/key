#ifndef GFL_MEMORY_HEAP_H
#define GFL_MEMORY_HEAP_H

#include <gfl/gfl_types.h>
#include <revolution/MEM.h>

namespace gfl {

    class Heap {
    public:
        static const char DefaultName[];
        static MEMAllocatorFuncs AllocFuncs;
        static MEMAllocatorAllocFunc HeapAlloc;
        static MEMAllocatorFreeFunc  HeapFree;

    public:
        void  SetName(const char* name) DONT_INLINE;
        Heap();
        ~Heap();
        void  Init(size_t range, u16 optFlag, int heapType);
        void* Alloc(size_t size, u32 alignment);
        void  Free(void* buf);
        int   CountFreeBlocks();
        bool  WithinRange(void* address);

    public:
        u8 heapID;
        char name[25];
        bool _1A;
        u8 _1B; // padding?
        MEMiHeapHead* expHeap;
        MEMAllocator allocator;
        MEMAllocatorFuncs* allocFuncs;
        MEMiHeapHead* _34;
        u32 flags;
        gfl::Heap* self;
        u32 heapType;
    };

    ASSERT_SIZE(Heap, 0x44)
}
#endif
