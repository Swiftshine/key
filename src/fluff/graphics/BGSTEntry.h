#ifndef FLUFF_BGSTENTRY_H
#define FLUFF_BGSTENTRY_H

#include "types.h"
#include "gfl/gflVec2.h"
#include "gfl/gflVec3.h"

class BgImage2;

namespace BGST {
    class Entry {
    private:
        bool m_0;
        u32 m_4;
        u32 m_8;
        BgImage2* mBgImage;
        gfl::Vec3 mMatrixTranslation;
        u32 m_1C;
        float m_20;
        float m_24;
        float m_28;
        float m_2C;
        uint mSortSceneID;
        bool m_34;
        gfl::Vec2 mPosition;
    };

    ASSERT_SIZE(Entry, 0x40);
}


#endif
