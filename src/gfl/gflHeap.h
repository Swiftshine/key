#ifndef GFL_HEAP_H
#define GFL_HEAP_H

#include "types.h"
#include <revolution/MEM.h>

namespace gfl {
    class Heap {
    public:
        static const char DefaultName[];
        static MEMAllocatorFuncs AllocFuncs;
        static size_t GetArenaSize(s32 type);
        static void* HeapAlloc(MEMAllocator* allocator, size_t size);
        static void HeapFree(MEMAllocator* allocator, void* data);
    public:
        void SetName(const char* name) DONT_INLINE_CLASS;
        Heap();
        ~Heap();
        void Init(size_t range, u16 optFlag, s32 heapType);
        void* Alloc(size_t size, u32 alignment);
        void Free(void* buf);
        size_t GetTotalFreeSizeForExpHeap();
        bool WithinRange(void* address);


        /* inline methods */
        inline MEMAllocator& GetAllocator1() {
            return mAllocator1;
        }

        inline void SetMEMAllocatorParameters(MEMAllocator* allocator, size_t alignment, MEMiHeapHead* heap);

        static inline void* GetArena(s32 type, size_t* size);
        static inline void* GetArenaLo(s32 type);
        static inline void* GetArenaHi(s32 type);
        static inline void SetArenaLo(s32 type, void* arena);
        static inline void SetArenaHi(s32 type, void* arena);
        static inline void SetAllocFuncs();
        static inline void SetArena(s32 type, void* start, void* end, bool useArenaHi);
    public:
        u8 mHeapID;
        char mHeapName[25];
        bool mUseArenaHi;
        MEMiHeapHead* mExpHeap;
        MEMAllocator mAllocator1;
        MEMAllocator mAllocator2;
        s32 mHeapType;
    };

    ASSERT_SIZE(Heap, 0x44)
    
}
#endif
