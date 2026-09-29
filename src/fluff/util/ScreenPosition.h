#ifndef FLUFF_SCREENPOSITION_H
#define FLUFF_SCREENPOSITION_H

#include <gfl/gflVec2.h>

struct ScreenPosition {
    ScreenPosition()
        : mX(0)
        , mY(0)
        , mCullThreshold(0)
    { }

    ScreenPosition(f32 x, f32 y, f32 c)
        : mX(x)
        , mY(y)
        , mCullThreshold(c)
    { }

    struct {
        f32 mX, mY;
        f32 mCullThreshold;
    };
};

#endif
