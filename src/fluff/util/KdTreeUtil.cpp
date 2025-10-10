#include "util/KdTreeUtil.h"

int KdTreeUtil::DetermineNodePlacement(KdTreeSplitInfo& rSplitInfo, nw4r::math::VEC2& point) {
    float coordinate;
    if (rSplitInfo.mSplitY) {
        // the node is split on the Y axis
        coordinate = point.y;

        if (coordinate > rSplitInfo.mMidpoint) {
            return NodePlacement::Child1;
        } else if (coordinate < rSplitInfo.mMidpoint) {
            return NodePlacement::Child2;
        }
        
        return NodePlacement::Self;
    }

    // the node is split on the X axis
    coordinate = point.x;
    if (coordinate > rSplitInfo.mMidpoint) {
        return NodePlacement::Child1;
    } else if (coordinate < rSplitInfo.mMidpoint) {
        return NodePlacement::Child2;
    }

    return NodePlacement::Self;
}
int KdTreeUtil::DetermineNodePlacementStrictly(KdTreeSplitInfo& rSplitInfo, PointPair& rPoints) {
    if (rSplitInfo.mSplitY) {
        // y axis
        if (rPoints.first.y > rSplitInfo.mMidpoint && rPoints.second.y > rSplitInfo.mMidpoint) {
            return NodePlacement::Child1;
        } else if (
            rPoints.first.y < rSplitInfo.mMidpoint
            && rPoints.second.y < rSplitInfo.mMidpoint
        ) {
            return NodePlacement::Child2;
        }

        return NodePlacement::Self;
    }
    // x axis
    if (rPoints.first.x > rSplitInfo.mMidpoint && rPoints.second.x > rSplitInfo.mMidpoint) {
        return NodePlacement::Child1;
    } else if (rPoints.first.x < rSplitInfo.mMidpoint && rPoints.second.x < rSplitInfo.mMidpoint) {
        return NodePlacement::Child2;
    }
    return NodePlacement::Self;
}

int KdTreeUtil::DetermineNodePlacementByProximity(
    KdTreeSplitInfo& rSplitInfo,
    PointPair& rPoints
) {
    float two;
    float one;

    if (rSplitInfo.mSplitY) {
        // y axis
        one = rPoints.first.y;
        two = rPoints.second.x;

        if (one - two > rSplitInfo.mMidpoint) {
            return NodePlacement::Child1;
        } else if (one + two < rSplitInfo.mMidpoint) {
            return NodePlacement::Child2;
        }

        return NodePlacement::Self;
    }

    // x axis
    two = rPoints.first.x;
    one = rPoints.second.x;

    if (two - one > rSplitInfo.mMidpoint) {
        return NodePlacement::Child1;
    } else if (two + one < rSplitInfo.mMidpoint) {
        return NodePlacement::Child2;
    }

    return NodePlacement::Self;
}

int KdTreeUtil::DetermineNodePlacement(KdTreeSplitInfo& rSplitInfo, PointPair& rPoints) {
    if (rSplitInfo.mSplitY) {
        // y axis

        if (rPoints.first.y > rSplitInfo.mMidpoint) {
            return NodePlacement::Child1;
        } else if (rPoints.second.y < rSplitInfo.mMidpoint) {
            return NodePlacement::Child2;
        }
    
        return NodePlacement::Self;
    }

    // x axis
    
    if (rPoints.first.x > rSplitInfo.mMidpoint) {
        return NodePlacement::Child1;
    } else if (rPoints.second.x < rSplitInfo.mMidpoint) {
        return NodePlacement::Child2;
    }

    return NodePlacement::Self;
}
