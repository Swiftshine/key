#ifndef FLUFF_KEYFRAME_H
#define FLUFF_KEYFRAME_H

#include <string>
#include <vector>
#include "types.h"
#include "gfl/gflArray.h"
#include "gfl/gflPointer.h"

#include "misc/VectorWrapper.h"

/// @note Size: `0x1C`
template <typename T>
class KeyFrame {
public:
    /* Structures */

    struct InnerKeyFrame {
        inline InnerKeyFrame() { }

        inline InnerKeyFrame(T start, T end, const std::string& rName)
            : mStart(start)
            , mEnd(end)
            , mName(rName)
        { }

        T mStart;
        T mEnd;
        std::string mName;
    };

    struct FrameTemplate {
        s32 mCount; // the number of start/end frames the structure uses
        T mStartFrames[8];
        T mEndFrames[8];
        T mDefaultFrame;
    };

    inline KeyFrame()
        : mInnerKeyFrames()
        , mCurrentFrame(0.0f)
        , mIncrementAmount(0.0f)
        , mHasFrames(false)
    { }

    /* Virtual Methods */

    /* 0x8 */ inline virtual ~KeyFrame() { }

    /* 0xC */ virtual void GetNextStartFrame(T mult, u32 index, InnerKeyFrame* pDst);
    // /* 0xC */ virtual void GetNextStartFrame(T mult, u32 index, InnerKeyFrame* pDst) {
    //     T cur = mInnerKeyFrames[index].mStart;
    //     T delta = mInnerKeyFrames[index + 1].mStart - mInnerKeyFrames[index].mStart;
    //     pDst->mStart = mInnerKeyFrames[index].mStart + delta * mult;
    // }

    /* Class Methods */

    void IncrementCurrentFrame(T amount) DONT_INLINE_CLASS {
        T prevEnd;
        T total = mCurrentFrame + amount;
        mCurrentFrame = total;

        if (!mHasFrames) {
            return;
        }

        prevEnd = mInnerKeyFrames.back().mEnd;

        if (total > prevEnd) {
            mCurrentFrame = total - prevEnd;
        }
    }

    // not complete - https://decomp.me/scratch/yjhK1
    T CalculateFrame(T start, std::string* pName) DONT_INLINE_CLASS {
        // T newFrame;

        // if (mHasFrames && GetPreviousEndFrame() < start) {
        //     T prev = GetPreviousEndFrame();

        //     u32 unk = static_cast<unsigned s32>(start / prev);
        //     newFrame = (T)(unk);
        // }

        // u32 c = mInnerKeyFrames.size();
        // u32 i = 0;

        // while (true) {
        //     if (c == 0) {
        //         if (pName != nullptr) {
        //             *pName = mInnerKeyFrames.back().mName;
        //         }
        //     }
        // }

        // if (pName != nullptr) {

        // }

        return 0;
    }

    T GetPreviousEndFrame() DONT_INLINE_CLASS {
        return mInnerKeyFrames.back().mEnd;
    }

    T GetFrame(std::string* pName) DONT_INLINE_CLASS {
        return CalculateFrame(mCurrentFrame, pName);
    }

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

    f32 AdvanceFrame(f32 arg1, std::string* pName = nullptr);
    
    void Add(T start, T end, const char* pName = nullptr) DONT_INLINE_CLASS {
        size_t count = mInnerKeyFrames.size();

        if (count != 0) {
            AddNew(start, end + mInnerKeyFrames[count - 1].mEnd, pName);
        } else {
            AddNew(start, end, pName);
        }
    }

    // https://decomp.me/scratch/hbETT
    void AddNew(T start, T end, const char* pName) DONT_INLINE_CLASS {
        // std::string name;

        // if (pName != nullptr) {
        //     name = pName;
        // }

        // InnerKeyFrame inner;
        // inner.mStart = start;
        // inner.mEnd = end;
        // inner.mName = std::string(name);

        // mInnerKeyFrames.push_back(inner);
    }

    bool IsFinished() const;
    /* Class Members */

    /* 0x04 */ VectorWrapper<InnerKeyFrame> mInnerKeyFrames;
    /* 0x10 */ f32 mCurrentFrame;
    /* 0x14 */ f32 mIncrementAmount;
    /* 0x18 */ bool mHasFrames;
};

#endif
