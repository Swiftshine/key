#ifndef FLUFF_ENVOBJECT_H
#define FLUFF_ENVOBJECT_H

#include "gfl/gflTask.h"
#include "gflPointer.h"

namespace env {
    class EnvObject {
    public:
        /* Constructors */

        EnvObject(gfl::Task* pParentTask, const char* pTaskName, uint flagIndex);
        EnvObject(gfl::Task* pParentTask, u8 taskFlags, const char* pTaskName, uint flagIndex);

        /* Virtual Methods */

        /* 0x08 */ virtual ~EnvObject();
        /* 0x0C */ virtual void Update() = 0;

        /* Class Methods */

        void DoUpdate(); // called via functor class method
        gfl::Task* GetNewTask(gfl::Task* pParentTask, u8 taskFlags, const char* pTaskName, uint arg4);
        void SetTaskFlags(uint flags); // resets the flags and applies the given flags
        void ApplyTaskFlags(uint flags); // applies the given flags
        void SetTaskFlagsByFlagIndex(uint index);
        void fn_8005E718(uint arg1, uint arg2);

        /* Class Members */

        /* 0x04 */ gfl::Pointer<gfl::Task> mTask;
        /* 0x08 */ uint mTaskFlags;
    };
}


#endif
