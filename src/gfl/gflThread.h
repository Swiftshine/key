#ifndef GFL_THREAD_H
#define GFL_THREAD_H

#include <revolution/OS.h>
#include "gflAlloc.h"

namespace gfl {

/// @note Size: `0x328`
class Thread {
public:
    Thread(OSThreadFunc pThreadFunc, size_t stackSize, int priority);
    virtual ~Thread();

    /* Class Methods */
    
    void ResumeThread();
    void CancelThread();
    bool IsThreadTerminated();

    /* Class Members */

    /* 0x004 */ OSThreadFunc mThreadFunc;
    /* 0x008 */ OSThread mThread;
    /* 0x320 */ void* mStack;
    /* 0x324 */ int m_324; // never used
};


};
#endif