#ifndef GFL_MEMORY_HEAP_H
#define GFL_MEMORY_HEAP_H

#include <flf_types.h>
#include <revolution/MEM.h>

namespace gfl {
    class Heap {
    public:
        bool WithinRange(void* address);

        void Free(void* buf);
    public:
        u8 heapID;
        char name[25];
        bool _1A;
        u8 _1B; // padding?
        MEMAllocator* allocatorPtr;
        MEMAllocator allocator;
        void* _30;
        void* _34;
        u32 flags;
        gfl::Heap* _3C;
        u32 heapType;
    };

    ASSERT_SIZE(Heap, 0x44)
}
#endif
