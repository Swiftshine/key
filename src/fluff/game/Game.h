#ifndef FLUFF_GAME_H
#define FLUFF_GAME_H

#include "gfl/gflMemoryManagement.h"
#include "gfl/gflHeap.h"

namespace Game {
    extern "C" gfl::Heap* Mem1Heap;
    extern "C" gfl::Heap* Mem2Heap;

    void OnReset();
    void Init();
    void Run();
    void Cleanup();

    void DisableController(u32);

    void fn_8064740C(bool);
    void fn_8063C450(u32, u32);
}

#endif
