#ifndef FLUFF_GMKMSCARRIERGOAL_H
#define FLUFF_GMKMSCARRIERGOAL_H

#include "object/Gimmick.h"
#include "misc/ScopedPointers.h"
#include "graphics/NwAnmCtrl.h"
#include "gfl/gflResFileInfo.h"

// size: 0x148
class GmkMsCarrierGoal : public Gimmick {
public:
    static GmkMsCarrierGoal* Build(GimmickBuildInfo* buildInfo);
    GmkMsCarrierGoal(GimmickBuildInfo* buildInfo, const char* taskName) DONT_INLINE_CLASS;
    virtual ~GmkMsCarrierGoal();
    
    void Init(GimmickBuildInfo* buildInfo);

    /* FlfGameObj */
    virtual void vf24() override;

    /* Gimmick */
    virtual void Update() override;

    nw4r::math::VEC3 GetEffectPosition();
    void PlayEffect();
    NwAnmCtrl* CreateAnimCtrl(const char* animName, gfl::ResFileObject& resFileObject);
private:
    int mState;
    uint mCounter;
    nw4r::math::VEC3 mAnimationPosition;
    gfl::Pointer<NwAnmCtrl> mAnimCtrl;
};

#endif
