#ifndef FLUFF_BGSTENTRYINFO_H
#define FLUFF_BGSTENTRYINFO_H

#include "types.h"

namespace BGST {
    struct EntryInfo {
        enum State {
            eState_Invalid          = 1,
            eState_Valid            = 2,
            eState_LoadMainImage    = 3, // assumed; this is n
            eState_MainImageLoaded  = 4,
            eState_LoadMaskImage    = 5,
            eState_MaskImageLoaded  = 6,
            eState_ReadyToRender    = 7
        };

        /* 0x00 */ u16 mState;
        /* 0x02 */ u16 mLayer;
        /* 0x04 */ u16 mRow;
        /* 0x06 */ u16 mColumn;
        /* 0x08 */ u16 mFileMainImageIndex; // refers to the file
        /* 0x0A */ u16 mFileMaskImageIndex; // refers to the file
        /* 0x0C */ u16 mMainImageIndex;
        /* 0x0E */ u16 mMaskImageIndex;
    };

    ASSERT_SIZE(EntryInfo, 0x10);
}

#endif
