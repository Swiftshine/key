#ifndef FLUFF_GMKTURTLE_H
#define FLUFF_GMKTURTLE_H

#include <game/object/Gimmick.h>
#include <game/object/PlayerBase.h>

// size: 0x15C


class GmkTurtle : public Gimmick {
public:
    SCOPED_ENUM(State,
        State_0,
        MoveLeft,
        TurnRight,
        State_3,
        MoveRight,
        TurnLeft,
        State_6,
        State_7,
        State_8,
    );

public:
    GmkTurtle(GimmickBuildInfo* buildInfo);
    virtual ~GmkTurtle();

    void vf24() override;

    int OnPlayerCollision(PlayerBase* player) override;

    void Update() override;

    void fn_804FB1D4();
public:
    int mCounterDefaultValue;
    f32 mSpeed;
    f32 m_138;
    bool m_13C;
    bool m_13D;
    u16 m_13E;
    int mCounter;
    int mNumTurtles;
    int mCurrentState;
    Gimmick* mpWater;
    class NwAnmCtrl* mpAnmCtrl;
    class ColObjTrans* mpColObjTrans;
    class RideHitCtrlTrans* mpRideHitCtrlTrans;
};

ASSERT_SIZE(GmkTurtle, 0x15C)

#endif
