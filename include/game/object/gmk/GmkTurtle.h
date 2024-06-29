#ifndef FLUFF_GMK_TURTLE_H
#define FLUFF_GMK_TURTLE_H

#include <game/object/Gimmick.h>
#include <game/object/PlayerBase.h>

// size: 0x15C
class GmkTurtle : public Gimmick {
public:
    enum State {
        State_0,
        MoveLeft,
        TurnRight,
        State_3,
        MoveRight,
        TurnLeft,
        State_6,
        State_7,
        State_8,
    };

public:
    GmkTurtle(StageTask* stageTask);
    ~GmkTurtle();

    virtual void Update();

    virtual int OnPlayerWeight(PlayerBase*);

    virtual void fn_804FB1D4();
    void fn_804FB1CC();

public:
    u32 counterDefaultValue;
    f32 speed;
    f32 _138;
    bool _13C;
    bool _13D;
    u16 _13E;
    u32 counter;
    u32 numTurtles;
    u32 currentState;
    Gimmick* water;
    void* animnCtrl; // NwAnmCtrl*
    void* colObjTrans; // ColObjTrans*
    void* rideHitCtrlTrans; // FlfRideHitCtrlTrans*
};

#endif
