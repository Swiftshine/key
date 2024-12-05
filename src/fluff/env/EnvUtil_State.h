#ifndef FLUFF_ENVUTILSTATE_H
#define FLUFF_ENVUTILSTATE_H

#include "types.h"

namespace env {
    template <typename StateT>
    class EnvUtil_State {
    public:
        inline EnvUtil_State() { }
        DECL_WEAK virtual ~EnvUtil_State();
    private:
        StateT mStateValue;
    };
}

#endif
