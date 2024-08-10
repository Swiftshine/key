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
        u8 mHeapID;
        char mHeapName[25];
        bool m_1A;
        u8 m_1B; // padding?
        MEMiHeapHead* mpExpHeap;
        MEMAllocator mAllocator;
        MEMAllocatorFuncs* mpAllocFuncs;
        MEMiHeapHead* mp_34;
        u32 mFlags;
        gfl::Heap* mpSelf;
        u32 mHeapType;
    };

    ASSERT_SIZE(Heap, 0x44)
}
#endif
