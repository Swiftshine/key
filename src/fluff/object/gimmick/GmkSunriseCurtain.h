#ifndef FLUFF_GMKSUNRISECURTAIN_H
#define FLUFF_GMKSUNRISECURTAIN_H

#include "object/Gimmick.h"
#include "sound/GameSound.h"
#include "gfl/gflSD3DActor.h"
#include "graphics/FlfMdlDraw.h"
#include "graphics/FbAlpha.h"
#include "manager/GameManager.h"
#include "manager/Stage.h"
#include "misc/ScopedPointers.h"

// size: 0x1B0
// this gimmick is tied to the Day/Night system in Splash Beach.
// it can interact with `GmkTurtle` and `GmkUpdownWater`.
class GmkSunriseCurtain : public Gimmick {
public:
    ENUM_CLASS(TimeType,
        Night = 0,
        Day = 1,
    );

    ENUM_CLASS(State,
        State_0 = 0,
        State_1 = 1,
        State_2 = 2,
        State_3 = 3,
        State_4 = 4,
        State_5 = 5,
        State_6 = 6,
    );

    ENUM_CLASS(Parameter,
        NightBackgroundBGSTLayer = 0, // int 0
        NightForegroundBGSTLayer = 1, // int 1
        DayBackgroundBGSTLayer = 2, // int 2
        DayForegroundBGSTLayer = 3, // int 4
    );

    static GmkSunriseCurtain* Build(GimmickBuildInfo* pBuildInfo);

    GmkSunriseCurtain(GimmickBuildInfo* pBuildInfo) DONT_INLINE_CLASS;
    virtual ~GmkSunriseCurtain();
    void SetBGSTLayersBasedOnMission();
    void SwitchStates() DONT_INLINE_CLASS;
    void OnTimeSwitch();
    void fn_803CA82C();
    void SetBGSTLayers(bool setDay);

    /* FlfGameObj */
    virtual void SetState(FlfGameObj* setter, std::string& state);

    /* Gimmick */
    virtual void Update() override;

private:
    /* 0x130 */ int mState;
    /* 0x134 */ int m_134;
    /* 0x138 */ int mNightBackgroundBGSTLayer;
    /* 0x13C */ int mNightForegroundBGSTLayer;
    /* 0x140 */ int mDayBackgroundBGSTLayer;
    /* 0x144 */ int mDayForegroundBGSTLayer;
    /* 0x148 */ bool m_148;
    /* 0x14C */ int m_14C;
    /* 0x150 */ union {
        GXColor mScreenTintColor;
        struct {
            u8 mTintR;
            u8 mTintG;
            u8 mTintB;
            u8 mTintA;
        };
    };
    /* 0x154 */ gfl::SoundHandle mMainSoundHandle;
    /* 0x15C */ gfl::SoundHandle mSplashBeachSoundHandle;
    /* 0x164 */ gfl::SD3DActorWrapper mSD3DActorWrapper;
    /* 0x19C */ FlfHandle mGateHandle; // GmkGate3
    /* 0x1A4 */ gfl::Pointer<FlfMdlDraw> mFlfMdlDraw1;
    /* 0x1A8 */ gfl::Pointer<FlfMdlDraw> mFlfMdlDraw2;
    /* 0x1AC */ G3dObjPointer<FbAlpha> mFbAlpha;
};

// ASSERT_SIZE(GmkSunriseCurtain, 0x1B0);

#endif
