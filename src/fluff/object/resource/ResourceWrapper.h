#ifndef FLUFF_RESOURCEWRAPPER_H
#define FLUFF_RESOURCEWRAPPER_H

#include "gfl/gflScnMdlWrapper.h"
#include "graphics/FullSortScene.h"

// todo: find a better name for this
class ResourceWrapper {
public:
    ResourceWrapper();
    ~ResourceWrapper();

    void SetMatrix(float& yOffset, MTX34& mtx);
    void RegisterResources(gfl::ResFileInfoPointer&, const char*, int, FullSortScene* scene, int);
    void SetUpdate(bool shouldUpdate);    
private:
    gfl::ScnMdlWrapper* mModelWrapper1;
    gfl::ScnMdlWrapper* mModelWrapper2;
    float mXOffset;
    float mZOffset;
};

#endif
