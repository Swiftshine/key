#ifndef FLUFF_GMKTURTLE_H
#define FLUFF_GMKTURTLE_H

#include "object/Gimmick.h"
#include "object/PlayerBase.h"
#include "object/collision/ColObj.h"
#include "object/collision/FlfRideHitCtrlTrans.h"
#include "graphics/NwAnmCtrl.h"
#include "misc/ScopedPointers.h"
#include "util/FullSortSceneUtil.h"
#include "manager/StageManager.h"
#include <nw4r/math.h>

class GmkUpdownWater;

// size: 0x15C
class GmkTurtle : public Gimmick {
public:
    ENUM_CLASS(State,
        InWater,
        MoveLeft,
        TurnRight,
        State_3,
        MoveRight,
        TurnLeft,
        State_6,
        State_7,
        State_8,
    );

    ENUM_CLASS(TurnDirection,
        Left,
        Right,
    );

    ENUM_CLASS(Parameter,
        NumTurtles = 1, // int 1
        ShouldMoveRight = 2, // int (bool) 2

        CounterDefaultValue = 0, // float 0
        Speed = 1, // float 1
        MaxDistance = 2, // float 2

        TargetGimmick = 0, // string 0
    );

public:
    static GmkTurtle* Build(GimmickBuildInfo* buildInfo);
    GmkTurtle(GimmickBuildInfo* buildInfo);
    virtual ~GmkTurtle();

    /* FlfGameObj */

    void Interact(FlfGameObj*) override;

    /* Gimmick */
    virtual int vf88(FlfGameObj* player, uint arg2) override;
    virtual int vf98() override;
    virtual void Update() override;

    /* GmkTurtle */
    
    void BecomeActive();

    void Turn(int turnDir) DONT_INLINE_CLASS;
public:
    uint mCounterDefaultValue;
    float mSpeed;
    float mMaxDistance;
    bool mShouldMoveRight;
    bool m_13D;
    u16 m_13E;
    int mCounter;
    int mNumTurtles;
    int mCurrentState;
    GmkUpdownWater* mWater;
    gfl::Pointer<NwAnmCtrl> mAnmCtrl;
    gfl::Pointer<ColObjTrans> mColObjTrans;
    gfl::Pointer<FlfRideHitCtrlTrans> mRideHitCtrlTrans;
};

// ASSERT_SIZE(GmkTurtle, 0x15C)

#endif
