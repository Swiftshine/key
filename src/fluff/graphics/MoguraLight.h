#ifndef FLUFF_MOGURALIGHT_H
#define FLUFF_MOGURALIGHT_H

#include "graphics/GmkMoleHoleRender.h"
#include "graphics/NwAnmCtrl.h"

// "mole light"
class MoguraLight {
public:
    MoguraLight();
    ~MoguraLight();

    void SetUpdate(bool doUpdate);
    void UpdateMatrix();
private:
    float mZPosition; // @ 0x0
    nw4r::math::VEC2 mPosition; // @ 0x4
    gfl::ResFileInfo* mFileInfo; // @ 0xC
    GmkMoleHoleRender::RenderUser* mRenderUser; // @ 0x10
    NwAnmCtrl* mAnimCtrl; // @ 0x14
};

ASSERT_SIZE(MoguraLight, 0x18);

#endif