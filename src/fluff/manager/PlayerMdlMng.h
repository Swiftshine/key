#ifndef FLUFF_PLAYERMDLMNG_H
#define FLUFF_PLAYERMDLMNG_H

#include "graphics/FlfMdlDraw.h"

class PlayerMdlMng {
public:
    /* Static Variables */

    static const int PlayerAnimationIDs[303]; // not sure how many there are

    /* Class Methods */

    void fn_800A0A84();
    void SetUpdateRate(float rate);
    void SetVisibility(bool visibility);
    void ResetUpdateRate();
    void ResetScene(FullSortScene*);

    FlfMdlDraw* GetFlfMdlDraw() {
        return *(reinterpret_cast<FlfMdlDraw**>(reinterpret_cast<u8*>(this) + 0x10));
    }
};

#endif
