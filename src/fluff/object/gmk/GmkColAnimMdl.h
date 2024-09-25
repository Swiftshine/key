#ifndef FLUFF_GMKCOLANIMMDL_H
#define FLUFF_GMKCOLANIMMDL_H


#include "object/Gimmick.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/NwAnmCtrl.h"
#include "gfl/gflVec3.h"
#include "object/gmk/GmkSimpleMdlRotZ.h"
#include "object/gmk/GmkColAnimCtrl.h"

// size: 0x150
class GmkColAnimMdl : public Gimmick {
public:
    static GmkColAnimMdl* Build(GimmickBuildInfo* buildInfo);

    GmkColAnimMdl(GimmickBuildInfo*) DONT_INLINE_CLASS;
    virtual ~GmkColAnimMdl();

    void SetAnimationIndex(uint index);
    bool HasAnimation(uint index);
    uint GetCurrentAnimationIndex();
    bool CheckAnimationProgress();
    bool IsAnimationDone();
    void SetUpdate(bool state);
    bool fn_800D60FC();

private:
    gfl::ResFileInfoPointer mResFileInfo;
    gfl::ScopedPointer<NwAnmCtrl> mAnimCtrl;
    gfl::ScopedPointer<NwAnmCtrl> mShadowAnimCtrl;
    gfl::ScopedPointer<GmkColAnimCtrl> mColAnimCtrlGmk;
    gfl::ScopedPointer<GmkSimpleMdlRotZ> mZRotationGmk;
    gfl::Vec3 mModelScale;
};


#endif