#ifndef FLUFF_ENVUTILSTATE_H
#define FLUFF_ENVUTILSTATE_H

#include "types.h"

namespace env {
    template <typename StateT>
    class EnvUtil_State {
    public:
        inline EnvUtil_State() { }
        inline EnvUtil_State(StateT initial) {
            mStateValue = initial;
        }
        /* 0x08 */ DECL_WEAK virtual ~EnvUtil_State() { }

        void set(StateT value) {
            mStateValue = value;
        }

        inline operator StateT() {
            return mStateValue;
        }

        /* Class Members */

        /* 0x04 */ StateT mStateValue;
    };
}

#endif
