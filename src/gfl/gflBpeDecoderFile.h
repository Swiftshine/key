#ifndef GFL_BPEDECODERFILE_H
#define GFL_BPEDECODERFILE_H

#include <revolution/OS.h>
#include "gflFile.h"

namespace gfl {
    class AsyncFileStream;

    class BpeDecoderFile {
    public:
        /**
         * @note Address: 0x80644FFC
         * @note Size: 0x2C
         */
        BpeDecoderFile(File* file, AsyncFileStream* output);
        /**
         * @note Address: 0x80645028
         * @note Size: 0x4
         */
        DECL_WEAK virtual ~BpeDecoderFile();

        /**
         * @note Address: 0x8064502C
         * @note Size: 0x674
         * @note Good-Feel uses byte pair encoding as a form of compression.
         * You can find the decoding function it is based off of here: http://www.pennelynn.com/Documents/CUJ/HTML/94HTML/19940045.HTM
         */
        void Decode(u8 heapID, size_t* decompressedSize, uint align);
    private:
        File* mFile;
        AsyncFileStream* mOutput;
        OSMutex* mInput;
        void* mDecodedData;
        size_t mEncodedSize;
        size_t mDecodedSize;
        uint _1C;
    };

    ASSERT_SIZE(BpeDecoderFile, 0x20);
}

#endif