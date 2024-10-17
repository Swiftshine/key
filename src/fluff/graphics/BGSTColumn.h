#ifndef FLUFF_BGSTCOLUMN_H
#define FLUFF_BGSTCOLUMN_H

#include "types.h"

namespace BGST {

    struct Column {
        ENUM_CLASS(Type,
            Shadowless = -2u,
        );

        u16 m_0;
        u16 m_2;
        u16 m_4;
        u16 m_6;
        u16 m_8;
        u16 mType;
        u16 mImageIndex;
        u16 mShadowImageIndex;
    };

    ASSERT_SIZE(Column, 0x10);
}

#endif
