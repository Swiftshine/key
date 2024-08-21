#ifndef GFL_TASKINFO_H
#define GFL_TASKINFO_H

#define GFL_TASKINFO_TASK_COUNT 1400


#include <string.h> // memset

#include "types.h"

namespace gfl {
    class Task;

    class TaskInfo {
    private:
        static Task* sCurrentTask;
    public:
        DECL_WEAK ~TaskInfo();
        TaskInfo();

        static inline Task* GetCurrentTask() {
            return sCurrentTask;
        }

        static inline void SetCurrentTask(Task* t) {
            sCurrentTask = t;
        }

        static inline void ClearCurrentTask() {
            sCurrentTask = nullptr;
        }


        inline TaskInfo* GetParentInfo() {
            return mParentInfo;
        }

        inline TaskInfo* GetSiblingInfo() {
            return mSiblingInfo;
        }

        inline TaskInfo* GetChildInfo() {
            return mChildInfo;
        }

        inline Task* GetOwner() {
            return mOwner;
        }

        static inline Task* GetParentTask(TaskInfo* ti) {
            TaskInfo* pi = ti->GetParentInfo();
            if (pi) {
                return pi->GetOwner();
            }

            return nullptr;
        }

        static inline Task* GetNextSiblingTask(TaskInfo* ti) {
            while (ti) {
                Task* t = ti->GetOwner();
                if (t) {
                    return t;
                }
                ti = ti->GetSiblingInfo();
            }

            return nullptr;
        }

        static inline Task* GetNextChildTask(TaskInfo* ti) {
            if (ti) {
                ti = ti->GetChildInfo();
                Task* t;
                while (ti) {
                    t = ti->GetOwner();
                    if (t) {
                        return t;
                    }
                    ti = ti->GetSiblingInfo();
                }
            }

            return nullptr;
        }
        
    private:
        char mName[0x17];
        u8 mFlags;
        TaskInfo* mParentInfo;
        TaskInfo* mSiblingInfo;
        TaskInfo* mChildInfo;
        Task* mOwner;
    }; 

    ASSERT_SIZE(TaskInfo, 0x28);

    class TaskList {
    private:
        static TaskList* sInstance;
    public:
        inline TaskList() {
            memset(mTaskActive, false, GFL_TASKINFO_TASK_COUNT);
        }

        inline ~TaskList() { }

        static void InitInstance();
        static void DestroyInstance();
    private:
        bool mTaskActive[GFL_TASKINFO_TASK_COUNT];
        TaskInfo mTaskInfo[GFL_TASKINFO_TASK_COUNT];
    };

    ASSERT_SIZE(TaskList, 0xE038);
}

#endif