#ifndef FLUFF_GMKFRIENDFACTORYINSTAGE_H
#define FLUFF_GMKFRIENDFACTORYINSTAGE_H

#include "object/Gimmick.h"

class FlfFriend;

class GmkFriendFactoryInStage : public Gimmick {
public:
    FlfFriend* GetFriend();
};

#endif
