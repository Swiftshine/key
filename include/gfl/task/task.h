#ifndef GFL_TASK_H
#define GFL_TASK_H

#include <types.h>
#include <gfl/functor/functorbase.h>
#include <gfl/task/taskinfo.h>

namespace gfl {


class Task {
public:
    enum Flags {
        Inactive = 0,
        Active   = 1,
    };

public:
    Task();
    void Init(const char* name);

    virtual ~Task();
    virtual int fn_806459E0();

    void  SetFlags(u8 newFlags);
    u8    GetFlags();
    // TaskInfo* GetLeaf();
    
    // virtual void dummy();
public:
    TaskInfo* info;
    void* functor;
    FunctorBase0<void>* functorClassMethod; // using FunctorBase0* here for inheritance template reasons
    void* child; // ?
    void* _14; // gimmick manager?
};

ASSERT_SIZE(Task, 0x18)

} // namespace gfl

#endif
