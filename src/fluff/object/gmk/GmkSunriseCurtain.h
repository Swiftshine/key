#ifndef FLUFF_GMKSUNRISECURTAIN_H
#define FLUFF_GMKSUNRISECURTAIN_H

#include "object/Gimmick.h"
#include "sound/GameSound.h"
#include "sound/SD3DActor.h"
#include "graphics/FlfMdlDraw.h"
#include "graphics/FbAlpha.h"
#include "manager/GameManager.h"
#include "manager/LevelManager.h"

// size: 0x1B0
// this gimmick is tied to the Day/Night system in Splash Beach.
// it can interact with `GmkTurtle` and `GmkUpdownWater`.
class GmkSunriseCurtain : public Gimmick {
public:
    static GmkSunriseCurtain* Build(GimmickBuildInfo* buildInfo);

    GmkSunriseCurtain(GimmickBuildInfo* buildInfo);
    virtual ~GmkSunriseCurtain();
    void SetBGSTEntriesBasedOnMission();
    void SwitchStates();
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
    FlfMdlDraw* mFlfMdl1;
    FlfMdlDraw* mFlfMdl2;
    FbAlpha* mFbAlpha;
};

// ASSERT_SIZE(GmkSunriseCurtain, 0x1B0);

#endif
