#ifndef GFL_BPEDECODERFILE_H
#define GFL_BPEDECODERFILE_H

#include <revolution/OS.h>
#include "gflAsyncFileStream.h"
#include "gflGfCompression.h"
#include "gflFile.h"
#include "gflMemoryManagement.h"
#include "gflPointer.h"

namespace gfl {
    class BpeDecoderFile {
    public:   
        /**
         * @note Address: 0x80644FFC
         * @note Size: 0x2C
         */
        BpeDecoderFile(File* pFile, size_t inputStreamPos);

        /**
         * @note Known to be inlined. Can be found
         * un-inlined in Wario Land: Shake It!
         * at US address 0x8001E728
         */
        inline void Reset() {
            mDecodedData = nullptr;
            mEncodedSize = 0;
            mDecodedSize = 0;
        }

        /**
         * @note Known to be inlined. Can be found
         * un-inlined in Wario Land: Shake It!
         * at US Address 0x8001E740
         */
        inline void PrepareDecode() {
            void* rawCompressionHeader = Alloc(HeapID::LIB1, 0x20, 0x20);
		    mFile->Read(rawCompressionHeader, 0x20, mInputStreamPos);
		    gfl::GfCompressionWrapper gfcpWrapper(rawCompressionHeader);
		    mDecodedSize = gfcpWrapper.GetDecompressedSize();
		    mEncodedSize = gfcpWrapper.GetCompressedSize();
		    gfl::Free(rawCompressionHeader);
        }

        /**
         * @note Address: 0x80645028
         * @note Size: 0x4
         */
        DECL_WEAK virtual ~BpeDecoderFile();

        /**
         * @note Address: 0x8064502C
         * @note Size: 0x674
         * @returns A pointed to decoded data.
         * @note Good-Feel uses byte pair encoding as a form of compression.
         * You can find the decoding function it is based off of here: http://www.pennelynn.com/Documents/CUJ/HTML/94HTML/19940045.HTM
         */
        void* Decode(u8 heapID, size_t* pDecompressedSize, uint align);
    private:
        File* mFile;            // @ 0x4
        size_t mInputStreamPos; // @ 0x8
        gfl::Pointer<AsyncFileStream> mInputStream; // @ 0xC
        void* mDecodedData;     // @ 0x10
        size_t mEncodedSize;    // @ 0x14
        size_t mDecodedSize;    // @ 0x18
    };

    ASSERT_SIZE(BpeDecoderFile, 0x1C);
}

#endif
