#ifndef FLUFF_DEMOMANAGER_H
#define FLUFF_DEMOMANAGER_H

#include "types.h"

class DemoManager {
public:
    /* Static Variables */
    
    static DemoManager* sInstance;

    static inline DemoManager* Instance() {
        return sInstance;
    }

    /* Static Methods */

    static void SetDemoFlag(size_t* pIndex, bool value);
};

#endif
