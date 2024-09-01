#ifndef FLUFF_IOBJHITCB_H
#define FLUFF_IOBJHITCB_H

#include "types.h"


#define CALLBACK_COUNT 0x53

// size (no inheritance): 0x45C (sizeof(PTMF) * 93)

/**
 * @note This class is inherited by objects that utilise collision.
 * The actual callbacks, up to 93 of them, are defined on a case-by-case basis.
 * See `PlayerBase::SetupCallbacks()` (0x8006A8D0) as an example.
 */
class IObjHitCB {
public:
    void(* mCallbacks[CALLBACK_COUNT])(void* owner);
};

#endif