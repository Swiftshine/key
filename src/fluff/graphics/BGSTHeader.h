#ifndef FLUFF_BGSTHEADER_H
#define FLUFF_BGSTHEADER_H

#include "types.h"
#include "gfl/gflMemoryManagement.h"

namespace BGST {
    struct Header {
        inline void operatordelete() {
            gfl::Free(this);
        }

        inline bool CheckLayer(int index) {
            return mLayerEnabled[index];
        }

        /* 0x00 */ char mMagic[4]; // "BGST"
        /* 0x04 */ uint mFlags;
        /* 0x08 */ uint mImageWidth;  // in pixels; this value is usually 512
        /* 0x0C */ uint mImageHeight; // same as above
        /* 0x10 */ uint mGridWidth;
        /* 0x14 */ uint mGridHeight;
        /* 0x18 */ u32 mEntryCount;
        /* 0x1C */ bool mLayerEnabled[12];
        /* 0x28 */ u32 mImageDataOffset;
        /* 0x2C */ u32 mSomeOffset3;
        /* 0x30 */ float mScale;
        /* 0x34 */ char padding[0xC];
    };

}

#endif
