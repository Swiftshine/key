#ifndef FLUFF_ENVOBJECT_H
#define FLUFF_ENVOBJECT_H

#include "gfl/gflTask.h"
#include "gflPointer.h"

namespace env {
    class EnvObject {
    public:
        EnvObject(gfl::Task* pParentTask, const char* pTaskName, u32 flagIndex);
        EnvObject(gfl::Task* pParentTask, u8 taskFlags, const char* pTaskName, u32 flagIndex);

        /* Virtual Methods */

        /* 0x08 */ virtual ~EnvObject();
        /* 0x0C */ virtual void Update() = 0;

        /* Class Methods */

        void DoUpdate(); // called via functor class method
        gfl::Task* GetNewTask(gfl::Task* pParentTask, u8 taskFlags, const char* pTaskName, u32 suspend);
        void SetTaskFlags(u32 flags); // resets the flags and applies the given flags
        void ApplyTaskFlags(u32 flags); // applies the given flags
        void SetTaskFlagsByFlagIndex(u32 index);
        void SetDescendantFlags(u32 flag, bool set);

        inline gfl::Task* GetTask() const {
            return mTask;
        }
        /* Class Members */

        /* 0x04 */ gfl::Pointer<gfl::Task> mTask;
        /* 0x08 */ u32 mTaskFlags;
    };
}


#endif
