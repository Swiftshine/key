#ifndef FLUFF_FLFFRIENDMANAGER_H
#define FLUFF_FLFFRIENDMANAGER_H

#include "object/FlfFriend.h"

class FlfFriendManager {
private:
    /* Static Variables */

    static FlfFriendManager* sInstance;
public:

    /* Static Methods */

    static FlfFriendManager* GetInstance();
    static bool fn_804FA7D8();

    /* Class Methods */
    
    FlfFriend* fn_8039DAF8(int);
};

#endif
