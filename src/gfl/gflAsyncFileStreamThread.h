#ifndef GFL_ASYNCFILESTREAMTHREAD_H
#define GFL_ASYNCFILESTREAMTHREAD_H

#include <list>
#include "gflThread.h"


namespace gfl {
class BgArchiveLoadTask;

struct Mutex : OSMutex {
    Mutex() {
        OSInitMutex(this);
    }
};

/// @note Size: `0x24`
class AsyncFileStreamThread {
public:
    /* Static Variables */

    static AsyncFileStreamThread* sInstance;
    static Thread* sThread;
    
    inline AsyncFileStreamThread()
        : mLoadTaskList()
    {
        sThread = new (HeapID::LIB1) Thread(ProcessLoadTasks, 0x10000, 21);
        sThread->ResumeThread();
    }

    /* Class Methods */

    void AddLoadTask(BgArchiveLoadTask* pLoadTask);
    bool HasLoadTask(BgArchiveLoadTask* pLoadTask);
    bool IsLoadTaskListEmpty();

    /* Static Methods */

    static AsyncFileStreamThread* GetInstance();
    static AsyncFileStreamThread* InitInstance();
    static void DestroyInstance();
    static void* ProcessLoadTasks(void*);    

    /* Class Members */
    /* 0x00 */ Mutex mMutex;
    /* 0x18 */ std::list<BgArchiveLoadTask*> mLoadTaskList;
};

};



#endif