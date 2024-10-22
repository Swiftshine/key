#include "util/KdTreeUtil.h"

int KdTreeUtil::DetermineNodePlacement(KdTreeSplitInfo& splitInfo, nw4r::math::VEC2& point) {
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
    } else if (coordinate < splitInfo.mMidpoint) {
        return NodePlacement::Child2;
    }

    return NodePlacement::Self;
}
int KdTreeUtil::DetermineNodePlacementStrictly(KdTreeSplitInfo& splitInfo, PointPair& points) {
    if (splitInfo.mSplitY) {
        // y axis
        if (points.first.y > splitInfo.mMidpoint && points.second.y > splitInfo.mMidpoint) {
            return NodePlacement::Child1;
        } else if (points.first.y < splitInfo.mMidpoint && points.second.y < splitInfo.mMidpoint) {
            return NodePlacement::Child2;
        }

        return NodePlacement::Self;
    }
    // x axis
    if (points.first.x > splitInfo.mMidpoint && points.second.x > splitInfo.mMidpoint) {
        return NodePlacement::Child1;
    } else if (points.first.x < splitInfo.mMidpoint && points.second.x < splitInfo.mMidpoint) {
        return NodePlacement::Child2;
    }
    return NodePlacement::Self;
}

int KdTreeUtil::DetermineNodePlacementByProximity(KdTreeSplitInfo& splitInfo, PointPair& points) {
    float two;
    float one;

    if (splitInfo.mSplitY) {
        // y axis
        one = points.first.y;
        two = points.second.x;

        if (one - two > splitInfo.mMidpoint) {
            return NodePlacement::Child1;
        } else if (one + two < splitInfo.mMidpoint) {
            return NodePlacement::Child2;
        }

        return NodePlacement::Self;
    }

    // x axis
    two = points.first.x;
    one = points.second.x;

    if (two - one > splitInfo.mMidpoint) {
        return NodePlacement::Child1;
    } else if (two + one < splitInfo.mMidpoint) {
        return NodePlacement::Child2;
    }

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
