#ifndef FLUFF_KDTREEUTIL_H
#define FLUFF_KDTREEUTIL_H


#include "types.h"
#include <utility>

#include <nw4r/math.h>

typedef std::pair<bool, float> SplitInfo;
typedef std::pair<nw4r::math::VEC2, nw4r::math::VEC2> PointPair;

/// @note Size: `0x8`
struct KdTreeSplitInfo {
    /* 0x0 */ bool mSplitY;
    /* 0x4 */ float mMidpoint;
};

struct KdTreeBounds {
    inline KdTreeBounds() {
        mMinX = 0.0f;
        mMinY = 0.0f;
        mMaxX = 0.0f;
        mMaxY = 0.0f;
    }
    
    /* 0x0 */ float mMinX;
    /* 0x4 */ float mMinY;
    /* 0x8 */ float mMaxX;
    /* 0xC */ float mMaxY;
};

namespace KdTreeUtil {
    ENUM_CLASS(NodePlacement,
        Child1  = 0,
        Child2  = 1,
        Self    = 2
    );

    /**
     * @note Address: 0x80048354
     * @note Size: 0x64
     */
    int DetermineNodePlacement(KdTreeSplitInfo& rSplitInfo, nw4r::math::VEC2& rPoint);

    /**
     * @note Address: 0x800483b8
     * @note Size: 0x64
     */

    int DetermineNodePlacementStrictly(KdTreeSplitInfo& rSplitInfo, PointPair& rPoints);

    /**
     * @note Address: 0x80048464
     * @note Size: 0x84
     */
    int DetermineNodePlacementByProximity(KdTreeSplitInfo& rSplitInfo, PointPair& rPoints);

    /**
     * @note Address: 0x800484e8
     * @note Size: 0x74
     */
    int DetermineNodePlacement(KdTreeSplitInfo& rSplitInfo, PointPair& rPoints);
}


#endif
