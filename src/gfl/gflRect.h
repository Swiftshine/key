#ifndef GFL_RECT
#define GFL_RECT

namespace gfl {
    struct Rect {
        Rect()
            : mLeft(0.0f)
            , mTop(0.0f)
            , mRight(0.0f)
            , mBottom(0.0f)
        { }
        
        float mLeft, mTop, mRight, mBottom;
    };
}

#endif