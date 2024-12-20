#ifndef FLUFF_FLFFRIENDMANAGER_H
#define FLUFF_FLFFRIENDMANAGER_H

#include "object/FlfFriend.h"

class FlfFriendManager {
private:
    static FlfFriendManager* sInstance;
public:
    static FlfFriendManager* GetInstance();
    static bool fn_804FA7D8();

    int fn_8039DAF8(int);
};

#endif
