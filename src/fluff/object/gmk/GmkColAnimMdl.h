#ifndef FLUFF_GMKCOLANIMMDL_H
#define FLUFF_GMKCOLANIMMDL_H


#include "object/Gimmick.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/NwAnmCtrl.h"
#include "gfl/gflVec3.h"
#include "object/gmk/GmkSimpleMdlRotZ.h"
#include "object/gmk/GmkColAnimCtrl.h"
#include "object/gmk/GmkAnimChg.h"

// size: 0x150
class GmkColAnimMdl : public Gimmick, public GmkAnimChg {
public:
    static GmkColAnimMdl* Build(GimmickBuildInfo* buildInfo);

    GmkColAnimMdl(GimmickBuildInfo*) DONT_INLINE_CLASS;
    virtual ~GmkColAnimMdl();

    /* FlfGameObj */

    virtual void SetState(uint arg1, std::string& stateStr) override;
    virtual void vf64(bool) override;
    /* Gimmick */

    virtual bool vf88(FlfGameObj*, uint) override;
    virtual bool vfA4(FlfGameObj*, uint) override;
    virtual void Update() override;

    /* GmkColAnimMdl */
    
    virtual void SetAnimationIndex(uint index);
    virtual bool HasAnimation(uint index);
    virtual uint GetCurrentAnimationIndex();
    virtual bool CheckAnimationProgress();
    virtual bool IsAnimationDone();
    virtual void SetUpdate(bool state);


    void UpdateModel();

private:
    gfl::ResFileInfoPointer mResFileInfo;
    gfl::ScopedPointer<NwAnmCtrl> mAnimCtrl;
    gfl::ScopedPointer<NwAnmCtrl> mShadowAnimCtrl;
    gfl::ScopedPointer<GmkColAnimCtrl> mColAnimCtrlGmk;
    gfl::ScopedPointer<GmkSimpleMdlRotZ> mZRotationGmk;
    gfl::Vec3 mModelScale;
};


#endif