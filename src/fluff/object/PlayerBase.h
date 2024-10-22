#ifndef FLUFF_PLAYERBASE_H
#define FLUFF_PLAYERBASE_H

#include "types.h"
#include "object/FlfGameObj.h"
#include "object/collision/IObjHitCB.h"

class PlayerBase : public FlfGameObj, public IObjHitCB {
public:
    ENUM_CLASS(PlayerIDs,
        Kirby,
        PrinceFluff,
    );

public:
    PlayerBase(gfl::Task* gameMgrTask, uint flags, uint unk3, uint unk4, uint unk5);
    virtual ~PlayerBase();

    static PlayerBase* build(gfl::Task* gameMgrTask, uint flags, uint unk1, uint unk2);

    void SetStartPosition(nw4r::math::VEC3& pos);
};
#endif