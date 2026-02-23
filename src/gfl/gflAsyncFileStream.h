#ifndef GFL_ASYNCFILESTREAM_H
#define GFL_ASYNCFILESTREAM_H

#include <revolution/OS.h>
#include "gflAlloc.h"
#include "gflFile.h"
#include "gflMutex.h"

#define BPE_BLOCK_SIZE 0x20000

namespace gfl {

class AsyncFileStream {
public:
    AsyncFileStream(File* pFile, size_t compressedSize, size_t streamPos);
    virtual ~AsyncFileStream();

    /* Class Methods */

    void Init();
    void Update();

    // getc equivalent
    inline char GetByte() {
        char result = *mByteCursor;
        mByteCursor++;
        return result;
    }

    /* Class Members */

    /* 0x04 */ File* mFile;
    /* 0x08 */ size_t mCompressedSize;
    /* 0x0C */ size_t mStartStreamPos;
    /* 0x10 */ void* mDecompressedBuffer;
    /* 0x14 */ void* mCompressedBuffer;
    /* 0x18 */ size_t mNumBlocksRead;
    /* 0x1C */ size_t mNumBytesRemaining; // in the current block
    /* 0x20 */ char* mByteCursor;
    /* 0x24 */ size_t mCurrentStreamPos;
    /* 0x28 */ size_t mNumBytesRead;
    /* 0x2C */ size_t mBlockSize;
};

ASSERT_SIZE(AsyncFileStream, 0x30);

// size: 0x24
class AsyncFileStreamManager {
private:
    static AsyncFileStreamManager* sInstance;
public:
    static inline AsyncFileStreamManager* Instance() {
        return sInstance;
    }

    inline AsyncFileStreamManager()
        : mFileStream(nullptr)
        , mMutex()
    {
        mCompressedBuffer = Alloc(HeapID::LIB1, BPE_BLOCK_SIZE, 0x20);
        mDecompressedBuffer = Alloc(HeapID::LIB1, BPE_BLOCK_SIZE, 0x20);
    }

    inline ~AsyncFileStreamManager() {
        Free(mDecompressedBuffer);
        Free(mCompressedBuffer);
        sInstance = nullptr;
    }

    /* Class Methods */

    void Reset(AsyncFileStream* pFileStream);

    /* Static Methods */

    static void InitInstance();
    static void DestroyInstance();

    inline Mutex& GetMutex() {
        return mMutex;
    }
    
    /* Class Members */

    /* 0x0 */ void* mCompressedBuffer;
    /* 0x4 */ void* mDecompressedBuffer;
    /* 0x8 */ AsyncFileStream* mFileStream;
    /* 0xC */ Mutex mMutex;
};

}


#endif
