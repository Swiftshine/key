#ifndef FLUFF_KEYFRAME_H
#define FLUFF_KEYFRAME_H

#include <string>
#include "types.h"
#include "gfl/gflArray.h"
#include "gfl/gflPointer.h"
/// @note Size: `0x1C`
template <typename T>
class KeyFrame {
public:
    /* Structures */

    // none of the below structures are known for sure
    struct InnerKeyFrame;

    struct FrameHolder {
        FrameHolder() 
            : mInnerKeyFrames(nullptr)
            , mCount(0)
        { }

        ~FrameHolder();
        void Clear(int);

        InnerKeyFrame* mInnerKeyFrames;
        int mCount;
    };

    // these are required for matching
    struct Dummy1 : FrameHolder { };
    struct Dummy2 : Dummy1 { };

    struct InnerKeyFrame {
        T m_0;
        T m_4;
        std::string mName;
    };

    /* Constructor */

    inline KeyFrame()
        : mFrameHolder()
        , m_C(0)
        , mCurrentFrame(0.0f)
        , mIncrementAmount(0.0f)
        , mEnabled(false)
    { }

    /* Virtual Methods */

    /* 0x8 */ inline virtual ~KeyFrame() { }
    /* 0xC */ void vfC();

    /* Class Methods */
    void IncrementCurrentFrame(float amount);

    /* Class Members */

    /* 0x04 */ Dummy2 mFrameHolder;
    /* 0x0C */ int m_C;
    /* 0x10 */ float mCurrentFrame;
    /* 0x14 */ float mIncrementAmount;
    /* 0x18 */ bool mEnabled;
};

#endif
