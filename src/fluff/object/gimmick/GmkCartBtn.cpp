#include "object/gimmick/GmkCartBtn.h"
#include "object/gimmick/GmkCart.h"

GmkCartBtn::GmkCartBtn()
    : Gimmick(0x115)
{
    mOption1.mBoolArray[0] = false;
    mOption2.mPointer = 0;
    mCollisionEntry.Set(nullptr);
    mPartsModelSet.Set(nullptr);
    mCart = nullptr;
    mCartCollision = nullptr;
}

GmkCartBtn::~GmkCartBtn() {
    // nonmatching
}

void GmkCartBtn::fn_802513F0(int* arg1) {
    // not decompiled
}

void GmkCartBtn::Update() {
    UpdateMatrix();
    mPartsModelSet->SetMatrix(0.0099999998f, mMatrix, true);
}

GmkCart* GmkCartBtn::GetCart() {
    return dynamic_cast<GmkCart*>(mCart);
}

bool GmkCartBtn::OnCollision(CollisionInfo* colSelf, CollisionInfo* colOther) {
    bool ret = true;

    mOption1.mBool = true;
    
    if (mCartCollision != nullptr) {
        ret = mCartCollision->OnCollision(colSelf, colOther);
    }
    
    mOption1.mBool = false;
    return ret;   
}

int GmkCartBtn::vf74() {
    int ret = 1;

    mOption1.mBool = true;

    if (mCart != nullptr) {
        ret = mCart->vf74();
    }
    
    mOption1.mBool = false;
    return ret;
}


int GmkCartBtn::vf78() {
    int ret = 1;

    mOption1.mBool = true;

    if (mCart != nullptr) {
        ret = mCart->vf78();
    }
    
    mOption1.mBool = false;
    return ret;
}


int GmkCartBtn::vf7C() {
    int ret = 1;

    mOption1.mBool = true;

    if (mCart != nullptr) {
        ret = mCart->vf7C();
    }
    
    mOption1.mBool = false;
    return ret;
}


int GmkCartBtn::vf8C() {
    int ret = 1;

    mOption1.mBool = true;

    if (mCart != nullptr) {
        ret = mCart->vf8C();
    }
    
    mOption1.mBool = false;
    return ret;
}
