#ifndef FLUFF_GMKCOLANIMMDL_H
#define FLUFF_GMKCOLANIMMDL_H


#include "object/Gimmick.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/NwAnmCtrl.h"

#include "object/gmk/GmkSimpleMdlRotZ.h"
#include "object/gmk/GmkColAnimCtrl.h"
#include "object/gmk/GmkAnimChg.h"

#define GMKCOLANIMMDL_ANIM_COUNT 4

// size: 0x150
class GmkColAnimMdl : public Gimmick, public GmkAnimChg {
private:
    ENUM_CLASS(Parameter,
        SortSceneIndex = 0, // int 0
        ZRotation = 0,      // float 0
        AnimationName = 0,  // string 0

        InitialFrameIndex = 2, // int 2
    );
public:
    static GmkColAnimMdl* Build(GimmickBuildInfo* buildInfo);

    GmkColAnimMdl(GimmickBuildInfo*) DONT_INLINE_CLASS;
    virtual ~GmkColAnimMdl();

    /* FlfGameObj */

    virtual void SetState(FlfGameObj* setter, std::string& stateStr) override;
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
    nw4r::math::VEC3 mModelScale;
};


#endif
