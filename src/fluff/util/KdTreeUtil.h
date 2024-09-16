#ifndef FLUFF_KDTREEUTIL_H
#define FLUFF_KDTREEUTIL_H


#include "types.h"
#include <utility>
#include "gfl/gflVec2.h"

typedef std::pair<bool, float> SplitInfo;
typedef std::pair<gfl::Vec2, gfl::Vec2> PointPair;

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
    int DetermineNodePlacement(SplitInfo& splitInfo, gfl::Vec2& point);
    int DetermineNodePlacementStrictly(SplitInfo& splitInfo, PointPair& points);
    int DetermineNodePlacementByProximity(SplitInfo& splitInfo, PointPair& points);
    int DetermineNodePlacement(SplitInfo& splitInfo, PointPair& points);
}


#endif
