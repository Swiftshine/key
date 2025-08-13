#ifndef FLUFF_ENVUTILSTATE_H
#define FLUFF_ENVUTILSTATE_H

#include "types.h"

namespace env {
    template <typename StateT>
    class EnvUtil_State {
    public:
        /* Constructor */

        inline EnvUtil_State() { }

        /* Virtual Methods */

        /* 0x08 */ DECL_WEAK virtual ~EnvUtil_State();

        /* Class Members */

        /* 0x04 */ StateT mStateValue;
    };
}

#endif
