#ifndef FLUFF_CAMERAMANAGER_H
#define FLUFF_CAMERAMANAGER_H


#include "gflVec3.h"

class CameraManager {
public:
    static const float CullingThreshold;
public:
    bool CheckCull(gfl::Vec3&);
};

#endif