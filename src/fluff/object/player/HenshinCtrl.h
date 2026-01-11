#ifndef FLUFF_HENSHINCTRL_H
#define FLUFF_HENSHINCTRL_H

#include "env/EnvManager_Sound.h"
#include "env/EnvParts_PlayGuideIconLocator.h"

#include "graphics/FlfMdlDraw.h"
#include "graphics/PlTransMdl.h"

#include "object/FlfHandleObj.h"
#include "object/collision/FlfMdlCollision.h"

#include "misc/ScopedPointers.h"

class PlayerBase;

/// @brief A base class for player transformations.
/// @note Size: `0x58`
class HenshinCtrl {
public:
    HenshinCtrl(PlayerBase* pPlayer);
    
    /* Virtual Methods */
    /* 0x008 */ virtual ~HenshinCtrl();
    /* 0x00C */ virtual void vfC() = 0;
    /* 0x010 */ virtual void vf10() = 0;
    /* 0x014 */ virtual void vf14() = 0;
    /* 0x018 */ virtual void vf18() = 0;
    /* 0x01C */ virtual void vf1C();
    /* 0x020 */ DECL_WEAK virtual int vf20();
    /* 0x024 */ DECL_WEAK virtual int vf24();
    /* 0x028 */ virtual bool vf28();
    /* 0x02C */ virtual void vf2C();
    /* 0x030 */ virtual void vf30();
    /* 0x034 */ virtual void vf34();
    /* 0x038 */ virtual void vf38();
    /* 0x03C */ virtual void vf3C();
    /* 0x040 */ virtual void vf40();
    /* 0x044 */ virtual void vf44();
    /* 0x048 */ virtual void vf48();
    /* 0x04C */ DECL_WEAK virtual void SetPosition(const gfl::Vec3&);
    /* 0x050 */ virtual void vf50();
    /* 0x054 */ virtual void vf54();
    /* 0x058 */ virtual void vf58();
    /* 0x05C */ virtual void vf5C();
    /* 0x060 */ virtual void vf60();
    /* 0x064 */ virtual void vf64();
    /* 0x068 */ virtual void vf68();
    /* 0x06C */ virtual void vf6C();
    /* 0x070 */ virtual void vf70();
    /* 0x074 */ virtual void vf74();
    /* 0x078 */ virtual void vf78();
    /* 0x07C */ virtual void vf7C();
    /* 0x080 */ virtual void vf80();
    /* 0x084 */ virtual void vf84();
    /* 0x088 */ virtual void vf88();
    /* 0x08C */ virtual void vf8C();
    /* 0x090 */ virtual void vf90();
    /* 0x094 */ virtual void vf94();
    /* 0x098 */ virtual FullSortScene* ResetScene(FullSortScene* pScene) {
        return nullptr;
    }
    /* 0x09C */ virtual void vf9C();
    /* 0x0A0 */ virtual void vfA0();
    /* 0x0A4 */ virtual void vfA4();
    /* 0x0A8 */ virtual void vfA8();
    /* 0x0AC */ virtual void Init(const gfl::Vec3& rPos);
    /* 0x0B0 */ virtual void vfB0();
    /* 0x0B4 */ virtual void vfB4();
    /* 0x0B8 */ virtual void vfB8();
    /* 0x0BC */ virtual void vfBC();
    /* 0x0C0 */ virtual void vfC0();
    /* 0x0C4 */ virtual void vfC4();
    /* 0x0C8 */ virtual void vfC8();
    /* 0x0CC */ virtual void vfCC();
    /* 0x0D0 */ virtual void vfD0();
    /* 0x0D4 */ virtual void vfD4();
    /* 0x0D8 */ virtual bool vfD8(float, PlayerBase* pPlayer, PlTransMdl* pPlTransMdl);
    /* 0x0DC */ virtual void vfDC(FlfMdlDraw* pFlfMdlDraw);
    /* 0x0E0 */ virtual void vfE0();
    /* 0x0E4 */ virtual void vfE4();
    /* 0x0E8 */ virtual void vfE8();
    /* 0x0EC */ virtual void vfEC();
    /* 0x0F0 */ virtual void vfF0();
    /* 0x0F4 */ virtual void vfF4();
    /* 0x0F8 */ virtual void vfF8();
    /* 0x0FC */ virtual void vfFC();
    /* 0x100 */ virtual void vf100();
    /* 0x104 */ virtual void vf104();
    /* 0x108 */ virtual void vf108();
    /* 0x10C */ virtual void vf10C();
    /* 0x110 */ virtual void vf110();
    /* 0x114 */ virtual void vf114();
    /* 0x118 */ virtual void vf118();
    /* 0x11C */ virtual void vf11C();
    /* 0x120 */ virtual void vf120();
    /* 0x124 */ virtual void vf124();
    /* 0x128 */ virtual void vf128();
    /* 0x12C */ virtual void vf12C();

    /* Class Members */

    /* 0x04 */ FlfHandle mPlayerHandle;
    /* 0x0C */ gfl::Vec3 mPosition;
    /* 0x18 */ int m_18;
    /* 0x1C */ FlfMdlCollision* mFlfMdlCollision;
    /* 0x20 */ int mCurrentState; // probably a StateObject?
    /* 0x24 */ int mPreviousState;
    /* 0x28 */ int m_28;
    /* 0x2C */ uint m_2C;
    /* 0x30 */ int m_30;
    /* 0x34 */ gfl::Pointer<gfl::SoundFadeCtrl> mSoundFadeCtrl;
    /* 0x38 */ gfl::Vec3 m_38;
    /* 0x44 */ int m_44;
    /* 0x48 */ gfl::Vec2 m_48;
    /* 0x50 */ bool m_50;
    /* 0x54 */ gfl::Pointer<env::EnvParts_PlayGuideIconLocator> mEnvParts_PlayGuideIconLocator;
};

// todo - make separate headers for these
class HenshinString : public HenshinCtrl { };
class HenshinBoat : public HenshinCtrl { };
class HenshinRobot : public HenshinCtrl { };
class HenshinVehicle : public HenshinCtrl { };
class HenshinSplash : public HenshinCtrl { };
class HenshinAquaRide : public HenshinCtrl { };
class HenshinRocket : public HenshinCtrl { };
class HenshinWarpStar : public HenshinCtrl { };
class HenshinBrightRobot : public HenshinCtrl { };
class HenshinTrainFree : public HenshinCtrl { };

#endif