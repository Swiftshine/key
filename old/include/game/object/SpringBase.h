#ifndef FLUFF_SPRING_BASE_H
#define FLUFF_SPRING_BASE_H

#include <game/object/FlfGameObj.h>

class SpringBase : public FlfGameObj {
public:
    SpringBase(u32, const char* taskName);
    ~SpringBase();
};

#endif
