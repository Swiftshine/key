#ifndef FLUFF_BEADPOPITEMINFO_H
#define FLUFF_BEADPOPITEMINFO_H

#include "types.h"
#include "graphics/MoguraLight.h"

class GmkBeadPopItem_Info {
public:
    GmkBeadPopItem_Info();
    ~GmkBeadPopItem_Info();

    void Init(float arg0);
    void SetPosition(nw4r::math::VEC3& position);
    void fn_805C46D0(bool);
    void fn_805C4760();
private:
    bool m_0;
    float m_4;
    float mZPosition; // @ 0x8
    MoguraLight* mMoleLight; // @ 0xC
};

ASSERT_SIZE(GmkBeadPopItem_Info, 0x10);

#endif
