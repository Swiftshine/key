#ifndef FLUFF_KDTREEUTIL_H
#define FLUFF_KDTREEUTIL_H


#include "types.h"
#include <utility>
#include "gfl/gflVec2.h"

typedef std::pair<bool, float> SplitInfo;
typedef std::pair<gfl::Vec2, gfl::Vec2> PointPair;

struct KdTreeSplitInfo {
    bool mSplitY;
    float mMidpoint;
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
    int DetermineNodePlacement(KdTreeSplitInfo& splitInfo, gfl::Vec2& point);

    /**
     * @note Address: 0x800483b8
     * @note Size: 0x64
     */

    int DetermineNodePlacementStrictly(KdTreeSplitInfo& splitInfo, PointPair& points);
    
    int DetermineNodePlacementByProximity(KdTreeSplitInfo& splitInfo, PointPair& points);

    /**
     * @note Address: 0x800484e8
     * @note Size: 0x74
     */
    int DetermineNodePlacement(KdTreeSplitInfo& splitInfo, PointPair& points);
}


#endif
