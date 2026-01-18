#include "gflMemoryManagement.h"
#include "gflThread.h"

#pragma readonly_strings on

using namespace gfl;

Thread::Thread(OSThreadFunc pThreadFunc, size_t stackSize, int priority)
    : mThreadFunc(pThreadFunc)
    , mStack(Alloc(HeapID::LIB1, stackSize, 0x20))
{
    OSCreateThread(&mThread, pThreadFunc, nullptr, (void*)((u32)mStack + stackSize), stackSize, priority, 1);
}

Thread::~Thread() {
    if (!OSIsThreadTerminated(&mThread)) {
        OSCancelThread(&mThread);

        if (mStack != nullptr) {
            Free(mStack);
            mStack = nullptr;
        }
    }

    if (mStack != nullptr) {
        Free(mStack);
        mStack = nullptr;
    }
}

void Thread::ResumeThread() {
    OSResumeThread(&mThread);
}

void Thread::CancelThread() {
    if (!OSIsThreadTerminated(&mThread)) {
        OSCancelThread(&mThread);

        if (mStack != nullptr) {
            Free(mStack);
            mStack = nullptr;
        }
    }
}

bool Thread::IsThreadTerminated() {
    return OSIsThreadTerminated(&mThread);
}