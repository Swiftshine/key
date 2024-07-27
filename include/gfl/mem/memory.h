#ifndef GFL_MEMORY_H
#define GFL_MEMORY_H

#include <gfl/mem/MemoryBase.h>

namespace gfl {
    class Memory : public MemoryBase {
    private:
        Memory();
    public:
        Heap lib1Heap;
        Heap lib2Heap;
        Heap stringHeap;
        Heap etcHeap;
        Heap soundHeap;
    };

    ASSERT_SIZE(Memory, 0x1B8);
}
#endif
