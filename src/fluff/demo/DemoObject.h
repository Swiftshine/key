#ifndef FLUFF_DEMOOBJECT_H
#define FLUFF_DEMOOBJECT_H

#include "gfl/gflTask.h"
#include "gfl/gflPointer.h"

namespace demo {
    
    class DemoObject {
    public:

        /* Constructor */

        DemoObject(gfl::Task* pParentTask, const char* pTaskName, uint index);

        /* Virtual Methods */

        /* 0x8 */ virtual ~DemoObject();
        /* 0xC */ virtual void Update() const = 0;
        
        /* Class Methods */
        
        void DoUpdate();
        gfl::Task* InitTask(gfl::Task* pParentTask, u8 flags, const char* pTaskName, uint arg4) DONT_INLINE_CLASS;


        /* Class Members */

        /* 0x4 */ gfl::Pointer<gfl::Task> mTask;
        /* 0x8 */ uint m_8;
    };
}

#endif
