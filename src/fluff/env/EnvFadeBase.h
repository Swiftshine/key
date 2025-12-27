#ifndef FLUFF_ENVFADEBASE_H
#define FLUFF_ENVFADEBASE_H

#include "env/EnvObject.h"
#include "env/EnvUtil_State.h"
#include "object/FlfHandleObj.h"
namespace env {

    class EnvFadeBase : public FlfHandleObj, public EnvObject {
        /* Structures */

        struct LocalState {
            int mStateValue;
        };

        

        EnvFadeBase(gfl::Task* pParentTask, int arg2, int arg3, const char* pTaskName, uint flagIndex);

        /* Virtual Methods */

        /* 0x08 */ virtual ~EnvFadeBase();

        /* 0x1C */ virtual void vf1C();
        /* 0x20 */ virtual void vf20();
        /* 0x24 */ virtual void vf24();
        /* 0x28 */ virtual void vf28();
        /* 0x2C */ virtual void vf2C();
        /* 0x30 */ virtual void vf30();
        /* 0x34 */ virtual void vf34();
        /* 0x38 */ virtual void vf38();
        /* 0x3C */ virtual void vf3C();

        /* Class Members */

        /* 0x18 */ int m_18;
        /* 0x1C */ int m_1C;
        /* 0x20 */ void* m_20;
        /* 0x24 */ int m_24;
        /* 0x28 */ EnvUtil_State<LocalState> mState;
    };
}

#endif
