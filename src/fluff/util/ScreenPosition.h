#ifndef FLUFF_SCREENPOSITION_H
#define FLUFF_SCREENPOSITION_H

#include <nw4r/math.h>

struct ScreenPosition {
    nw4r::math::VEC2 mPosition;
    float mCullThreshold;
};


#endif