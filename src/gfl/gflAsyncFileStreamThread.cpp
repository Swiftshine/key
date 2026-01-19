#include "gflAsyncFileStreamThread.h"
#include <algorithm>

using namespace gfl;

AsyncFileStreamThread* AsyncFileStreamThread::GetInstance() {
    return sInstance;
}

AsyncFileStreamThread* AsyncFileStreamThread::InitInstance() {
    sInstance = new (HeapID::LIB1) AsyncFileStreamThread();
    return sInstance;
}

void AsyncFileStreamThread::DestroyInstance() {
    // not decompiled
}


// https://decomp.me/scratch/sg6vH
void AsyncFileStreamThread::AddLoadTask(BgArchiveLoadTask* pLoadTask) {
    OSLockMutex(&mMutex);

    // not decompiled
    mLoadTaskList.push_back(pLoadTask); // except it's a different, uninlined version

    OSUnlockMutex(&mMutex);
}

// https://decomp.me/scratch/ijCtd
bool AsyncFileStreamThread::HasLoadTask(BgArchiveLoadTask* pLoadTask) {
    OSLockMutex(&mMutex);

    std::list<BgArchiveLoadTask*>::iterator it = std::find(mLoadTaskList.begin(), mLoadTaskList.end(), pLoadTask);

    if (it != mLoadTaskList.end()) {
        OSUnlockMutex(&mMutex);
        return false;
    }

    OSUnlockMutex(&mMutex);
    return true;
}


bool AsyncFileStreamThread::IsLoadTaskListEmpty() {
    OSLockMutex(&mMutex);
    size_t size = mLoadTaskList.size();
    OSUnlockMutex(&mMutex);
    return size == 0;
}

void* AsyncFileStreamThread::ProcessLoadTasks(void*) {
    // not decompiled
    return nullptr;
}