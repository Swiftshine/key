#ifndef FLUFF_GAME_H
#define FLUFF_GAME_H

#include "gfl/gflMemoryManagement.h"
#include "gfl/gflHeap.h"

namespace Game {
    gfl::Heap* Mem1Heap;
    gfl::Heap* Mem2Heap;

    void OnReset();
    void Init();
    void Run();
    void Cleanup();
}

#endif
