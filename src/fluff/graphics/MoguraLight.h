#ifndef FLUFF_MOGURALIGHT_H
#define FLUFF_MOGURALIGHT_H

#include "graphics/GmkMoleHoleRender.h"
#include "graphics/NwAnmCtrl.h"

/// @brief "Mole Light"
class MoguraLight {
public:
    

    MoguraLight();
    ~MoguraLight();

    /* Class Methods */

    void SetUpdate(bool doUpdate);
    void UpdateMatrix();
    void SetZPosition(float pos);
    void SetPosition(nw4r::math::VEC2& rPosition);

    /* Class Members */

    /* 0x00 */ float mZPosition;
    /* 0x04 */ nw4r::math::VEC2 mPosition;
    /* 0x0C */ gfl::ResFileInfo* mFileInfo;
    /* 0x10 */ GmkMoleHoleRender::RenderUser* mRenderUser;
    /* 0x14 */ NwAnmCtrl* mAnimCtrl;
};

ASSERT_SIZE(MoguraLight, 0x18);

#endif
