#ifndef FLUFF_NWBLENDANM_H
#define FLUFF_NWBLENDANM_H

#include "types.h"
#include "gfl/gflMtx34.h"
#include "gfl/gflScnMdlWrapper.h"

/// @note Size: `0x28`
class NwBlendAnm {
public:
    NwBlendAnm();
    virtual ~NwBlendAnm();

    gfl::Mtx34 GetMatrix(gfl::ScnMdlWrapper* pScnMdlWrapper, u32 id);
    /* 0x00 */ STRUCT_FILL(0x24);
};

#endif
