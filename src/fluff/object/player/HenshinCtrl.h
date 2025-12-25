#ifndef FLUFF_HENSHINCTRL_H
#define FLUFF_HENSHINCTRL_H

#include "object/FlfHandleObj.h"

class PlayerBase;

/// @brief A base class for player transformations.
/// @note Size: `0x58`
class HenshinCtrl {
public:
    virtual ~HenshinCtrl();

    /* Class Members */
    /* 0x04 */ FlfHandle mPlayerHandle;
    /* 0x0C */ STRUCT_FILL(0x4C); 
};

// todo - make separate headers for these
class HenshinSubmarine : public HenshinCtrl { };
class HenshinString : public HenshinCtrl { };
class HenshinBoat : public HenshinCtrl { };
class HenshinRobot : public HenshinCtrl { };
class HenshinVehicle : public HenshinCtrl { };
class HenshinSplash : public HenshinCtrl { };
class HenshinAquaRide : public HenshinCtrl { };
class HenshinRocket : public HenshinCtrl { };
class HenshinWarpStar : public HenshinCtrl { };
class HenshinUFO : public HenshinCtrl { };
class HenshinBrightRobot : public HenshinCtrl { };
class HenshinTrainFree : public HenshinCtrl { };

#endif