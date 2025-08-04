#ifndef FLUFF_DEMOOBJECT_H
#define FLUFF_DEMOOBJECT_H

#include "gfl/gflTask.h"
#include "gfl/gflPointer.h"

namespace demo {
    
    class DemoObject {
    public:
        DemoObject(gfl::Task* pParentTask, const char* pTaskName, uint index);
        virtual ~DemoObject();
        
        void fn_802A4F28();
        gfl::Task* InitTask(gfl::Task* pParentTask, u8 flags, const char* pTaskName, uint arg4) DONT_INLINE_CLASS;
    
        gfl::Pointer<gfl::Task> mTask; // @ 0x4
        uint m_8;
    };
}

#endif
