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
    struct Substruct2;

    struct Substruct1 {
        Substruct1() 
            : mSub(nullptr)
            , mCount(0)
        { }

        ~Substruct1();
        void Clear(int);

        Substruct2* mSub;
        int mCount;
    };

    // these are required for matching
    struct Dummy1 : Substruct1 { };
    struct Dummy2 : Dummy1 { };

    struct Substruct2 {
        int m_0;
        int m_4;
        std::string mName;
    };

    /* Constructor */

    inline KeyFrame()
        : m_4()
        , m_C(0)
        , mPrev(0.0f)
        , mNext(0.0f)
        , mEnabled(false)
    { }

    /* Virtual Methods */

    /* 0x8 */ inline virtual ~KeyFrame() { }

    /* 0xC */ void vfC();

    /* Class Members */

    // one of these types must be a T*

    /* 0x04 */ Dummy2 m_4;
    /* 0x0C */ int m_C;
    /* 0x10 */ float mPrev;
    /* 0x14 */ float mNext;
    /* 0x18 */ bool mEnabled;
};

#endif
