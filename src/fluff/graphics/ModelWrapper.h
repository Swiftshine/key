#ifndef FLUFF_MODELWRAPPER_H
#define FLUFF_MODELWRAPPER_H

#include "gfl/gflScnMdlWrapper.h"
#include "graphics/FullSortScene.h"
#include "gfl/gflResFileInfo.h"
#include <nw4r/math.h>

class ModelWrapper {
public:
    ModelWrapper();
    ~ModelWrapper();

    void SetMatrix(const float zOffset, nw4r::math::MTX34& mtx, bool arg3);
    bool GetPrimaryMatrix(nw4r::math::MTX34& dest);
    void RegisterResources(gfl::ResFileObject& fileInfo, const char* modelName, const char* shadowName, FullSortScene* scene, uint flags);
    void SetUpdate(bool shouldUpdate);
    void fn_802374D4(float);
    void ReplaceScene(gfl::Scene* scene);
private:
    gfl::ScnMdlWrapper* mPrimaryModel;
    gfl::ScnMdlWrapper* mShadowModel;
    nw4r::math::VEC2 mShadowOffset;
};

#endif
