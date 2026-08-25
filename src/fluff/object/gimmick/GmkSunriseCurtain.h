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
    enum TimeType {
        eTimeType_Night = 0,
        eTimeType_Day   = 1,
    };

    enum State {
        eState_Start = 0,
        eState_State_1 = 1,
        eState_State_2 = 2,
        eState_AfterNight = 3,
        eState_Wait = 4,
        eState_BeforeDay = 5,
        eState_Day = 6,
    };

    enum Parameter {
        eParameter_NightBackgroundBGSTLayer = 0, // s32 0
        eParameter_NightForegroundBGSTLayer = 1, // s32 1
        eParameter_DayBackgroundBGSTLayer = 2, // s32 2
        eParameter_DayForegroundBGSTLayer = 3, // s32 4
    };
public:
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
    /* 0x130 */ s32 mState;
    /* 0x134 */ u32 mStateFrames; // a frame counter
    /* 0x138 */ s32 mNightBackgroundBGSTLayer;
    /* 0x13C */ s32 mNightForegroundBGSTLayer;
    /* 0x140 */ s32 mDayBackgroundBGSTLayer;
    /* 0x144 */ s32 mDayForegroundBGSTLayer;
    /* 0x148 */ bool mTimeChanged; // never actually used in any meaningful way
    /* 0x14C */ u32 mColorChangeFrames;
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
