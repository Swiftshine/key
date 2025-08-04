#ifndef FLUFF_ENVPLAYERCLONEELEMENT_H
#define FLUFF_ENVPLAYERCLONEELEMENT_H

#include "util/Player.h"
#include "graphics/PlTransMdl.h"

namespace env {
    class PlayerCloneElement {
    private:
        PlayerBase* mPlayer;
        PlTransMdl* mTransMdl;
    public:
        inline PlayerCloneElement() { }

        virtual ~PlayerCloneElement();

        inline void SetPlayer(PlayerBase* pPlayer) {
            mPlayer = pPlayer;
        }

        inline void SetTransMdl(PlTransMdl* pModel) {
            mTransMdl = pModel;
        }
    };
}

#endif
