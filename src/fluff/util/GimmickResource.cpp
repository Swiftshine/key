#include "util/GimmickResource.h"

GimmickResource::GimmickResource(const char* pResName)
    : mResourceName(pResName)
    , mCullAll(true)
    , mGimmickHandles()
{ }

GimmickResource::~GimmickResource() { }

void GimmickResource::RegisterGimmick(Gimmick* pGmk) {
    FlfHandle handle;

    if (pGmk != nullptr) {
        handle.SetObject(pGmk->GetHandleObject());
        handle.SetID(pGmk->GetHandleID());
    } else {
        handle.SetObject(nullptr);
        handle.SetID(0);
    }

    mGimmickHandles.push_back(handle);
}

// https://decomp.me/scratch/7nV6s
void GimmickResource::Clear() {
    bool uncull = false;

    std::list<FlfHandle>::iterator it = mGimmickHandles.begin();
    
    while (it != mGimmickHandles.end()) {  
        FlfHandle handle = *it;
        FlfHandleObj** ptr;

        FLFHANDLEOBJ_DO_IF_VALID(handle, ptr) {
            uncull = uncull || !static_cast<FlfGameObj*>(*ptr)->mIsCulled;
            it++;
        } else {
            std::list<FlfHandle>::iterator i;
            std::list<FlfHandle>::erase(i, &mGimmickHandles, it);
            it = i;
        }
    }

    if (!mCullAll) {
        uncull = true;
    }

    if (uncull) {
        for (std::list<FlfHandle>::iterator it = mGimmickHandles.begin(); it != mGimmickHandles.end(); it++) {
            static_cast<FlfGameObj*>(*it->GetObject())->SetCulled(false);
        }
    }
}