#ifndef GFL_MEMORY_H
#define GFL_MEMORY_H

#include "gflMemoryBase.h"

namespace gfl {
    class Memory : public MemoryBase {
    public:
        inline Memory() { }
    public:
        Heap mLIB1Heap;
        Heap mLIB2Heap;
        Heap mStringHeap;
        Heap mEtcHeap;
        Heap mSoundHeap;
    };

    ASSERT_SIZE(Memory, 0x1B8);
}

#endif