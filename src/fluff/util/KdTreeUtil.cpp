#include "util/KdTreeUtil.h"

s32 KdTreeUtil::DetermineNodePlacement(KdTreeSplitInfo& rSplitInfo, nw4r::math::VEC2& point) {
    f32 coordinate;
    if (rSplitInfo.mSplitY) {
        // the node is split on the Y axis
        coordinate = point.y;

        if (coordinate > rSplitInfo.mMidpoint) {
            return KdTreeUtil::eNodePlacement_Child1;
        } else if (coordinate < rSplitInfo.mMidpoint) {
            return KdTreeUtil::eNodePlacement_Child2;
        }

        return KdTreeUtil::eNodePlacement_Self;
    }

    // the node is split on the X axis
    coordinate = point.x;
    if (coordinate > rSplitInfo.mMidpoint) {
        return KdTreeUtil::eNodePlacement_Child1;
    } else if (coordinate < rSplitInfo.mMidpoint) {
        return KdTreeUtil::eNodePlacement_Child2;
    }

    return KdTreeUtil::eNodePlacement_Self;
}
s32 KdTreeUtil::DetermineNodePlacementStrictly(KdTreeSplitInfo& rSplitInfo, PointPair& rPoints) {
    if (rSplitInfo.mSplitY) {
        // y axis
        if (rPoints.first.y > rSplitInfo.mMidpoint && rPoints.second.y > rSplitInfo.mMidpoint) {
            return KdTreeUtil::eNodePlacement_Child1;
        } else if (
            rPoints.first.y < rSplitInfo.mMidpoint
            && rPoints.second.y < rSplitInfo.mMidpoint
        ) {
            return KdTreeUtil::eNodePlacement_Child2;
        }

        return KdTreeUtil::eNodePlacement_Self;
    }
    // x axis
    if (rPoints.first.x > rSplitInfo.mMidpoint && rPoints.second.x > rSplitInfo.mMidpoint) {
        return KdTreeUtil::eNodePlacement_Child1;
    } else if (rPoints.first.x < rSplitInfo.mMidpoint && rPoints.second.x < rSplitInfo.mMidpoint) {
        return KdTreeUtil::eNodePlacement_Child2;
    }
    return KdTreeUtil::eNodePlacement_Self;
}

s32 KdTreeUtil::DetermineNodePlacementByProximity(
    KdTreeSplitInfo& rSplitInfo,
    PointPair& rPoints
) {
    f32 two;
    f32 one;

    if (rSplitInfo.mSplitY) {
        // y axis
        one = rPoints.first.y;
        two = rPoints.second.x;

        if (one - two > rSplitInfo.mMidpoint) {
            return KdTreeUtil::eNodePlacement_Child1;
        } else if (one + two < rSplitInfo.mMidpoint) {
            return KdTreeUtil::eNodePlacement_Child2;
        }

        return KdTreeUtil::eNodePlacement_Self;
    }

    // x axis
    two = rPoints.first.x;
    one = rPoints.second.x;

    if (two - one > rSplitInfo.mMidpoint) {
        return KdTreeUtil::eNodePlacement_Child1;
    } else if (two + one < rSplitInfo.mMidpoint) {
        return KdTreeUtil::eNodePlacement_Child2;
    }

    return KdTreeUtil::eNodePlacement_Self;
}

s32 KdTreeUtil::DetermineNodePlacement(KdTreeSplitInfo& rSplitInfo, PointPair& rPoints) {
    if (rSplitInfo.mSplitY) {
        // y axis

        if (rPoints.first.y > rSplitInfo.mMidpoint) {
            return KdTreeUtil::eNodePlacement_Child1;
        } else if (rPoints.second.y < rSplitInfo.mMidpoint) {
            return KdTreeUtil::eNodePlacement_Child2;
        }

        return KdTreeUtil::eNodePlacement_Self;
    }

    // x axis

    if (rPoints.first.x > rSplitInfo.mMidpoint) {
        return KdTreeUtil::eNodePlacement_Child1;
    } else if (rPoints.second.x < rSplitInfo.mMidpoint) {
        return KdTreeUtil::eNodePlacement_Child2;
    }

    return KdTreeUtil::eNodePlacement_Self;
}
