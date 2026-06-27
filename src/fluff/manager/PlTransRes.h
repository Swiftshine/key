#ifndef FLUFF_PLTRANSRESMNG_H
#define FLUFF_PLTRANSRESMNG_H

#include "types.h"

class PlTransResMng {
private:
    static PlTransResMng* sInstance;
public:
    PlTransResMng();
    DECL_WEAK virtual ~PlTransResMng();

    static void AddPlayerResourceName(uint id);
    static const char* GetPlayerResourceName(uint id);

    static void InitInstance();
    static void DestroyInstance();
};

#endif
