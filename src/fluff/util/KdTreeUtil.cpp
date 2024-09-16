#include "util/KdTreeUtil.h"

int KdTreeUtil::DetermineNodePlacement(SplitInfo& splitInfo, gfl::Vec2& point) {
    float val;
    if (splitInfo.first) {
        // the node is split on the Y axis
        val = point.y;
        if (val > splitInfo.second) {
            return NodePlacement::Child1;
        }

        if (val < splitInfo.second) {
            return NodePlacement::Child2;
        }
        
        return NodePlacement::Self;
    }

    // the node is split on the X axis
    val = point.x;
    if (val > splitInfo.second) {
        return NodePlacement::Child1;
    }

    if (val < splitInfo.second) {
        return NodePlacement::Child2;
    }

    return NodePlacement::Self;
}
int KdTreeUtil::DetermineNodePlacementStrictly(SplitInfo& splitInfo, PointPair& points) {

    return NodePlacement::Self;
}

int KdTreeUtil::DetermineNodePlacementByProximity(SplitInfo& splitInfo, PointPair& points) {
    return NodePlacement::Self;
}

int KdTreeUtil::DetermineNodePlacement(SplitInfo& splitInfo, PointPair& points) {
    
    return NodePlacement::Self;
}
