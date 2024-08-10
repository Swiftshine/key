#include <game/object/gmk/GmkTurtle.h>

GmkTurtle::GmkTurtle(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, "GmkTurtle")
{

}

GmkTurtle::~GmkTurtle() { }

void GmkTurtle::Update() {
    u32 state = mCurrentState;
}

int GmkTurtle::OnPlayerCollision(PlayerBase* player) {
    

    return 1;
}

void GmkTurtle::fn_804FB1D4() { }

void GmkTurtle::vf24() {
    
}
