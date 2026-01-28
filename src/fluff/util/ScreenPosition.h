#ifndef FLUFF_SCREENPOSITION_H
#define FLUFF_SCREENPOSITION_H

#include "gfl/gflVec2.h"

struct ScreenPosition {
    ScreenPosition() {
        mPosition.x = 0;
        mPosition.y = 0;
        mCullThreshold = 0;
    }
    gfl::Vec2 mPosition;
    float mCullThreshold;
};


#endif
