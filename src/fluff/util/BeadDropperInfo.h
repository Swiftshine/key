#ifndef FLUFF_BEADDROPPERINFO_H
#define FLUFF_BEADDROPPERINFO_H

#include "types.h"
#include <nw4r/math.h>

// size: 0x1C
class BeadDropperInfo {
public:
    BeadDropperInfo();
    DECL_WEAK ~BeadDropperInfo();
    void Configure(int type, int color, int limit);
    void SpawnBeads(nw4r::math::VEC3& pos, nw4r::math::VEC3& offset);
private:
    int m_0;
    int m_4;
    int mPreferredBeadType;     // @ 0x8; refers to the type of bead that the dropper will try to spawn first if funds are sufficient
    int mBeadColor;             // @ 0xC
    int mRemainingBeadFunds;    // @ 0x10
    int mTotalBeadFunds;        // @ 0x14
    int mNumSpawnedBeads;       // @ 0x18
};

ASSERT_SIZE(BeadDropperInfo, 0x1C);

#endif