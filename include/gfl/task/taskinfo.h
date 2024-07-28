#ifndef GFL_TASK_INFO_H
#define GFL_TASK_INFO_H

#include <gfl/gfl_types.h>

const u32 TASK_COUNT = 1400;
const u32 TASK_NAME_LENGTH = 0x17;

namespace gfl {

class Task;

struct TaskInfo {
public:
    static Task* CurrentTask;
    static inline void SetCurrentTask(gfl::Task* dest) { TaskInfo::CurrentTask = dest; }
    static inline void ClearCurrentTask() { TaskInfo::CurrentTask = NULL; }
    static inline Task* GetNextSibling(TaskInfo* taskInfo) {
        while (taskInfo) {
            Task* task = taskInfo->owner;
            if (task) { return task; }
            taskInfo = taskInfo->sibling;
        }

        return NULL;
    }
    static inline Task* GetParent(TaskInfo* taskInfo) {
        TaskInfo* parentInfo = taskInfo->parent;
        if (parentInfo) { return parentInfo->owner; }
        return NULL;
    }

    static inline Task* GetNextChild(TaskInfo* taskInfo) {
        if (taskInfo) {
            taskInfo = taskInfo->child;
            Task* task;
            while (taskInfo) {
                task = taskInfo->owner;
                if (task) { return task; }
                taskInfo = taskInfo->sibling;
            }
        }

        return NULL;
    }

public:
    TaskInfo();
    ~TaskInfo();
    char name[TASK_NAME_LENGTH];
    u8   flags;
    TaskInfo* parent;
    TaskInfo* sibling;
    TaskInfo* child;
    Task* owner;
};

ASSERT_SIZE(TaskInfo, 0x28)

class TaskList {
public:
    static TaskList* Instance;

    // helper functions for readability

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

class Subtask;

class SubtaskList {
public:
    u32 count;
    Subtask* _4;
    Subtask* _8;
};
} // gfl

#endif
