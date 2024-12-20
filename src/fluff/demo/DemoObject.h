#ifndef FLUFF_DEMOOBJECT_H
#define FLUFF_DEMOOBJECT_H

#include "gfl/gflTask.h"
#include "gfl/gflPointer.h"
namespace demo {
    class DemoObject {
    public:
        DemoObject(gfl::Task* parentTask, const char* taskName, uint index);
        virtual ~DemoObject();
        
        void fn_802A4F28();
        gfl::Task* InitTask(gfl::Task* parent, u8 flags, const char* taskName, uint arg4) DONT_INLINE_CLASS;
    private:
        gfl::Pointer<gfl::Task> mTask;
        uint m_8;
    };
}

#endif
