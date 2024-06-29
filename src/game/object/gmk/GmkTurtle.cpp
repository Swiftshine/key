#include <game/object/gmk/GmkTurtle.h>

GmkTurtle::GmkTurtle(StageTask* stageTask)
    : Gimmick(stageTask, "GmkTurtle")
{

}

GmkTurtle::~GmkTurtle() { }

void GmkTurtle::Update() {
    u32 state = currentState;
}

int GmkTurtle::OnPlayerWeight(PlayerBase* player) {
    

    return 1;
}

void GmkTurtle::fn_804FB1D4() { }

void GmkTurtle::fn_804FB1CC() { }
