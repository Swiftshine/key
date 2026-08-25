#ifndef FLUFF_BEADDROPPERINFO_H
#define FLUFF_BEADDROPPERINFO_H

#include "types.h"
#include <nw4r/math.h>

/// @note Size: `0x1C`
class BeadDropperInfo {
public:
    

    BeadDropperInfo();
    DECL_WEAK ~BeadDropperInfo();

    /* Class Methods */

    void Configure(s32 type, s32 color, s32 limit);
    void SpawnBeads(nw4r::math::VEC3& rPos, nw4r::math::VEC3& rOffset);

    /* Class Members */

    /* 0x00 */ s32 m_0;
    /* 0x04 */ s32 m_4;
    /// @brief The type of bead the dropper will try to spawn first if funds allow for it.
    /* 0x08 */ s32 mPreferredBeadType;
    /* 0x0C */ s32 mBeadColor;
    /* 0x10 */ s32 mRemainingBeadFunds; 
    /* 0x14 */ s32 mTotalBeadFunds;
    /* 0x18 */ s32 mNumSpawnedBeads;
};

ASSERT_SIZE(BeadDropperInfo, 0x1C);

#endif
