#ifndef FLUFF_ENVOBJECT_H
#define FLUFF_ENVOBJECT_H

#include "gfl/gflTask.h"
#include "gflPointer.h"

namespace env {
    class EnvObject {
    public:
        EnvObject(gfl::Task* parentTask, const char* taskName, uint flagIndex);
        EnvObject(gfl::Task* parentTask, u8 taskFlags, const char* taskName, uint flagIndex);
        virtual ~EnvObject();
        virtual void vfC() = 0;

        
        // called via functor class method
        void DoUpdate();
        gfl::Task* GetNewTask(gfl::Task* parentTask, u8 taskFlags, const char* taskName, uint arg4);
        // resets the flags and applies the given flags
        void SetTaskFlags(uint flags);
        // applies the given flags
        void ApplyTaskFlags(uint flags);
        void SetTaskFlagsByFlagIndex(uint index);
        
        void fn_8005E718(uint arg1, uint arg2);
        virtual void Update() = 0;
    protected:
        gfl::Pointer<gfl::Task> mTask;
        uint mTaskFlags;
    };
}


#endif
