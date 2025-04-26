#ifndef FLUFF_CAMERAMANAGER_H
#define FLUFF_CAMERAMANAGER_H

#include <nw4r/math.h>

class CameraManager {
private:
    static CameraManager* sInstance;
public:
    static const float CullingThreshold;
public:
    static inline CameraManager* Instance() {
        return sInstance;
    }

    void fn_80056974();
    void fn_800544B4(void*, float);
    void fn_800548AC();
    void fn_800545B4(int, int);
    void fn_800545D8(int);
    bool CheckCull(nw4r::math::VEC3& position);
    nw4r::math::VEC2& GetCurrentPosition();
    void SetAllPositions(const nw4r::math::VEC2&);
    void SetZoom(float);
};

#endif
