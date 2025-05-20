#ifndef GFL_HEAP_H
#define GFL_HEAP_H

#include "types.h"
#include <revolution/MEM.h>

namespace gfl {
    class Heap {
    public:
        static const char DefaultName[];
        static MEMAllocatorFuncs AllocFuncs;
        static void* HeapAlloc(MEMAllocator* allocator, size_t size);
        static void HeapFree(MEMAllocator* allocator, void* data);
    public:
        inline Heap() {
            CreateHeap(this);
        }
        void SetName(const char* name) DONT_INLINE_CLASS;
        static Heap* CreateHeap(Heap*);
        ~Heap();
        void Init(size_t range, u16 optFlag, int heapType);
        void* Alloc(size_t size, uint alignment);
        void Free(void* buf);
        uint CountFreeBlocks();
        bool WithinRange(void* address);

        inline MEMAllocator& GetAllocator() {
            return mAllocator1;
        }

        inline void InitMEMAllocators() {

        }
        
        static inline void* GetArena(int type, size_t* size);
        static inline void* GetArenaLo(int type);
        static inline void* GetArenaHi(int type);
        static inline void SetArenaLo(void* arena, int type);
        static inline void SetAllocFuncs();
        inline void SetMEMAllocatorParameters(MEMAllocator* allocator, size_t alignment, MEMiHeapHead* heap);
    public:
        u8 mHeapID;
        char mHeapName[25];
        bool m_1A;
        MEMiHeapHead* mExpHeap;
        MEMAllocator mAllocator1;
        MEMAllocator mAllocator2;
        int mHeapType;
    };

    ASSERT_SIZE(Heap, 0x44)
    
}
#endif
