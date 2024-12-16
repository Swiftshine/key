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

    void SetMatrix(float& yOffset, MTX34& mtx);
    void RegisterResources(gfl::ResFileInfoPointer&, const char*, int, FullSortScene* scene, int);
    void SetUpdate(bool shouldUpdate);    
private:
    gfl::ScnMdlWrapper* mModelWrapper1;
    gfl::ScnMdlWrapper* mModelWrapper2;
    nw4r::math::VEC2 mOffset;
};

#endif
