#ifndef FLUFF_CAMERAMANAGER_H
#define FLUFF_CAMERAMANAGER_H


#include "gflVec3.h"

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
    bool CheckCull(gfl::Vec3&);

};

#endif
