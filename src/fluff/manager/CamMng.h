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

    static const f32 CullingThreshold;

    /* Class Methods */

    void fn_80056974();
    void fn_800544B4(void*, f32);
    void GetScreenBounds(f32* pX, f32* pY, f32* pWidth, f32* pHeight, s32 sceneID);
    void fn_800545B4(s32, s32);
    void fn_800545D8(s32);
    bool ShouldCull(ScreenPosition&);
    const gfl::Vec2& GetCurrentPosition() const;
    void SetAllPositions(const nw4r::math::VEC2&);
    void SetZoom(f32);
};

#endif
