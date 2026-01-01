#ifndef FLUFF_BGSTENTRYINFO_H
#define FLUFF_BGSTENTRYINFO_H

#include "types.h"

namespace BGST {

    struct EntryInfo {
        ENUM_CLASS(State,
            Invalid         = 1,
            Valid           = 2,
            LoadMainImage   = 3, // assumed; this is never used
            MainImageLoaded = 4,
            LoadMaskImage   = 5,
            MaskImageLoaded = 6,
            ReadyToRender   = 7
        );
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
