#ifndef FLUFF_BEADPOPITEMINFO_H
#define FLUFF_BEADPOPITEMINFO_H

#include "types.h"
#include "graphics/MoguraLight.h"

/// @note Size: `0x10`
class GmkBeadPopItem_Info {
public:
    /* Constructor + Destructor */

    GmkBeadPopItem_Info();
    ~GmkBeadPopItem_Info();
    
    /* Class Methods */

    void Init(float arg0);
    void SetPosition(nw4r::math::VEC3& rPos);
    void fn_805C46D0(bool);
    void fn_805C46FC(bool);
    void fn_805C4760();

    /* Class Members */

    /* 0x0 */ bool m_0;
    /* 0x4 */ float m_4;
    /* 0x8 */ float mZPosition;
    /* 0xC */ MoguraLight* mMoleLight;
};

ASSERT_SIZE(GmkBeadPopItem_Info, 0x10);

#endif
