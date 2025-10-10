#ifndef FLUFF_KEYFRAME_H
#define FLUFF_KEYFRAME_H

#include "types.h"

template <typename T>
class KeyFrame {
public:
    /* Constructor */

    inline KeyFrame() {
        m_4 = nullptr;
        m_8 = nullptr;
        m_C = nullptr;
        mFirst = 0.0f;
        mSecond = 0.0f;
    }

    /* Virtual Methods */

    /* 0x08 */ inline virtual ~KeyFrame();

    /* Class Members */

    /* 0x04 */ void* m_4;
    /* 0x08 */ int m_8;
    /* 0x0C */ void* m_C;
    /* 0x10 */ T mFirst;
    /* ???? */ T mSecond;
};

#endif
