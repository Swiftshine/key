#ifndef FLUFF_COLBIN_H
#define FLUFF_COLBIN_H


#include "types.h"
#include <nw4r/math.h>

namespace Colbin {

struct Header {
    /* 0x0 */ float m_0;
    /* 0x4 */ u32 mNumEntries;
    /* 0x8 */ u32 mEntryOffset;
    /* 0xC */ u32 mFooterOffset;
};

struct Entry {
    /* 0x0 */ nw4r::math::VEC2 mStart;
    /* 0x8 */ nw4r::math::VEC2 mEnd;
    /* 0x10 */ nw4r::math::VEC2 m_10;
    /* 0x18 */ u32 mEntryIndex;
    /* 0x1C */ u32 mCollisionTypeIndex;
};

// variable length structure
struct Footer {
    u32 mNumCollisionTypes;
    /* string32[mNumCollisionTypes] */
};

// file is padded to next offset of 0x20
}

#endif
