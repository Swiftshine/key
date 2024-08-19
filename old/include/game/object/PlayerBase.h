#ifndef FLUFF_PLAYERBASE_H
#define FLUFF_PLAYERBASE_H

#include <gfl/task/Task.h>
#include <game/object/FlfGameObj.h>
// size: 0xF68
class PlayerBase : public FlfGameObj {
public:
    SCOPED_ENUM(PlayerIDs,
        Kirby,
        PrinceFluff,
    );
public:
    PlayerBase(gfl::Task* gameMgrTask, u32 flags, u32 unk3, u32 unk4, u32 unk5);
    ~PlayerBase();

    static PlayerBase* build(gfl::Task* gameMgrTask, u32 flags, u32 unk1, u32 unk2);

    void SetStartPosition(Vec3f* pos);
public:
    u8 contents[0xF68 - sizeof(FlfGameObj)];
};

ASSERT_SIZE(PlayerBase, 0xF68)

#endif
