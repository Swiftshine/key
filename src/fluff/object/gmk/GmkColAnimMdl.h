#ifndef FLUFF_GMKCOLANIMMDL_H
#define FLUFF_GMKCOLANIMMDL_H


#include "object/Gimmick.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/NwAnmCtrl.h"
#include "gfl/gflVec3.h"
#include "object/gmk/GmkSimpleMdlRotZ.h"

class GmkColAnimCtrl;

// size: 0x150
class GmkColAnimMdl : public Gimmick {
public:
    static GmkColAnimMdl* Build(GimmickBuildInfo* buildInfo);


    GmkColAnimMdl(GimmickBuildInfo*);
    virtual ~GmkColAnimMdl();
private:
    gfl::ResFileInfoPointer mResFileInfo;
    NwAnmCtrl* mAnimCtrl;
    NwAnmCtrl* mShadowAnimCtrl;
    GmkColAnimCtrl* mColAnimCtrlGmk;
    GmkSimpleMdlRotZ* mZRotationGmk;
    gfl::Vec3 mModelScale;
};

// ASSERT_SIZE(GmkColAnimCtrl, 0x150);

#endif