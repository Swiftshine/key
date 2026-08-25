#ifndef FLUFF_GMKTURTLE_H
#define FLUFF_GMKTURTLE_H

#include "object/Gimmick.h"
#include "object/PlayerBase.h"
#include "object/collision/ColObj.h"
#include "object/collision/FlfRideHitCtrlTrans.h"
#include "graphics/NwAnmCtrl.h"
#include "misc/ScopedPointers.h"
#include "util/FullSortSceneUtil.h"
#include "manager/Stage.h"
#include <nw4r/math.h>

class GmkUpdownWater;

// size: 0x15C
class GmkTurtle : public Gimmick {
public:
    enum State {
        eState_InWater,
        eState_MoveLeft,
        eState_TurnRight,
        eState_State_3,
        eState_MoveRight,
        eState_TurnLeft,
        eState_State_6,
        eState_State_7,
        eState_State_8,
    };

    enum TurnDirection {
        eTurnDirection_Left,
        eTurnDirection_Right,
    };

    enum Parameter {
        eParameter_NumTurtles = 1, // s32 1
        eParameter_ShouldMoveRight = 2, // s32 (bool) 2

        eParameter_CounterDefaultValue = 0, // float 0
        eParameter_Speed = 1, // float 1
        eParameter_MaxDistance = 2, // float 2

        eParameter_TargetGimmick = 0, // string 0
    };
public:
    static GmkTurtle* Build(GimmickBuildInfo* buildInfo);
    GmkTurtle(GimmickBuildInfo* buildInfo);
    virtual ~GmkTurtle();

    /* FlfGameObj */

    void Interact(FlfGameObj*) override;

    /* Gimmick */
    virtual s32 vf88(FlfGameObj* player, u32 arg2) override;
    virtual s32 vf98() override;
    virtual void Update() override;

    /* GmkTurtle */

    void BecomeActive();

    void Turn(s32 turnDir) DONT_INLINE_CLASS;
public:
    u32 mCounterDefaultValue;
    float mSpeed;
    float mMaxDistance;
    bool mShouldMoveRight;
    bool m_13D;
    u16 m_13E;
    s32 mCounter;
    s32 mNumTurtles;
    s32 mCurrentState;
    GmkUpdownWater* mWater;
    gfl::Pointer<NwAnmCtrl> mAnmCtrl;
    gfl::Pointer<ColObjTrans> mColObjTrans;
    gfl::Pointer<FlfRideHitCtrlTrans> mRideHitCtrlTrans;
};

// ASSERT_SIZE(GmkTurtle, 0x15C)

#endif
