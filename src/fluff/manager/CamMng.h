#ifndef FLUFF_CAMMNG_H
#define FLUFF_CAMMNG_H

#include <nw4r/math.h>
#include "util/ScreenPosition.h"
#include "gfl/gflVec2.h"

class CamMng {
public:
    /* Static Variables */

    static CamMng* sInstance;

    static inline CamMng* Instance() {
        return sInstance;
    }

    static const float CullingThreshold;

    /* Class Methods */

    void fn_80056974();
    void fn_800544B4(void*, float);
    void fn_800548AC(float*,float*,float*,float*,int);
    void fn_800545B4(int, int);
    void fn_800545D8(int);
    bool ShouldCull(ScreenPosition&);
    const gfl::Vec2& GetCurrentPosition() const;
    void SetAllPositions(const nw4r::math::VEC2&);
    void SetZoom(float);
};

#endif
