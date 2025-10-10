#ifndef FLUFF_ENEMY76_H
#define FLUFF_ENEMY76_H

#include "object/EnemyBase.h"
#include "object/callback/ScnMdlCallbackBase.h"

class Enemy76MatrixCallback : public ScnMdlCallbackBase {
private:
    u32 m_14;
    u32 m_18;
};

ASSERT_SIZE(Enemy76MatrixCallback, 0x1C);

/// @brief An odd-looking smiley face.
/// @note Size: `0x17C0`
class Enemy76 : public EnemyBase {
public:
    /* Class Members */

    /* 0x1774 */ nw4r::math::MTX34 mMatrix; // @ 0x1774
    /* 0x17A4 */ Enemy76MatrixCallback mMatrixCallback; // @ 0x17A4
};

// ASSERT_SIZE(Enemy76, 0x17C0);


#endif
