#include "util/GimmickResource.h"

// every issue in this TU is because of Good-Feel's linked list

GimmickResource::GimmickResource(const char* resName)
    : mResourceName(resName)
    , m_C(true)
{ }

// https://decomp.me/scratch/I6rGn
GimmickResource::~GimmickResource() {

}

// https://decomp.me/scratch/4SCDU
void GimmickResource::RegisterGimmick(Gimmick* gimmick) {
    FlfHandle handle;

    if (gimmick != nullptr) {
        handle.SetObject(gimmick->GetHandleObject());
        handle.SetID(gimmick->GetHandleID());
    } else {
        handle.SetObject(nullptr);
        handle.SetID(0);
    }

    mGimmickHandles.Insert(handle);
}

void GimmickResource::Clear() {
    // not decompiled
}
