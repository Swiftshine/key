#ifndef FLUFF_COLBIN_H
#define FLUFF_COLBIN_H


#include "types.h"
#include <nw4r/math.h>

namespace Colbin {
    struct Header {
        float m_0;
        u32 mNumEntries;
        u32 mEntryOffset;
        u32 mFooterOffset;
    };

    struct Entry {
        nw4r::math::VEC2 mStart;
        nw4r::math::VEC2 mEnd;
        nw4r::math::VEC2 m_10;
        u32 mEntryIndex;
        u32 mCollisionTypeIndex;
    };

    // variable length structure
    struct Footer {
        u32 mNumCollisionTypes;
        /* string32[mNumCollisionTypes] */
    };

    // file is padded to next offset of 0x20
}

#endif
