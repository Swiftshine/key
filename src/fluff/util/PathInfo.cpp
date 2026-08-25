#include "util/PathInfo.h"

PathInfo::PathInfo(Mapdata::MapdataPath* pPath, bool looped)
    : mPath(pPath)
    , mPathLength(0.0f)
    , mSegments()
    , m_14(0.0f)
    , m_18(0.0f)
    , mNumSegments(0)
    , mIsLooped(looped)
{
    AddPoints();
}

PathInfo::~PathInfo() { }

// https://decomp.me/scratch/S3VP6
gfl::Vec2 PathInfo::GetPointAtPercentage(f32 percentage) const {
    if (percentage >= 1.0f) {
        // const gfl::Vec2& ret = GetPoint(mNumSegments - 1);
        // return ret;
    }
        
    f32 targetDist = mPathLength * percentage;
    f32 curDist = 0.0f;
    f32 foundDist = 0.0f;
    u32 pointIndex = 0;
    f32 prevDist = 0.0f;

    for (u32 i = 0; i < mNumSegments; i++) {
        if (targetDist < curDist) {
            foundDist = targetDist - prevDist;
            pointIndex = i;
            break;
        }

        prevDist = curDist;
        curDist += mSegments[i].mLength;
    }


    const PathSegment* seg = &mSegments[pointIndex];
    
    gfl::Vec2 ret(seg->mDirX * foundDist, seg->mDirY * foundDist);

    ret += GetPoint(pointIndex);
    // gfl::Vec2 ret(point.x + seg->mDirX * foundDist, point.y + seg->mDirY * foundDist);
    // ret.x = (point.x + seg->mDirX) * foundDist;
    // ret.y = (point.y + seg->mDirY) * foundDist;
    return ret;
}

// https://decomp.me/scratch/nqqF8
// i hate this compiler
gfl::Vec2 PathInfo::fn_802FF9B8(f32 arg1) const {
    // const gfl::Vec2& vec = fn_802FF9FC(arg1);
    // return gfl::Vec2(vec.x, -vec.y);
    return gfl::Vec2();
}

f32 PathInfo::GetPathLength() const {
    return mPathLength;
}

void PathInfo::fn_802FFC04() {
    m_14 = 0.0f;
    m_18 = 0.0f;
}

bool PathInfo::fn_802FFC14() const {
    if (IsLooped()) {
        return false;
    }

    return m_14 <= 0.0f;
}


bool PathInfo::fn_802FFC68() const {
    if (IsLooped()) {
        return false;
    }

    return m_14 >= 1.0f;
}

bool PathInfo::IsLooped() const {
    return mIsLooped;
}

void PathInfo::fn_80300214(f32 arg1) {
    f32 val = (f32)mPathLength * (f32)(double)arg1;
    m_14 = arg1;
    m_18 = val;
}

const nw4r::math::VEC2& PathInfo::GetPoint(s32 index) const {
    if (IsLooped()) {
        index -= index / mPath->GetNumSegments() * mPath->GetNumSegments();
    } else {
        s32 last = mPath->GetNumSegments() - 1;

        if (index < 0) {
            index = 0;
        } else if (index > last) {
            index = last;
        }
    }

    return mPath->mPoints[index];
}
