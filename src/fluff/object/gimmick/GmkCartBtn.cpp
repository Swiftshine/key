#include "object/gimmick/GmkCartBtn.h"
#include "object/gimmick/GmkCart.h"

GmkCartBtn::GmkCartBtn()
    : Gimmick(0x115)
{
    m_134 = false;
    mResFileObject = nullptr;
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

    m_134 = true;
    
    if (mCartCollision != nullptr) {
        ret = mCartCollision->OnCollision(colSelf, colOther);
    }
    
    m_134 = false;
    return ret;   
}

int GmkCartBtn::vf74() {
    int ret = 1;

    m_134 = true;

    if (mCart != nullptr) {
        ret = mCart->vf74();
    }
    
    m_134 = false;
    return ret;
}


int GmkCartBtn::vf78() {
    int ret = 1;

    m_134 = true;

    if (mCart != nullptr) {
        ret = mCart->vf78();
    }
    
    m_134 = false;
    return ret;
}


int GmkCartBtn::vf7C() {
    int ret = 1;

    m_134 = true;

    if (mCart != nullptr) {
        ret = mCart->vf7C();
    }
    
    m_134 = false;
    return ret;
}


int GmkCartBtn::vf8C() {
    int ret = 1;

    m_134 = true;

    if (mCart != nullptr) {
        ret = mCart->vf8C();
    }
    
    m_134 = false;
    return ret;
}
