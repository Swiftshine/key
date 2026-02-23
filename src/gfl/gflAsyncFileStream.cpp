#include "gflAsyncFileStream.h"
using namespace gfl;
#pragma readonly_strings on

AsyncFileStreamManager* AsyncFileStreamManager::sInstance;

void AsyncFileStreamManager::InitInstance() {
    sInstance = new (HeapID::LIB1) AsyncFileStreamManager;
}

void AsyncFileStreamManager::DestroyInstance() {
    delete sInstance;
    sInstance = nullptr;
}

void AsyncFileStreamManager::Reset(AsyncFileStream* pFileStream) {
    Mutex& mutex = mMutex;
    mMutex.Lock();

    if (pFileStream == mFileStream) {
        mFileStream = nullptr;
    }

    mutex.Unlock();
}

AsyncFileStream::AsyncFileStream(File* pFile, size_t compressedSize, size_t streamPos)
    : mFile(pFile)
    , mCompressedSize(compressedSize)
    , mStartStreamPos(streamPos)
    , mDecompressedBuffer(nullptr)
    , mCompressedBuffer(nullptr)
    , mNumBlocksRead(0)
    , mNumBytesRemaining(0)
    , mByteCursor(nullptr)
    , mCurrentStreamPos(0)
    , mNumBytesRead(0)
    , mBlockSize(0)
{ }

AsyncFileStream::~AsyncFileStream() {
    AsyncFileStreamManager* mgr = AsyncFileStreamManager::Instance();
    Mutex& mutex = mgr->mMutex;
    mgr->mMutex.Lock();

    if (this == mgr->mFileStream) {
        mgr->mFileStream = nullptr;
    }

    mutex.Unlock();
}

// https://decomp.me/scratch/MPna5
void AsyncFileStream::Init() {
    size_t blockSize = BPE_BLOCK_SIZE;
    size_t temp = mCompressedSize - mCurrentStreamPos;

    if (temp < BPE_BLOCK_SIZE) {
        blockSize = ROUND_UP(temp, 0x20);
    }

    mNumBlocksRead = 0;

    AsyncFileStreamManager* mgr = AsyncFileStreamManager::Instance();


    bool claimed;
    do {
        Mutex& mutex = mgr->mMutex;
        OSSleepTicks(OS_MSEC_TO_TICKS(10)); // ?
        // ghidra: OSSleepTicks(0,(OS_BUS_CLOCK / 4000) * 10);
        mutex.Lock();

        if (mgr->mFileStream != nullptr) {
            mutex.Unlock();
            claimed = false;
        } else {
            mgr->mFileStream = this;
            mutex.Unlock();
            claimed = true;
        }
    } while (!claimed);

    Mutex& mutex = mgr->mMutex;
    mutex.Lock();
    void* buf = mgr->mCompressedBuffer;
    mutex.Unlock();
    mCompressedBuffer = buf;
    mutex.Lock();
    buf = mgr->mDecompressedBuffer;
    mutex.Unlock();
    mDecompressedBuffer = buf;

    mFile->ReadAsync(mCompressedBuffer, blockSize, mStartStreamPos + mCurrentStreamPos, 2);
    mBlockSize = blockSize;
    mCurrentStreamPos += blockSize;
}
void AsyncFileStream::Update() {
    size_t blockSize;
    bool loop = true;
    
    while (loop) {
        if (mFile->GetFileStatus() == 2) {
            loop = false;
        }

        OSSleepTicks(OS_MSEC_TO_TICKS(1));
    }

    mDecompressedBuffer = mCompressedBuffer;
    mNumBlocksRead = static_cast<int>(mNumBlocksRead + 1) % 2;

    size_t num = mNumBlocksRead;

    AsyncFileStreamManager* mgr = AsyncFileStreamManager::Instance();
    Mutex& mutex = mgr->GetMutex();
    mutex.Lock();
    void* buf = reinterpret_cast<char**>(&mgr->mCompressedBuffer)[num];
    mutex.Unlock();
    mCompressedBuffer = buf;

    size_t remaining = mCompressedSize - mCurrentStreamPos;
    blockSize = 0;
    if (static_cast<int>(remaining) > 0) {
        blockSize = BPE_BLOCK_SIZE;
        if (remaining < BPE_BLOCK_SIZE) {
            blockSize = ROUND_UP(remaining, 0x20);
        }

        mFile->ReadAsync(mCompressedBuffer, blockSize, mStartStreamPos + mCurrentStreamPos, 2);
        mCurrentStreamPos += blockSize;
    }

    mByteCursor = reinterpret_cast<char*>(mDecompressedBuffer);
    mNumBytesRemaining = mBlockSize;
    mBlockSize = blockSize;
}
