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

// https://decomp.me/scratch/342yv
// nw4r::math::VEC2 PathInfo::GetPointAtPercentage(float percentage) const {
    //     if (percentage >= 1.0f) {
        //         nw4r::math::VEC2 ret = GetPoint(mNumPoints - 1);
        //         return ret;
        //     }
        
        //     float targetDist = mPathLength * percentage;
        //     float curDist = 0.0f;
        //     float foundDist = 0.0f;
        //     uint pointIndex = 0;
        //     float prevDist = 0.0f;
        
        //     for (uint i = 0; i < mNumPoints; i++) {
            //         if (targetDist < curDist) {
                //             foundDist = targetDist - prevDist;
                //             pointIndex = i;
                //             break;
//         }

//         prevDist = curDist;
//         curDist += mSegments[i].mLength;
//     }


//     const PathSegment* seg = &mSegments[pointIndex];

//     nw4r::math::VEC2 ret;

//     const nw4r::math::VEC2& point = GetPoint(pointIndex);

//     ret.x = point.x + seg->mDirX * foundDist;
//     ret.y = point.y + seg->mDirY * foundDist;

//     return ret;
// }

// https://decomp.me/scratch/20SxI
// i hate this compiler
// nw4r::math::VEC2 PathInfo::fn_802FF9B8(float arg1) const {

// }

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