#ifndef FLUFF_GMKBACKDOOR_H
#define FLUFF_GMKBACKDOOR_H

#include "object/Gimmick.h"

class FlfFriend;

/// @note Size: `0x160`
class GmkBackDoor : public Gimmick {
public:
    void fn_80329320(FlfFriend* pFriend, bool);
    STRUCT_FILL(0x30);
};

#endif
