#ifndef FLUFF_PLAYERBASE_H
#define FLUFF_PLAYERBASE_H

#include "types.h"
#include "object/FlfGameObj.h"
#include "object/collision/IObjHitCB.h"
#include "object/collision/FlfMdlCollision.h"
#include "manager/PlayerMdlMng.h"

/// @brief The player class.
class PlayerBase : public FlfGameObj, public IObjHitCB {
public:
    /* Structures */

    ENUM_CLASS(PlayerID,
        Kirby           = 0,
        PrinceFluff     = 1,
    );

    ENUM_CLASS(PlayerState,
        Default         = 0,
        TouchGround     = 1,
        Jump            = 2,

        YarnWhip        = 4,
        Weight          = 5,
        Fall            = 6,

        TakeDamage      = 9,
        Sled            = 10,
        YarnWhipLockOn  = 11,
        ThrowItem       = 12,

        Parachute       = 14,
        Tangled         = 15,
        Crumple         = 16,
        SideBumped      = 17,
        EntityCollision = 18,

        Baseball        = 20,

        DropItem        = 22,
    );

    /* Constructor */

    PlayerBase(gfl::Task* pGameMgrTask, uint flags, uint unk3, uint unk4, uint unk5);
    
    /* Virtual Methods */

    /* 0x008 */ virtual ~PlayerBase();

    /* Class Methods */

    void SetStartPosition(nw4r::math::VEC3& rPos);
    bool IsStateDefault();
    void fn_8009C464(bool);
    void Reset(uint arg1, int playerState, int arg3, int arg4);
    uint GetPlayerID();
    void PlayAnimation(int id);
    void SetFullSortScene(FullSortScene* pScene, int arg2);

    /* Temporary Inlines */
    inline void SetIsControlled(bool value) {
        *(reinterpret_cast<u8*>(this) + 0xF39) = value;
    }

    inline FlfMdlCollision* GetFlfMdlCollision() {
        return *(reinterpret_cast<FlfMdlCollision**>(reinterpret_cast<u8*>(this) + 0x788));
    }

    inline void SetUnk78C(int val) {
        *(reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x78C)) = val;
    }

    inline PlayerMdlMng* GetPlayerMdlMng() {
        return *(reinterpret_cast<PlayerMdlMng**>(reinterpret_cast<u8*>(this) + 0x50C));
    }

    /* Static Methods */
    static PlayerBase* Build(gfl::Task* pGameMgrTask, uint flags, uint unk1, uint unk2);
    
};
#endif