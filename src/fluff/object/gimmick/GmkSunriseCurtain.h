#ifndef FLUFF_GMKSUNRISECURTAIN_H
#define FLUFF_GMKSUNRISECURTAIN_H

#include "object/Gimmick.h"
#include "sound/GameSound.h"
#include "sound/SD3DActor.h"
#include "graphics/FlfMdlDraw.h"
#include "graphics/FbAlpha.h"
#include "manager/GameManager.h"
#include "manager/StageManager.h"
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

    static GmkSunriseCurtain* Build(GimmickBuildInfo* buildInfo);

    GmkSunriseCurtain(GimmickBuildInfo* buildInfo) DONT_INLINE_CLASS;
    virtual ~GmkSunriseCurtain();
    void SetBGSTEntriesBasedOnMission();
    void SwitchStates() DONT_INLINE_CLASS;
    void OnTimeSwitch();
    void fn_803CA82C();
    void SetBGSTEntries(bool setDay);

    /* FlfGameObj */
    virtual void SetState(FlfGameObj* setter, std::string& state);

    /* Gimmick */
    virtual void Update() override;

private:
    int mState;
    int m_134;
    int mNightMainBGSTIndex;
    int mNightShadowBGSTIndex;
    int mDayMainBGSTIndex;
    int mDayShadowBGSTIndex;
    bool m_148;
    int m_14C;
    GXColor mScreenTintColor;
    int m_154;
    int m_158;
    int m_15C;
    int m_160;
    SD3DActor mSD3DActor;
    int m_19C;
    int m_1A0;
    gfl::Pointer<FlfMdlDraw> mFlfMdl1;
    gfl::Pointer<FlfMdlDraw> mFlfMdl2;
    G3dObjPointer<FbAlpha> mFbAlpha;
    // FbAlpha* mFbAlpha;
};

// ASSERT_SIZE(GmkSunriseCurtain, 0x1B0);

#endif
