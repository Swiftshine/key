#ifndef FLUFF_WOOLLINKOBJ_H
#define FLUFF_WOOLLINKOBJ_H

#include "object/wool/WoolBaseTask.h"

// this does not inherit from WoolLinkObjBase

// size: 0x214
class WoolLinkObj : public WoolBaseTask {
public:
    WoolLinkObj(u32, u32, int**, u32, u32, u32, u32);
    virtual ~WoolLinkObj();

    /* FlfGameObj */

    virtual void vf24() override;
    virtual gfl::Vec3 GetScreenPos() override;
    virtual void vf58() override;

    /* SpringBase */
    virtual void vf70() override;
private:
    STRUCT_FILL(0x214 - sizeof(WoolBaseTask));
};

ASSERT_SIZE(WoolLinkObj, 0x214);

#endif
