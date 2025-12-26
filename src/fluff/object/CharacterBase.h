#ifndef FLUFF_CHARACTERBASE_H
#define FLUFF_CHARACTERBASE_H

#include "object/EnemyBase.h"

/// @note Size: `0x1798`
class CharacterBase : public EnemyBase {
public:
    STRUCT_FILL(0x1798 - 0x1774);
};

#endif