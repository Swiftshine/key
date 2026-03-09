#include "util/FullSortSceneUtil.h"
#pragma readonly_strings on

float ZOrders[12] = {
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

float PriorityOffsets[9] = {
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

const char* FullSortSceneUtil::GetSceneLabelByIndex(uint index) {
    return SceneLabels[index];
}

const char* FullSortSceneUtil::GetNearSceneLabelByIndex(uint index) {
    return SceneLabels[index] + 9;
}

float FullSortSceneUtil::GetZOrder(uint sceneIndex, uint priority) {
    return ZOrders[sceneIndex] + PriorityOffsets[priority];
}
