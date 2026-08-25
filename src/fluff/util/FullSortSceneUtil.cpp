#include "util/FullSortSceneUtil.h"
#pragma readonly_strings on

f32 ZOrders[12] = {
    -1290.0f,
    -1080.0f,
    -870.0,
    -660.0,
    -450.0,
    -240.0,
    0.0f,
    240.0f,
    450.0f,
    660.0f,
    870.0f,
    1080.0f,
};

f32 PriorityOffsets[9] = {
    -120.0f,
    -90.0f,
    -60.0f,
    -30.0f,
    0.0f,
    30.0f,
    60.0f,
    90.0f,
    120.0f,
};

const char* SceneLabels[12] = {
    "SCENE_ID_FAR_05",
    "SCENE_ID_FAR_04",
    "SCENE_ID_FAR_03",
    "SCENE_ID_FAR_02",
    "SCENE_ID_FAR_01",
    "SCENE_ID_MAP",
    "SCENE_ID_GAME",
    "SCENE_ID_NEAR_01",
    "SCENE_ID_NEAR_02",
    "SCENE_ID_NEAR_03",
    "SCENE_ID_NEAR_04",
    "SCENE_ID_NEAR_05",
};

const char* FullSortSceneUtil::GetSceneLabelByIndex(u32 index) {
    return SceneLabels[index];
}

const char* FullSortSceneUtil::GetNearSceneLabelByIndex(u32 index) {
    return SceneLabels[index] + 9;
}

f32 FullSortSceneUtil::GetZOrder(u32 sceneIndex, u32 priority) {
    return ZOrders[sceneIndex] + PriorityOffsets[priority];
}
