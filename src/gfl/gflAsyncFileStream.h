#ifndef GFL_ASYNCFILESTREAM_H
#define GFL_ASYNCFILESTREAM_H

#include <revolution/OS.h>
#include "gflFile.h"

namespace gfl {

class AsyncFileStream {
public:
    AsyncFileStream(File* pFile, size_t compressedSize, size_t streamPos);
    virtual ~AsyncFileStream();
    
    void Update();

    // getc equivalent
    inline char GetByte() {
        char result = *mByteCursor;
        mByteCursor++;
        return result;
    }
public:
    File* mFile; // @ 0x4
    size_t mCompressedSize; // @ 0x8
    size_t mStartStreamPos; // @ 0xC
    void* mDecompressedBuffer; // @ 0x10
    void* mCompressedBuffer; // @ 0x14
    int m_18;
    int m_1C;
    char* mByteCursor; // @ 0x20
    size_t mCurrentStreamPos; // @ 0x24
    int m_28;
    int m_2C;
};

ASSERT_SIZE(AsyncFileStream, 0x30);

#define GFL_ASYNCFILESTREAM_BUFFER_SIZE 0x20000

// size: 0x24
class AsyncFileStreamManager {
private:
    static AsyncFileStreamManager* sInstance;
public:
    static inline AsyncFileStreamManager* Instance() {
        return sInstance;
    }

    static void MakeInstance();
    static void DestroyInstance();
    void Reset(AsyncFileStream* pFileStream);
private:
    void* mCompressedBuffer; // @ 0x0
    void* mDecompressedBuffer; // @ 0x4
    AsyncFileStream* mFileStream; // @ 0x8
    OSMutex mMutex; // @ 0xC
};

}


#endif
