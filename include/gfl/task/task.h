#ifndef GFL_TASK_H
#define GFL_TASK_H

#include <types.h>
#include <gfl/functor/functorbase.h>
#include <gfl/functor/functorfunc.h>
#include <gfl/task/taskinfo.h>


namespace gfl {

namespace TaskStatus {
    enum TaskStatusEnum {
        StillProcessing     = 0,
        TaskExecuted        = 1,
        ChildrenExecuted    = 2,
    };
} // TaskStatus

class Task {
public:
    static const char DeathMarker[]; 
    static const char NoName[];
    static const char AllocError[];
    enum Flags {
        Inactive = 0,
        Active   = 1,
    };

public:
    inline Task();
    void Init(const char* name);

    virtual ~Task();
    virtual u32 GetTaskStatus();

    Task* GetParent();
    Task* GetNextChild();
    Task* GetNextSibling();
    void  MakeChild(Task* dest);
    void  Replace(Task* other);
    void  SetFlags(u8 newFlags);
    u8    GetFlags();
    void  SetTaskName(const char* newName);
    void  CreateSubtask(u8 groupID);
public:
    TaskInfo* info;
    void* functor;
    // FunctorBase0<void>* functorClassMethod; // using FunctorBase0* here for inheritance template reasons
    FunctorFunc0<void(*)(), void>* functorFunc;
    // it probably actually is a FunctorBase<void>* because they seem to be different every time
    int _10; // ?
    int _14; // gimmick manager?
};

ASSERT_SIZE(Task, 0x18)

class Subtask {
public:
    inline Subtask();
    inline ~Subtask();

public:
    Subtask* _0;
    Subtask* _4;
    u32 _8;
    Task* parent;
    Task* owner;
    u32 groupID;
};

ASSERT_SIZE(Subtask, 0x18)


} // namespace gfl

#endif
