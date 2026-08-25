#ifndef FLUFF_NURBSDRAWOBJ_H
#define FLUFF_NURBSDRAWOBJ_H

#include "gfl/gflCustomRenderObj.h"
#include "graphics/FlfMdlDraw.h"

/// @note Size: `0x118`
class NURBSDrawObj : public gfl::CustomRenderObj {
public:
    /* Class Members */

    /* 0x104 */ FlfMdlDraw* mOwner;
    /* 0x108 */ f32 m_108;
    /* 0x10C */ f32 m_10C;
    /* 0x110 */ f32 m_110;
    /* 0x114 */ f32 m_114;
};

#endif
