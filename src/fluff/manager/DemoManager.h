#ifndef FLUFF_DEMOMANAGER_H
#define FLUFF_DEMOMANAGER_H

#include "types.h"

class DemoManager {
private:
    static DemoManager* sInstance;
public:
    static inline DemoManager* Instance() {
        return sInstance;
    }

    static void SetDemoFlag(size_t* index, bool value);
};

#endif
