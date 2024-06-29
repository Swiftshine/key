#include <game/object/PlayerBase.h>

PlayerBase::PlayerBase(gfl::Task* gameMgrTask, u32 flags, u32 unk3, u32 unk4, u32 unk5)
    : FlfGameObj(ActorType_Player)
{
    
}

PlayerBase::~PlayerBase() {

}

PlayerBase* PlayerBase::build(gfl::Task* gameMgrTask, u32 flags, u32 unk1, u32 unk2) {
    PlayerBase* player = new PlayerBase(gameMgrTask, flags, unk1, unk2, 0);
    Vec3f pos;
    player->SetStartPosition(&pos);
    return player;
} 

void PlayerBase::SetStartPosition(Vec3f* pos) {
    
}
