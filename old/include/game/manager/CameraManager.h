#ifndef FLUFF_CAMERA_MANAGER_H
#define FLUFF_CAMERA_MANAGER_H

#include <flf_types.h>

class CameraManager {
public:
    static const f32 CullingThreshold;
public:
    bool CheckCull(Vec3f*);
};

#endif
