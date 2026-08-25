#ifndef FLUFF_SCREENPOSITION_H
#define FLUFF_SCREENPOSITION_H

struct ScreenPosition {
    ScreenPosition(f32 x, f32 y, f32 c)
        : mX(x)
        , mY(y)
        , mCullThreshold(c)
    { }

    struct {
        f32 mX;
        f32 mY;
        f32 mCullThreshold;
    };
};

#endif
