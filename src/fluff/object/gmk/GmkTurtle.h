#ifndef FLUFF_GMKTURTLE_H
#define FLUFF_GMKTURTLE_H

#include "object/Gimmick.h"
#include "object/PlayerBase.h"
#include "graphics/NwAnmCtrl.h"
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

public:
    GmkTurtle(GimmickBuildInfo* buildInfo);
    virtual ~GmkTurtle();

    /* FlfGameObj */

    void vf24() override;

    /* Gimmick */
    virtual int vfA4() override;
    virtual bool vf88(FlfGameObj* player, uint arg2) override;
    virtual void Update() override;

    /* GmkTurtle */
    
    void BecomeActive();

    void Turn(int turnDir);
public:
    int mCounterDefaultValue;
    float mSpeed;
    float mMaxDistance;
    bool m_13C;
    bool m_13D;
    u16 m_13E;
    int mCounter;
    int mNumTurtles;
    int mCurrentState;
    Gimmick* mWater;
    class NwAnmCtrl* mAnmCtrl;
    class ColObjTrans* mColObjTrans;
    class RideHitCtrlTrans* mRideHitCtrlTrans;
};

// ASSERT_SIZE(GmkTurtle, 0x15C)

#endif
