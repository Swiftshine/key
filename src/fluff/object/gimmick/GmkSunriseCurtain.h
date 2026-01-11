#ifndef FLUFF_GMKSUNRISECURTAIN_H
#define FLUFF_GMKSUNRISECURTAIN_H

#include "object/Gimmick.h"
#include "sound/GameSound.h"
#include "gfl/gflColor.h"
#include "gfl/gflSD3DActor.h"
#include "graphics/FlfMdlDraw.h"
#include "graphics/FbAlpha.h"
#include "manager/GameManager.h"
#include "manager/Stage.h"
#include "misc/ScopedPointers.h"

/// @brief A gimmick tied to the day/night system in Splash Beach.
/// It can interact with `GmkTurtle` and `GmkUpdownWater`.
/// @note Size: `0x1B0`
class GmkSunriseCurtain : public Gimmick {
private:
public:
    ENUM_CLASS(TimeType,
        Night = 0,
        Day = 1,
    );

    ENUM_CLASS(State,
        Start = 0,
        State_1 = 1,
        State_2 = 2,
        AfterNight = 3,
        Wait = 4,
        BeforeDay = 5,
        Day = 6,
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
    void DoTimeSwitch() DONT_INLINE_CLASS;
    void RemoveSoundHandle() DONT_INLINE_CLASS;
    void SetBGSTLayers(bool setDay);

    /* FlfGameObj */
    virtual void SetState(FlfGameObj* setter, const std::string& state);

    /* Gimmick */
    virtual void Update() override;

private:
    /* 0x130 */ int mState;
    /* 0x134 */ uint mStateFrames; // a frame counter
    /* 0x138 */ int mNightBackgroundBGSTLayer;
    /* 0x13C */ int mNightForegroundBGSTLayer;
    /* 0x140 */ int mDayBackgroundBGSTLayer;
    /* 0x144 */ int mDayForegroundBGSTLayer;
    /* 0x148 */ bool mTimeChanged; // never actually used in any meaningful way
    /* 0x14C */ uint mColorChangeFrames;
    /* 0x150 */ gfl::Color mScreenTintColor; // a frame counter
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
