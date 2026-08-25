#ifndef FLUFF_PATHINFO_H
#define FLUFF_PATHINFO_H

#include "misc/VectorWrapper.h"
#include "mapdata/Mapdata.h"

struct PathSegment {
    f32 mLength;
    f32 mDirX; // x offs
    f32 mDirY; // y offs
};

/// @note Size: `0x24`
class PathInfo {
public:
    PathInfo(Mapdata::MapdataPath* pPath, bool looped);
    ~PathInfo();

    /* Class Methods */
    gfl::Vec2 GetPointAtPercentage(f32 percentage) const;
    gfl::Vec2 fn_802FF9B8(f32) const;

    void fn_802FF9FC(gfl::Vec2&) const;
    
    f32 GetPathLength() const;
    void fn_802FFC04();
    bool fn_802FFC14() const;
    bool fn_802FFC68() const;
    bool IsLooped() const;
    void fn_80300214(f32 arg1);

    void AddPoints();
    const nw4r::math::VEC2& GetPoint(s32 index) const;

    /* Class Members */

    /* 0x00 */ Mapdata::MapdataPath* mPath;
    /* 0x04 */ f32 mPathLength;
    /* 0x08 */ VectorWrapper<PathSegment> mSegments;
    /* 0x14 */ f32 m_14;
    /* 0x18 */ f32 m_18;
    /* 0x1C */ s32 mNumSegments;
    /* 0x20 */ bool mIsLooped;
};

#endif
