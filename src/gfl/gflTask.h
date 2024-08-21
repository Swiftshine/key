#ifndef GFL_TASK_H
#define GFL_TASK_H

#include "types.h"
#include "gflTaskInfo.h"

namespace gfl {
    class Task {
    public:
        ENUM_CLASS(PollStatus,
            StillProcessing = 0,
            TaskExecuted = 1,
            ChildrenExecuted = 2
        );

        ENUM_CLASS(Flags,
            Inactive = 0,
            Active = 1
        );

    public:
        static const char DeathMarker[]; 
        static const char NoName[];
        static const char AllocError[];

    public:
        inline Task() { }

        virtual ~Task();
        virtual uint PollTask();

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
        TaskInfo* mInfo;
        void* mFunctor;
        void* mFunctorFunc; // gfl::FunctorFunc0<void(*)(), void>
        int m_10;
        int m_14; // owner?
    };

    ASSERT_SIZE(Task, 0x18);

    class Subtask {
    public:
        inline Subtask();
        inline ~Subtask();

    public:
        Subtask* m_0;
        Subtask* m_4;
        uint m_8;
        Task* mParent;
        Task* mOwner;
        uint mGroupID;
    };

    ASSERT_SIZE(Subtask, 0x18)
}

#endif