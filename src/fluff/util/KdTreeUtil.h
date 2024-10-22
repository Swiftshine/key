#ifndef FLUFF_KDTREEUTIL_H
#define FLUFF_KDTREEUTIL_H


#include "types.h"
#include <utility>

#include <nw4r/math.h>

typedef std::pair<bool, float> SplitInfo;
typedef std::pair<nw4r::math::VEC2, nw4r::math::VEC2> PointPair;

struct KdTreeSplitInfo {
    bool mSplitY;
    float mMidpoint;
};

struct KdTreeBounds {
    inline KdTreeBounds() {
        mMinX = 0.0f;
        mMinY = 0.0f;
        mMaxX = 0.0f;
        mMaxY = 0.0f;
    }
    
    float mMinX;
    float mMinY;
    float mMaxX;
    float mMaxY;
};

// todo: find better names for these functions

namespace KdTreeUtil {
    ENUM_CLASS(NodePlacement,
        Child1 = 0,
        Child2 = 1,
        Self = 2
    );

    /**
     * @note Address: 0x80048354
     * @note Size: 0x64
     */
    int DetermineNodePlacement(KdTreeSplitInfo& splitInfo, nw4r::math::VEC2& point);

    /**
     * @note Address: 0x800483b8
     * @note Size: 0x64
     */

    int DetermineNodePlacementStrictly(KdTreeSplitInfo& splitInfo, PointPair& points);

    /**
     * @note Address: 0x80048464
     * @note Size: 0x84
     */
    int DetermineNodePlacementByProximity(KdTreeSplitInfo& splitInfo, PointPair& points);

    /**
     * @note Address: 0x800484e8
     * @note Size: 0x74
     */
    int DetermineNodePlacement(KdTreeSplitInfo& splitInfo, PointPair& points);
}


#endif
