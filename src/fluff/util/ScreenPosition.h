#ifndef FLUFF_SCREENPOSITION_H
#define FLUFF_SCREENPOSITION_H

#include "gfl/gflVec2.h"

struct ScreenPosition {
    gfl::Vec2 mPosition;
    float mCullThreshold;
};


#endif