#ifndef FLUFF_ENVPLAYERCLONEELEMENT_H
#define FLUFF_ENVPLAYERCLONEELEMENT_H

#include "util/Player.h"
#include "graphics/PlTransMdl.h"

namespace env {
    class PlayerCloneElement {
    public:
        /* Class Members (the vtable comes after the class members) */

        /* 0x00 */ PlayerBase* mPlayer;
        /* 0x04 */ PlTransMdl* mTransMdl;

        /* Constructor */

        inline PlayerCloneElement() { }

        /* Virtual Methods */

        /* 0x08 */ virtual ~PlayerCloneElement();
    };
}

#endif
