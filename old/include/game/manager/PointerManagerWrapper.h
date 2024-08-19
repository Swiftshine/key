#ifndef FLUFF_POINTER_MANAGER_WRAPPER_H
#define FLUFF_POINTER_MANAGER_WRAPPER_H

#include <game/manager/PointerManager.h>

class PointerManagerWrapper {
public:
    PointerManagerWrapper();
    ~PointerManagerWrapper();
public:
    PointerManager* mgr;
};

ASSERT_SIZE(PointerManagerWrapper, 4)

#endif
