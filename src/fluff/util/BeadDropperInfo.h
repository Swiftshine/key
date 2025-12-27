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

    void Configure(int type, int color, int limit);
    void SpawnBeads(nw4r::math::VEC3& rPos, nw4r::math::VEC3& rOffset);

    /* Class Members */

    /* 0x00 */ int m_0;
    /* 0x04 */ int m_4;
    /// @brief The type of bead the dropper will try to spawn first if funds allow for it.
    /* 0x08 */ int mPreferredBeadType;
    /* 0x0C */ int mBeadColor;
    /* 0x10 */ int mRemainingBeadFunds; 
    /* 0x14 */ int mTotalBeadFunds;
    /* 0x18 */ int mNumSpawnedBeads;
};

ASSERT_SIZE(BeadDropperInfo, 0x1C);

#endif