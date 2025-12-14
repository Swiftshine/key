#include "util/GimmickResource.h"

// every issue in this TU is because of Good-Feel's linked list

GimmickResource::GimmickResource(const char* pResName)
    : mResourceName(pResName)
    , m_C(true)
    , mGimmickHandles()
{ }

// https://decomp.me/scratch/I6rGn
GimmickResource::~GimmickResource() {

}

void GimmickResource::RegisterGimmick(Gimmick* pGmk) {
    // gfl::LinkedList<FlfHandle>::Modifier mod;

    // if (pGmk != nullptr) {
    //     mod.GetData().SetObject(pGmk->GetHandleObject());
    //     mod.GetData().SetID(pGmk->GetHandleID());
    // } else {
    //     mod.GetData().SetObject(nullptr);
    //     mod.GetData().SetID(0);
    // }

    // mod.SetNode2(mGimmickHandles.GetNode());
    // mod.AddToListAfterNode2(mGimmickHandles);
}

void GimmickResource::Clear() {
    // not decompiled
}
