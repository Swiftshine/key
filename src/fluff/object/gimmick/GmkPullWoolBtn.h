#ifndef FLUFF_GMKPULLWOOLBTN_H
#define FLUFF_GMKPULLWOOLBTN_H

#include "object/gimmick/GmkWoolBtnBase.h"
#include "graphics/GimmickModelResource.h"

/// @note Size: `0x230`
class GmkPullWoolBtn : public GmkWoolBtnBase {
public:
    GmkPullWoolBtn();
    virtual ~GmkPullWoolBtn();
    
    /* Virtual Methdods */
    /* 0xD0 */ virtual void SetModelResource(const GimmickModelResource& rResource);

    /* Class Methods */
    void fn_80143A58(bool, float);
    bool fn_80143A98();
    
    STRUCT_FILL(0x210 - 0x1FC);
    bool mIsPulled;
    PAD(3);
    STRUCT_FILL(0x230 - 0x214);
};

#endif