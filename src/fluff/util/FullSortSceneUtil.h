#ifndef FLUFF_FULLSORTSCENEUTIL_H
#define FLUFF_FULLSORTSCENEUTIL_H

#include "types.h"

namespace FullSortSceneUtil {
    const char* GetSceneLabelByIndex(u32 index);
    const char* GetNearSceneLabelByIndex(u32 index);
    f32 GetZOrder(u32 sceneIndex, u32 order);

    enum SceneID {
        eSceneID_Far_05  = 0,
        eSceneID_Far_04  = 1,
        eSceneID_Far_03  = 2,
        eSceneID_Far_02  = 3,
        eSceneID_Far_01  = 4,
        eSceneID_Map     = 5,
        eSceneID_Game    = 6,
        eSceneID_Near_01 = 7,
        eSceneID_Near_02 = 8,
        eSceneID_Near_03 = 9,
        eSceneID_Near_04 = 10,
        eSceneID_Near_05 = 11
    };

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
