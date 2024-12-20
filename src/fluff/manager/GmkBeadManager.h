#ifndef FLUFF_GMKBEADMANAGER_H
#define FLUFF_GMKBEADMANAGER_H

#include "types.h"

class GmkBead;
class GmkBeadPopItem;

class GmkBeadManager {
private:
    static GmkBeadManager* sInstance;
public:
    static GmkBeadManager* GetInstance();
    void EnableBeadPopSwitch(GmkBeadPopItem*, const char*, bool);
};

#endif
