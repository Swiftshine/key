#ifndef FLUFF_HENSHINUFO_H
#define FLUFF_HENSHINUFO_H

#include "object/player/HenshinCtrl.h"
#include "object/collision/IObjHitCB.h"

class HenshinUFO : public HenshinCtrl, public IObjHitCB { };

#endif