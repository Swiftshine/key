#include "object/gimmick/GmkCartBtn.h"
#include "object/gimmick/GmkCart.h"

GmkCartBtn::GmkCartBtn()
    : Gimmick(0x115)
{
    mOption1.mBoolArray[0] = false;
    mOption2.mInt = 0;
    mCollisionEntry.Set(nullptr);
    mPartsModelSet.Set(nullptr);
    mCart = nullptr;
    mCollisionOther = nullptr;
}

GmkCartBtn::~GmkCartBtn() {
    // unmatching due to pointer dtor belonging
    // to IObjHitCB::mOption2
    // (HOW did they do this?)
}