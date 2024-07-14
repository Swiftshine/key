#ifndef GFL_TASK_INFO_H
#define GFL_TASK_INFO_H

#include <types.h>

const u32 TASK_COUNT = 1400;

namespace gfl {

class Task;

struct TaskInfo {
    TaskInfo();
    ~TaskInfo();
    char name[23];
    u8   flags;
    void* _18;
    void* _1C;
    void* _20;
    Task* owner;
};

ASSERT_SIZE(TaskInfo, 0x28)

class TaskList {
public:
    static TaskList* Instance;
    static gfl::Task* CurrentTask;

    // helper functions for readability
    static inline void SetCurrentTask(gfl::Task* dest) { TaskList::CurrentTask = dest; }
    static inline void ClearCurrentTask() { TaskList::CurrentTask = NULL; }
public:
    inline TaskList();
    inline ~TaskList();

    static void MakeInstance();
    static void RemoveInstance();
public:
    bool active[TASK_COUNT];
    TaskInfo taskInfo[TASK_COUNT];
};

ASSERT_SIZE(TaskList, 0xE038)

} // gfl

#endif
