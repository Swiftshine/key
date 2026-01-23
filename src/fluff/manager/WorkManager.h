#ifndef FLUFF_WORKMANAGER_H
#define FLUFF_WORKMANAGER_H

#include "work/InStageWork.h"

class WorkManager {
public:
    /* Static Variables */
    static WorkManager* sInstance;

    static inline WorkManager* Instance() {
        return sInstance;
    }

    /* Static Methods */
    
    static InStageWork* GetInStageWork();
};

#endif
