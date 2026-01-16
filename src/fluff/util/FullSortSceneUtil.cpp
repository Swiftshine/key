#include "util/FullSortSceneUtil.h"

const char* FullSortSceneUtil::GetSceneLabelByIndex(uint index) {
    return SceneLabels[index];
}

const char* FullSortSceneUtil::GetNearSceneLabelByIndex(uint index) {
    return SceneLabels[index] + 9;
}

float FullSortSceneUtil::GetZOrder(uint sceneIndex, uint priority) {
    return ZOrders[sceneIndex] + PriorityOffsets[priority];
}
