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
    PathInfo(Mapdata::MapdataPath* pPath, bool looped);
    ~PathInfo();

    /* Class Methods */
    gfl::Vec2 GetPointAtPercentage(float percentage) const;
    gfl::Vec2 fn_802FF9B8(float) const;

    void fn_802FF9FC(gfl::Vec2&) const;
    
    float GetPathLength() const;
    void fn_802FFC04();
    bool fn_802FFC14() const;
    bool fn_802FFC68() const;
    bool IsLooped() const;
    void fn_80300214(float arg1);

    void AddPoints();
    const nw4r::math::VEC2& GetPoint(int index) const;

    /* Class Members */

    /* 0x00 */ Mapdata::MapdataPath* mPath;
    /* 0x04 */ float mPathLength;
    /* 0x08 */ VectorWrapper<PathSegment> mSegments;
    /* 0x14 */ float m_14;
    /* 0x18 */ float m_18;
    /* 0x1C */ int mNumSegments;
    /* 0x20 */ bool mIsLooped;
};

#endif
