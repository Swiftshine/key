#ifndef FLUFF_FULLSORTSCENEUTIL_H
#define FLUFF_FULLSORTSCENEUTIL_H

#include "types.h"

namespace FullSortSceneUtil {
    const char* GetSceneLabelByIndex(uint index);
    const char* GetNearSceneLabelByIndex(uint index);
    float GetZOrder(uint sceneIndex, uint priority);

    ENUM_CLASS(SceneID,
        Far_05  = 0,
        Far_04  = 1,
        Far_03  = 2,
        Far_02  = 3,
        Far_01  = 4,
        Map     = 5,
        Game    = 6,
        Near_01 = 7,
        Near_02 = 8,
        Near_03 = 9,
        Near_04 = 10,
        Near_05 = 11
    );

    float ZOrders[12];
    float PriorityOffsets[9];
    const char* SceneLabels[12];
}

#endif
