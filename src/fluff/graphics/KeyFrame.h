#ifndef FLUFF_KEYFRAME_H
#define FLUFF_KEYFRAME_H

#include "types.h"

template <typename T>
class KeyFrame {
public:
    inline KeyFrame() {
        m_4 = nullptr;
        m_8 = nullptr;
        m_C = nullptr;
        mFirst = 0.0f;
        mSecond = 0.0f;
    }

    inline virtual ~KeyFrame();
private:
    void* m_4;
    int m_8;
    void* m_C;
    // these fields are guessed
    T mFirst;
    T mSecond;
};

#endif
