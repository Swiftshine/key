#ifndef FLUFF_BEADUTIL_H
#define FLUFF_BEADUTIL_H

#include "object/gimmick/GmkBead.h"

namespace BeadUtil {
    GmkBead* CreateBead(int beadType, int beadColor, nw4r::math::VEC2 const& rBeadPosition);
}

#endif
