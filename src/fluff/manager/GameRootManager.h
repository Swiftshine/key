#ifndef FLUFF_MANAGER_GAMEROOTMANAGER_H
#define FLUFF_MANAGER_GAMEROOTMANAGER_H

#include "types.h"

// size: 0x70
class GameRootManager {
    static GameRootManager* sInstance;
public:
    static inline GameRootManager* Instance() {
        return sInstance;
    }
    /* Class Members */

    STRUCT_FILL(0x6C);
    int m_6C;
};

#endif
