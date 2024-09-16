#include "util/KdTreeUtil.h"

int KdTreeUtil::DetermineNodePlacement(KdTreeSplitInfo& splitInfo, gfl::Vec2& point) {
    float coordinate;
    if (splitInfo.mSplitY) {
        // the node is split on the Y axis
        coordinate = point.y;

        if (coordinate > splitInfo.mMidpoint) {
            return NodePlacement::Child1;
        } else if (coordinate < splitInfo.mMidpoint) {
            return NodePlacement::Child2;
        }
        
        return NodePlacement::Self;
    }

    // the node is split on the X axis
    coordinate = point.x;
    if (coordinate > splitInfo.mMidpoint) {
        return NodePlacement::Child1;
    }

    if (coordinate < splitInfo.mMidpoint) {
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

int KdTreeUtil::DetermineNodePlacement(KdTreeSplitInfo& splitInfo, PointPair& points) {
    if (splitInfo.mSplitY) {
        // y axis

        if (points.first.y > splitInfo.mMidpoint) {
            return NodePlacement::Child1;
        } else if (points.second.y < splitInfo.mMidpoint) {
            return NodePlacement::Child2;
        }
    
        return NodePlacement::Self;
    }

    // x axis
    
    if (points.first.x > splitInfo.mMidpoint) {
        return NodePlacement::Child1;
    } else if (points.second.x < splitInfo.mMidpoint) {
        return NodePlacement::Child2;
    }

    return NodePlacement::Self;
}
