#ifndef FLUFF_BGSTLAYER_H
#define FLUFF_BGSTLAYER_H

#include "types.h"
#include <nw4r/math.h>
#include "gfl/gflVec3.h"
#include "gfl/gflVec2.h"

class BgImage2;

namespace BGST {
    class File;

    struct Layer {
        /* 0x00 */ bool mEnabled;
        /* 0x04 */ u32 m_4;
        /* 0x08 */ File* mBGSTFile;
        /* 0x0C */ BgImage2* mBgImage;
        /* 0x10 */ gfl::Vec3 mMatrixTranslation;
        /* 0x1C */ u32 m_1C;
        /* 0x20 */ float m_20;
        /* 0x24 */ float m_24;
        /* 0x28 */ float m_28;
        /* 0x2C */ float m_2C;
        /* 0x30 */ uint mSortSceneID;
        /* 0x34 */ bool m_34;
        /* 0x38 */ gfl::Vec2 mPosition;
    };

    ASSERT_SIZE(Layer, 0x40);
}


#endif
