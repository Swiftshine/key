#ifndef GFL_TASK_H
#define GFL_TASK_H

#include <types.h>



namespace gfl {


class Task {
public:
    enum Flags {
        Inactive = 0,
        Active   = 1,
    };

    struct Info {
        char name[23];
        u8   flags;
        Task* child1;
        Task* child2;
        Task::Info* _20;
        Task* owner;
    };

public:
    Task();
    Task(const char* name);
    virtual ~Task();

    void  SetFlags(u8 newFlags);
    u8    GetFlags();
    Info* GetLeaf();
    
    // virtual void dummy();
public:
    Task::Info* info;
    void* functor;
    void* functorClassMethod;
    void* child; // ?
    void* _14; // gimmick manager?
};


namespace TaskList {
    static bool enabled[1400];
    static Task::Info taskInfo[1400];
} // namespace Tasklist

} // namespace gfl

#endif
