#ifndef FLUFF_BGSTENTRYINFO_H
#define FLUFF_BGSTENTRYINFO_H

#include "types.h"

namespace BGST {

    struct EntryInfo {
        ENUM_CLASS(Type,
            Shadowless = -2u,
        );

        /* 0x00 */ u16 m_0;
        /* 0x02 */ u16 m_2;
        /* 0x04 */ u16 m_4;
        /* 0x06 */ u16 m_6;
        /* 0x08 */ u16 m_8;
        /* 0x0A */ u16 mType;
        /* 0x0C */ u16 mImageIndex;
        /* 0x0E */ u16 mShadowImageIndex;
    };

    ASSERT_SIZE(EntryInfo, 0x10);
}

#endif
