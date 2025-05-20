#ifndef GFL_MEMORYBASE_H
#define GFL_MEMORYBASE_H

#include "types.h"
#include "gflHeap.h"

#define GFL_MEMORYBASE_HEAP_COUNT 24

namespace gfl {
    class MemoryBase {
    public:
        inline Heap* FindContainingHeap(Heap** heapArr, void* address) {
            for (uint i = 0; i < GFL_MEMORYBASE_HEAP_COUNT; i++) {
                if (mHeaps[i] && mHeaps[i]->WithinRange(address)) {
                    return mHeaps[i];
                }
            }

            return nullptr;
        }
    public:
        inline MemoryBase() {

        }

        void Reset();
        void ReplaceHeap(Heap*);
        Heap* GetHeapByAddress(void*);
        u8 GetHeapIDByAddress(void*);
        void Free(void*);
        virtual Heap* GetHeapByID(uint heapID);
    public:
        Heap* mHeaps[GFL_MEMORYBASE_HEAP_COUNT];
    };

    // ASSERT_SIZE(MemoryBase, 0x64)
}
#endif
