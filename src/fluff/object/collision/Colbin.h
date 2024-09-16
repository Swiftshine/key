#ifndef FLUFF_COLBIN_H
#define FLUFF_COLBIN_H

#include "gfl/gflVec2.h"
#include "types.h"

namespace Colbin {
    struct Header {
        float m_0;
        u32 mNumEntries;
        u32 mEntryOffset;
        u32 mFooterOffset;
    };

    struct Entry {
        gfl::Vec2 mStart;
        gfl::Vec2 mEnd;
        gfl::Vec2 m_10;
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
