#ifndef FLUFF_SCREENPOSITION_H
#define FLUFF_SCREENPOSITION_H

struct ScreenPosition {
    ScreenPosition(float x, float y, float c)
        : mX(x)
        , mY(y)
        , mCullThreshold(c)
    { }

    struct {
        float mX;
        float mY;
        float mCullThreshold;
    };
};

#endif
