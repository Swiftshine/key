#ifndef FLUFF_PATHINFO_H
#define FLUFF_PATHINFO_H

#include "misc/VectorWrapper.h"
#include "mapdata/Mapdata.h"

struct PathSegment {
    float mLength;
    float mDirX; // x offs
    float mDirY; // y offs
};

/// @note Size: `0x24`
class PathInfo {
public:
    PathInfo(Mapdata::MapdataPath* pPath, bool arg2);
    ~PathInfo();

    /* Class Methods */
    nw4r::math::VEC2 GetPointAtPercentage(float percentage) const;
    nw4r::math::VEC2 fn_802FF9B8(float) const;

    
    bool fn_802FFCBC() const;
    const nw4r::math::VEC2& fn_802FF9FC(float) const;
    void AddPoints();
    const nw4r::math::VEC2& GetPoint(int index) const;

    /* Class Members */

    /* 0x00 */ Mapdata::MapdataPath* mPath;
    /* 0x04 */ float mPathLength;
    /* 0x08 */ VectorWrapper<PathSegment> mSegments;
    /* 0x14 */ nw4r::math::VEC2 m_14;
    /* 0x1C */ int mNumSegments;
    /* 0x20 */ bool m_20;
};

#endif