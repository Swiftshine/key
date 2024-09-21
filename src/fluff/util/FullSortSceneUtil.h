#ifndef FLUFF_FULLSORTSCENEUTIL_H
#define FLUFF_FULLSORTSCENEUTIL_H

#include "types.h"

namespace FullSortSceneUtil {
    const char* GetSceneLabelByIndex(uint index);
    const char* GetNearSceneLabelByIndex(uint index);
    float GetZOrder(uint sceneIndex, uint arg1);

    ENUM_CLASS(SceneIDs,
        Far_05,
        Far_04,
        Far_03,
        Far_02,
        Far_01,
        Map,
        Game,
        Near_01,
        Near_02,
        Near_03,
        Near_04,
        Near_05
    );

    float ZOrders[12];
    float Angles[9];
    const char* SceneLabels[12];
}

#endif
