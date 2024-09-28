#ifndef FLUFF_BGSTHEADER_H
#define FLUFF_BGSTHEADER_H

#include "types.h"
#include "gfl/gflMemoryManagement.h"

namespace BGST {
    struct Header {
        inline void operatordelete() {
            gfl::Free(this);
        }

        inline bool CheckColumns(int index) {
            return mColumnEnabled[index];
        }

        char mMagic; // "BGST"
        uint m_4;
        uint mImageWidth; // pixels
        uint mImageHeight;
        uint mGridWidth;
        uint mGridHeight;
        u32 mSomeOffset1;
        bool mColumnEnabled[12];
        u32 mImageDataOffset;
        u32 mSomeOffset3;
        float mYOffset;
        char padding[0xC];
    };

}

#endif
