#ifndef FLUFF_ENEMYBASE_H
#define FLUFF_ENEMYBASE_H

#include "types.h"
#include "object/FlfGameObj.h"
#include "demo/EventDemoAttachment.h"
#include "object/collision/IObjHitCB.h"
#include "object/MoveTarget.h"

class EnemyBase : public FlfGameObj, public IObjHitCB {
public:
    virtual ~EnemyBase();
private:
    demo::EventDemoAttachment* mDemoAttachment; // @ 0x84
    int m_98;
    int m_9C;
    int m_A0;
    int m_A4;
    int m_A8;
    int m_AC;
    int m_B0;
    nw4r::math::VEC3 m_B4;
    int m_C0;
    int m_C4;
    int m_C8;
    int m_CC;
    int m_D0;
    int m_D4;
    int m_D8;
    int m_DC;
    int m_E0;
    int m_E4;
    int m_E8;
    int m_EC;
    MoveTarget mMoveTargets[2]; // @ 0xF0
    int m_180;
    int m_184;
    int m_18C;
    int m_190;
    nw4r::math::MTX44 m_194;
    nw4r::math::VEC2 m_1D4;
    nw4r::math::VEC2 m_1DC;
    STRUCT_FILL(0x1774 - 464);
};

const int size = sizeof(EnemyBase);

ASSERT_SIZE(EnemyBase, 0x1774);

#endif
