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
        /* 0x10 */ gfl::Vec2 mMatrixTranslation;
        /* 0x18 */ s32 m_18;
        /* 0x1C */ u32 m_1C;
        /* 0x20 */ f32 m_20;
        /* 0x24 */ f32 m_24;
        /* 0x28 */ f32 m_28;
        /* 0x2C */ f32 m_2C;
        /* 0x30 */ u32 mSortSceneID;
        /* 0x34 */ bool m_34;
        /* 0x38 */ gfl::Vec2 mPosition;
    };

    ASSERT_SIZE(Layer, 0x40);
}


#endif
