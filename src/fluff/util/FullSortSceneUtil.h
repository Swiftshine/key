#ifndef FLUFF_FULLSORTSCENEUTIL_H
#define FLUFF_FULLSORTSCENEUTIL_H

#include "types.h"

namespace FullSortSceneUtil {
    const char* GetSceneLabelByIndex(u32 index);
    const char* GetNearSceneLabelByIndex(u32 index);
    f32 GetZOrder(u32 sceneIndex, u32 order);

    enum SceneOrder {
        eSceneOrder_Far_04  = 0,
        eSceneOrder_Far_03  = 1,
        eSceneOrder_Far_02  = 2,
        eSceneOrder_Far_01  = 3,
        eSceneOrder_Center  = 4,
        eSceneOrder_Near_01 = 5,
        eSceneOrder_Near_02 = 6,
        eSceneOrder_Near_03 = 7,
        eSceneOrder_Near_04 = 8
    };
}

#endif
