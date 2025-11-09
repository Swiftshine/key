#include "object/gimmick/GmkCartBtn.h"
#include "object/gimmick/GmkCart.h"
#include "util/FullSortSceneUtil.h"
#include "object/collision/CollisionTemplate.h"
#include "gfl/gflVec2.h"
#include "graphics/FlfMdlDraw.h"
#include "manager/Stage.h"

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

GmkCartBtn::~GmkCartBtn() { }

// https://decomp.me/scratch/jD8Dg
void GmkCartBtn::Init(ButtonBuildInfo* buildInfo) {
    Gimmick* owner = buildInfo->mOwner;
    mCart = owner;
    mCartCollision = buildInfo->mCollision;

    nw4r::math::VEC3 pos(buildInfo->mOffset + owner->mPosition);
    pos.z = FullSortSceneUtil::GetZOrder(buildInfo->mSceneIndex, buildInfo->m_14);
    SetPosition(pos);
    UpdateMatrix();
    CollisionTemplate colTemplate;
    colTemplate.m_14 = buildInfo->m_C;
    colTemplate.mCollisionFlags = 1;
    colTemplate.m_4 = 0x19;
    colTemplate.m_8 = 2;
    colTemplate.m_C.x = gfl::Vec2::Zero.x;
    colTemplate.m_C.y = gfl::Vec2::Zero.y;
    
    CollisionEntry* entry = CollisionEntry::Get(&colTemplate, this, nullptr, mMatrix, "GmkCartBtn");
    mCollisionEntry.Create(entry);

    entry = mCollisionEntry.Get();

    entry->ResetMatrix(true);

    mFlags |= mCart->mFlags;

    {
        gfl::ResFileObject obj;
        FlfMdlDraw::GetFileInfoFromArchive(obj, "gimmick/button/button.brres");
        mResFileObject = obj;
    }

    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(buildInfo->mSceneIndex);
    mPartsModelSet.Create(gfl::HeapID::Work);
    mPartsModelSet->RegisterResources(mResFileObject, "pull", "button_shadow", scene, 0);
    mPartsModelSet->SetMatrix(0.01f, mMatrix, true);
}

void GmkCartBtn::Update() {
    UpdateMatrix();
    mPartsModelSet->SetMatrix(0.01f, mMatrix, true);
}

GmkCart* GmkCartBtn::GetCart() {
    return dynamic_cast<GmkCart*>(mCart);
}

bool GmkCartBtn::OnCollision(CollisionInfo* colSelf, CollisionInfo* colOther, gfl::Vec3& pos) {
    bool ret = true;

    m_134 = true;
    
    if (mCartCollision != nullptr) {
        ret = mCartCollision->OnCollision(colSelf, colOther, pos);
    }
    
    m_134 = false;
    return ret;   
}

int GmkCartBtn::vf74(IObjHitCB* other) {
    int ret = 1;

    m_134 = true;

    if (mCart != nullptr) {
        ret = mCart->vf74(other);
    }
    
    m_134 = false;
    return ret;
}


int GmkCartBtn::vf78(IObjHitCB* other) {
    int ret = 1;

    m_134 = true;

    if (mCart != nullptr) {
        ret = mCart->vf78(other);
    }
    
    m_134 = false;
    return ret;
}


int GmkCartBtn::vf7C(IObjHitCB* other, int arg2) {
    int ret = 1;

    m_134 = true;

    if (mCart != nullptr) {
        ret = mCart->vf7C(other, arg2);
    }
    
    m_134 = false;
    return ret;
}


int GmkCartBtn::vf8C(IObjHitCB* other, int arg2) {
    int ret = 1;

    m_134 = true;

    if (mCart != nullptr) {
        ret = mCart->vf8C(other, arg2);
    }
    
    m_134 = false;
    return ret;
}
