#include "util/PathInfo.h"

PathInfo::PathInfo(Mapdata::MapdataPath* pPath, bool looped)
    : mPath(pPath)
    , mPathLength(0.0f)
    , mSegments()
    , m_14(0.0f, 0.0f)
    , mNumSegments(0)
    , mIsLooped(looped)
{
    AddPoints();
}

PathInfo::~PathInfo() { }

// https://decomp.me/scratch/S3VP6
gfl::Vec2 PathInfo::GetPointAtPercentage(float percentage) const {
    if (percentage >= 1.0f) {
        // const gfl::Vec2& ret = GetPoint(mNumSegments - 1);
        // return ret;
    }
        
    float targetDist = mPathLength * percentage;
    float curDist = 0.0f;
    float foundDist = 0.0f;
    uint pointIndex = 0;
    float prevDist = 0.0f;

    for (uint i = 0; i < mNumSegments; i++) {
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
gfl::Vec2 PathInfo::fn_802FF9B8(float arg1) const {
    // const gfl::Vec2& vec = fn_802FF9FC(arg1);
    // return gfl::Vec2(vec.x, -vec.y);
    return gfl::Vec2();
}

const nw4r::math::VEC2& PathInfo::GetPoint(int index) const {
    if (IsLooped()) {
        index -= index / mPath->GetNumSegments() * mPath->GetNumSegments();
    } else {
        int last = mPath->GetNumSegments() - 1;

        if (index < 0) {
            index = 0;
        } else if (index > last) {
            index = last;
        }
    }

    return mPath->mPoints[index];
}