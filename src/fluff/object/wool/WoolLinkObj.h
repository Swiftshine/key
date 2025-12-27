#ifndef FLUFF_WOOLLINKOBJ_H
#define FLUFF_WOOLLINKOBJ_H

#include "object/wool/WoolBaseTask.h"

/// @note Despite what the name suggests, this does not inherit from `WoolLinkObjBase`.
/// @note Size: `0x214`
class WoolLinkObj : public WoolBaseTask {
public:
    

    WoolLinkObj(u32, WoolBuildInfo* pWoolBuildInfo, int**, u32, u32, u32, u32);

    /* Virtual Methods */
    
    /* 0x08 */ virtual ~WoolLinkObj();
    /* 0x24 */ virtual void Interact(FlfGameObj*) override;
    /* 0x38 */ virtual ScreenPosition GetScreenPosition() override;
    /* 0x58 */ virtual void vf58() override;
    // /* 0x70 */ virtual void Update() override;
private:
    STRUCT_FILL(0x214 - sizeof(WoolBaseTask));
};

ASSERT_SIZE(WoolLinkObj, 0x214);

#endif
