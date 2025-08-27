#ifndef FLUFF_GMKPARTSMDLSET_H
#define FLUFF_GMKPARTSMDLSET_H

#include "gfl/gflScnMdlWrapper.h"
#include "graphics/FullSortScene.h"
#include "gfl/gflResFileInfo.h"
#include <nw4r/math.h>

class GmkPartsMdlSet {
public:
    /* Constructor + Destructor */

    GmkPartsMdlSet();
    ~GmkPartsMdlSet();

    /* Class Methods */

    void SetMatrix(const float zOffset, nw4r::math::MTX34& rMatrix, bool arg3);
    bool GetPrimaryMatrix(nw4r::math::MTX34& rDestMatrix);
    void RegisterResources(gfl::ResFileObject& rFileInfo, const char* pModelName, const char* pShadowName, FullSortScene* pFullSortScene, uint flags);
    void SetUpdate(bool shouldUpdate);
    void fn_802374D4(float);
    void ReplaceScene(gfl::Scene* pScene);

    /* Class Members */

    /* 0x0 */ gfl::ScnMdlWrapper* mPrimaryModel;
    /* 0x4 */ gfl::ScnMdlWrapper* mShadowModel;
    /* 0x8 */ nw4r::math::VEC2 mShadowOffset;
};

#endif
