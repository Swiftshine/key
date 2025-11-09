#ifndef FLUFF_KEYFRAME_H
#define FLUFF_KEYFRAME_H

#include <string>
#include <vector>
#include "types.h"
#include "gfl/gflArray.h"
#include "gfl/gflPointer.h"

/// @note Size: `0x1C`
template <typename T>
class KeyFrame {
public:
    /* Structures */
    
    struct InnerKeyFrame {
        T mStart;
        T mEnd;
        std::string mName;
    };


    struct FrameTemplate {
        int mCount; // the number of start/end frames the structure uses
        T mStartFrames[8];
        T mEndFrames[8];
        T mDefaultFrame;
    };
    
    /* Constructor */

    inline KeyFrame()
        : mInnerKeyFrames()
        , mCurrentFrame(0.0f)
        , mIncrementAmount(0.0f)
        , mHasFrames(false)
    { }

    /* Virtual Methods */

    /* 0x8 */ inline virtual ~KeyFrame() { }
    /* 0xC */ void GetNextStartFrame(T mult, uint index, InnerKeyFrame* pDst);

    /* Class Methods */

    void IncrementCurrentFrame(T amount);
    
    void Add(T start, T end, const char* pName = nullptr);
    void AddNew(T start, T end, const char* pName);
    T GetFrame(std::string* pString);
    T CalculateFrame(T start, std::string* pName);
    T GetPreviousEndFrame();

    inline void Reset() {
        mInnerKeyFrames.clear();
        mCurrentFrame = 0;
        mHasFrames = false;
    }

    inline size_t Count() {
        return mInnerKeyFrames.size();
    }

    inline void IncrementCurrentFrame() {
        IncrementCurrentFrame(mIncrementAmount);
    }

    /* Class Members */

    /* 0x04 */ std::vector<InnerKeyFrame> mInnerKeyFrames;
    /* 0x10 */ T mCurrentFrame;
    /* 0x14 */ T mIncrementAmount;
    /* 0x18 */ bool mHasFrames;
};

#endif
