#ifndef GFL_HEAP_H
#define GFL_HEAP_H

#include "types.h"
#include <revolution/MEM.h>

namespace gfl {
    class Heap {
    public:
        static const char DefaultName[];
        static MEMAllocatorFuncs AllocFuncs;
        static size_t GetArenaSize(int type);
        static void* HeapAlloc(MEMAllocator* allocator, size_t size);
        static void HeapFree(MEMAllocator* allocator, void* data);
    public:
        void SetName(const char* name) DONT_INLINE_CLASS;
        Heap();
        ~Heap();
        void Init(size_t range, u16 optFlag, int heapType);
        void* Alloc(size_t size, uint alignment);
        void Free(void* buf);
        size_t GetTotalFreeSizeForExpHeap();
        bool WithinRange(void* address);


        /* inline methods */
        inline MEMAllocator& GetAllocator1() {
            return mAllocator1;
        }

        inline void SetMEMAllocatorParameters(MEMAllocator* allocator, size_t alignment, MEMiHeapHead* heap);

        static inline void* GetArena(int type, size_t* size);
        static inline void* GetArenaLo(int type);
        static inline void* GetArenaHi(int type);
        static inline void SetArenaLo(int type, void* arena);
        static inline void SetArenaHi(int type, void* arena);
        static inline void SetAllocFuncs();
        static inline void SetArena(int type, void* start, void* end, bool useArenaHi);
    public:
        u8 mHeapID;
        char mHeapName[25];
        bool mUseArenaHi;
        MEMiHeapHead* mExpHeap;
        MEMAllocator mAllocator1;
        MEMAllocator mAllocator2;
        int mHeapType;
    };

    ASSERT_SIZE(Heap, 0x44)
    
}
#endif
