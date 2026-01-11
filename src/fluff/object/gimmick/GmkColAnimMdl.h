#ifndef FLUFF_GMKCOLANIMMDL_H
#define FLUFF_GMKCOLANIMMDL_H


#include "object/Gimmick.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/NwAnmCtrl.h"

#include "object/gimmick/GmkSimpleMdlRotZ.h"
#include "object/gimmick/GmkColAnimCtrl.h"
#include "object/gimmick/GmkAnimChg.h"

#define GMKCOLANIMMDL_ANIM_COUNT 4

// size: 0x150
class GmkColAnimMdl : public Gimmick, public GmkAnimChg {
private:
    ENUM_CLASS(Parameter,
        SortSceneIndex = 0, // int 0
        ZRotation = 0,      // float 0
        AnimationName = 0,  // string 0
        InitialFrameIndex = 2, // int 2
        AnimationSpeed = 2, // float 2
    );
public:
    static GmkColAnimMdl* Build(GimmickBuildInfo* buildInfo);

    GmkColAnimMdl(GimmickBuildInfo*) DONT_INLINE_CLASS;
    virtual ~GmkColAnimMdl();

    /* FlfGameObj */

    virtual void SetState(FlfGameObj* pSetter, const std::string& rState) override;
    virtual void vf64(bool) override;
    
    /* Gimmick */
    virtual int vf88(FlfGameObj*, uint) override;
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
    gfl::ResFileObject mResFileObject;
    gfl::Pointer<NwAnmCtrl> mAnimCtrl;
    gfl::Pointer<NwAnmCtrl> mShadowAnimCtrl;
    gfl::Pointer<GmkColAnimCtrl> mColAnimCtrlGmk;
    gfl::Pointer<GmkSimpleMdlRotZ> mZRotationGmk;
    nw4r::math::VEC3 mModelScale;
};


#endif
