#ifndef GFL_TASK_H
#define GFL_TASK_H

#include "types.h"
#include "gflTaskInfo.h"
#include "gflFunctor.h"

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
        inline Task()
            : mFunctor()
            , mFlags(0)
            , m_14(0)
        { }


        // must rely on automatic type deduction
        template <typename OwnerT, typename FunctionT>
        inline Task(OwnerT owner, FunctionT function, const char* pTaskName)
            : mFunctor(CreateTaskFunctor<void, OwnerT, FunctionT>(owner, function))
            , mFlags(0)
            , m_14(0)
        {
            Init(pTaskName);
        }

        void Init(const char* newname);

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


        inline TaskInfo* GetTaskInfo() {
            return mTaskInfo;
        }

        inline void SetUnk14(uint value) {
            m_14 = value;
        }
        
        inline void OrUnk14(int value) {
            m_14 |= value;
        }
        
        template <typename ReturnT, typename OwnerT, typename FunctionT>
        inline Functor0<void> CreateTaskFunctor(OwnerT owner, FunctionT function) {
            FunctorClassMethod0<ReturnT, OwnerT, FunctionT>* fcm0
                = new (gfl::HeapID::LIB1) FunctorClassMethod0<ReturnT, OwnerT, FunctionT>(owner, function);

            mFunctorBase = static_cast<FunctorBase0<ReturnT>*>(fcm0);
            Functor0<ReturnT> f;
            return f;
        }

        /* Class Members */

        /* 0x04 */ TaskInfo* mTaskInfo;
        /* 0x08 */ Functor0<void> mFunctor;
        /* 0x0C */ FunctorBase0<void>* mFunctorBase;
        /* 0x10 */ int mFlags;
        /* 0x14 */ int m_14;
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
