#ifndef FLUFF_BGSTLOADSTATE_H
#define FLUFF_BGSTLOADSTATE_H

#include "types.h"

namespace BGST {
    enum LoadState {
        eLoadState_LoadingNotInited = 0,
        eLoadState_LoadingImage     = 1,
        eLoadState_LoadingGrid      = 2,
        eLoadState_LoadingStop      = 3,
    };
}

#endif
