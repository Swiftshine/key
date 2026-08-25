#ifndef FLUFF_BGSTHEADER_H
#define FLUFF_BGSTHEADER_H

#include "types.h"
#include "gfl/gflMemoryManagement.h"

namespace BGST {
    struct Header {
        inline void operatordelete() {
            gfl::Free(this);
        }

        inline bool CheckLayer(s32 index) {
            return mLayerEnabled[index];
        }

        /* 0x00 */ char mMagic[4]; // "BGST"
        /* 0x04 */ u32 mFlags;
        /* 0x08 */ u32 mImageWidth;  // in pixels; this value is usually 512
        /* 0x0C */ u32 mImageHeight; // same as above
        /* 0x10 */ u32 mGridWidth;
        /* 0x14 */ u32 mGridHeight;
        /* 0x18 */ u32 mEntryCount;
        /* 0x1C */ bool mLayerEnabled[12];
        /* 0x28 */ u32 mImageDataOffset;
        /* 0x2C */ u32 mSomeOffset3;
        /* 0x30 */ f32 mScaleModifier;
        /* 0x34 */ char padding[0xC];
    };

}

#endif
