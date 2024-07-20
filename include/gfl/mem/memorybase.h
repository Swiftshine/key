#ifndef GFL_MEMORY_BASEH
#define GFL_MEMORY_BASEH

#include <gfl/mem/heap.h>
#include <flf_types.h>

const u32 HEAP_COUNT = 0x18;

namespace gfl {
    class MemoryBase {
    public:
        inline Heap* FindContainingHeap(Heap** heapArr, void* address) {
            for (u32 i = 0; i < HEAP_COUNT; i++) {
                if (heaps[i] && heaps[i]->WithinRange(address)) {
                    return heaps[i];
                }

            }
            return NULL;
        }
    public:
        inline MemoryBase() { }
        virtual ~MemoryBase() = 0;

        void Reset();
        void ReplaceHeap(Heap*);
        Heap* GetHeapByAddress(void*);
        u8 GetHeapIDByAddress(void*);
        void Free(void*);
        Heap* GetHeapByID(u32 heapID);
    public:
        Heap* heaps[HEAP_COUNT];
    };

    ASSERT_SIZE(MemoryBase, 0x64)
}
#endif
