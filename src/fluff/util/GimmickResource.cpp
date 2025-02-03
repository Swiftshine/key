#include "util/GimmickResource.h"

// every issue in this TU is because of Good-Feel's linked list

GimmickResource::GimmickResource(const char* resName)
    : mResourceName(resName)
    , m_C(true)
{ }

// https://decomp.me/scratch/I6rGn
GimmickResource::~GimmickResource() {

}

void GimmickResource::RegisterGimmick(Gimmick* gimmick) {
    gfl::LinkedList<FlfHandle>::Modifier mod;

    if (gimmick != nullptr) {
        mod.GetData().SetObject(gimmick->GetHandleObject());
        mod.GetData().SetID(gimmick->GetHandleID());
    } else {
        mod.GetData().SetObject(nullptr);
        mod.GetData().SetID(0);
    }


    mod.SetNode2(mGimmickHandles.GetNode());
    mod.AddToListAfterNode2(mGimmickHandles);
}

void GimmickResource::Clear() {
    // not decompiled
}
