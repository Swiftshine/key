#ifndef FLUFF_PLAYERBASE_H
#define FLUFF_PLAYERBASE_H

#include "types.h"
#include "object/FlfGameObj.h"

class PlayerBase : public FlfGameObj {
public:
    ENUM_CLASS(PlayerIDs,
        Kirby,
        PrinceFluff,
    );
};
#endif