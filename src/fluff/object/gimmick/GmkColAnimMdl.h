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
public:
    enum Parameter {
        eParameter_SortSceneIndex = 0, // s32 0
        eParameter_ZRotation = 0,      // f32 0
        eParameter_AnimationName = 0,  // string 0
        eParameter_InitialFrameIndex = 2, // s32 2
        eParameter_AnimationSpeed = 2, // f32 2
    };
public:
    static GmkColAnimMdl* Build(GimmickBuildInfo* buildInfo);

    GmkColAnimMdl(GimmickBuildInfo*) DONT_INLINE_CLASS;
    virtual ~GmkColAnimMdl();

    /* FlfGameObj */

    virtual void SetState(FlfGameObj* pSetter, const std::string& rState) override;
    virtual void UpdateWater(bool) override;

    /* Gimmick */
    virtual s32 vf88(FlfGameObj*, u32) override;
    virtual bool vfA4(FlfGameObj*, u32) override;
    virtual void Update() override;

    /* GmkColAnimMdl */

    virtual void SetAnimationIndex(u32 index);
    virtual bool HasAnimation(u32 index);
    virtual u32 GetCurrentAnimationIndex();
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
