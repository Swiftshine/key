#ifndef FLUFF_SPRINGBASE_H
#define FLUFF_SPRINGBASE_H

#include "object/FlfGameObj.h"

// size: 0x150
class SpringBase : public FlfGameObj {
public:
    SpringBase(u32, const char* taskName);
    virtual ~SpringBase();

    /* SpringBase */

    virtual void vf68();
    virtual float GetZPos();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7C();
private:
    STRUCT_FILL(0x150 - sizeof(FlfGameObj));
};

ASSERT_SIZE(SpringBase, 0x150);

#endif
