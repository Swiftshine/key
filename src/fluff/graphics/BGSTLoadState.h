#ifndef FLUFF_BGSTLOADSTATE_H
#define FLUFF_BGSTLOADSTATE_H

#include "types.h"

namespace BGST {
    ENUM_CLASS(LoadState,
        BGST_LOADING_NOT_INITED = 0,
        BGST_LOADING_IMAGE = 1,
        BGST_LOADING_GRID = 2,
        BGST_LOADING_STOP = 3
    );
}

#endif
