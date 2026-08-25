#ifndef FLUFF_BEADUTIL_H
#define FLUFF_BEADUTIL_H

#include "object/gimmick/GmkBead.h"

namespace BeadUtil {
    GmkBead* CreateBead(s32 beadType, s32 beadColor, nw4r::math::VEC2 const& rBeadPosition);
}

#endif
