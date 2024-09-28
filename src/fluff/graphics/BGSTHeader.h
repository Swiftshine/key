#ifndef FLUFF_BGSTHEADER_H
#define FLUFF_BGSTHEADER_H

#include "types.h"

namespace BGST {
    struct Header {
        char mMagic; // "BGST"
        uint m_4;
        uint mImageWidth; // pixels
        uint mImageHeight;
        uint mGridWidth;
        uint mGridHeight;
        u32 mSomeOffset1;
        bool mGrid1Enabled;
        bool mGrid2Enabled;
        bool mGrid3Enabled;
        bool mGrid4Enabled;
        bool mGrid5Enabled;
        bool mGrid6Enabled;
        bool mGrid7Enabled;
        bool mGrid8Enabled;
        bool mGrid9Enabled;
        bool mGrid10Enabled;
        bool mGrid11Enabled;
        bool mGrid12Enabled;
        u32 mImageDataOffset;
        u32 mSomeOffset3;
        float mYOffset;
        char padding[0xC];
    };

}

#endif
