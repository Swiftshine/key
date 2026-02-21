#ifndef FLUFF_GMKBACKDOORCANCEL_H
#define FLUFF_GMKBACKDOORCANCEL_H

#include "object/Gimmick.h"

class FlfFriend;

class GmkBackDoorCancel : public Gimmick {
public:
    void CancelMission(FlfFriend*);
};

#endif
