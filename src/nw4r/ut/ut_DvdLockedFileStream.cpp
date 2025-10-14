#include <nw4r/ut.h>

#include <revolution/OS.h>

namespace nw4r {
namespace ut {

NW4R_UT_RTTI_DEF_DERIVED(DvdLockedFileStream, DvdFileStream);

OSThreadQueue DvdLockedFileStream::sThreadQueue;
bool DvdLockedFileStream::sInitialized = false;
OSMutex DvdLockedFileStream::sMutex;

void DvdLockedFileStream::InitMutex_() {
    BOOL enabled = OSDisableInterrupts();

    if (!sInitialized) {
        OSInitMutex(&sMutex);
        OSInitThreadQueue(&sThreadQueue);
        sInitialized = true;
    }

    OSRestoreInterrupts(enabled);
}

DvdLockedFileStream::DvdLockedFileStream(s32 entrynum)
    : DvdFileStream(entrynum) {
    mCancelFlag = false;
    InitMutex_();
}

DvdLockedFileStream::DvdLockedFileStream(const DVDFileInfo* pInfo, bool close)
    : DvdFileStream(pInfo, close) {
    mCancelFlag = false;
    InitMutex_();
}

DvdLockedFileStream::~DvdLockedFileStream() {}

void DvdLockedFileStream::Close() {
    DvdFileStream::Close();
    mCancelFlag = false;
}

s32 DvdLockedFileStream::Read(void* pDst, u32 size) {
    BOOL enabled;
    s32 result;
       
    if (!LockMutex()) {
        return -3;
    }

    result = DvdFileStream::Read(pDst, size);
    enabled = OSDisableInterrupts();
    OSUnlockMutex(&sMutex);
    OSWakeupThread(&sThreadQueue);
    OSRestoreInterrupts(enabled);
    return result;
}

s32 DvdLockedFileStream::Peek(void* pDst, u32 size) {
    BOOL enabled;
    s32 result;
       
    if (!LockMutex()) {
        return -3;
    }
    
    result = DvdFileStream::Peek(pDst, size);
    enabled = OSDisableInterrupts();
    OSUnlockMutex(&sMutex);
    OSWakeupThread(&sThreadQueue);
    OSRestoreInterrupts(enabled);
    return result;
}

void DvdLockedFileStream::Cancel() {
    BOOL enabled = OSDisableInterrupts();
    mCancelFlag = true;
    OSWakeupThread(&sThreadQueue);
    OSRestoreInterrupts(enabled);
    DvdFileStream::Cancel();
}

inline bool DvdLockedFileStream::LockMutex() {
    BOOL enabled = OSDisableInterrupts();

    while (!OSTryLockMutex(&sMutex)) {
        OSSleepThread(&sThreadQueue);

        if (mCancelFlag) {
            OSRestoreInterrupts(enabled);
            return false;
        }
    }

    OSRestoreInterrupts(enabled);
    return true;
}

} // namespace ut
} // namespace nw4r
