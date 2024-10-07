#ifndef FLUFF_WORKMANAGER_H
#define FLUFF_WORKMANAGER_H


#include "work/InStageWork.h"

class WorkManager {
private:
    static WorkManager* sInstance;

    static inline WorkManager* Instance() {
        return sInstance;
    }
public:

    static InStageWork* GetInStageWork();
};

#endif