#ifndef FLUFF_ENVFADEBASE_H
#define FLUFF_ENVFADEBASE_H

#include "env/EnvObject.h"
#include "env/EnvUtil_State.h"
#include "object/FlfHandleObj.h"
namespace env {

    class EnvFadeBase : public FlfHandleObj, public EnvObject {
    public:
        struct LocalState {
            int mStateValue;
        };
    public:
        EnvFadeBase(gfl::Task* pParentTask, int arg2, int arg3, const char* pTaskName, uint flagIndex);
        virtual ~EnvFadeBase();

        virtual void vf1C();
        virtual void vf20();
        virtual void vf24();
        virtual void vf28();
        virtual void vf2C();
        virtual void vf30();
        virtual void vf34();
        virtual void vf38();
        virtual void vf3C();
    private:
        int m_18;
        int m_1C;
        void* m_20;
        int m_24;
        EnvUtil_State<LocalState> mState;
    };
}

#endif
