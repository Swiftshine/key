#define DONT_INLINE_STL

#include "manager/GmkBeadManager.h"
#include "manager/GmkMng.h"
#include "object/gimmick/GmkBeadPopItem.h"
#include "util/GimmickUtil.h"

void GmkBeadManager::InitInstance(gfl::Task* pParentTask) {
    sInstance = new (gfl::HeapID::Work) GmkBeadManager(pParentTask);
}

void GmkBeadManager::DestroyInstance() {
    delete sInstance;
    sInstance = nullptr;
}

GmkBeadManager* GmkBeadManager::GetInstance() {
    return sInstance;
}

GmkBeadManager::GmkBeadManager(gfl::Task* pParentTask) {
    // not decompiled
}

GmkBeadManager::~GmkBeadManager() {
    // nonmatching due to inlined gfl::LinkedList destructor
}

void GmkBeadManager::vfC() {
    // not decompiled

    mInfo.fn_8051CFB4();
    // mList.SomeFunction();
}


const char ON[] = "ON";
void GmkBeadManager::EnableBeadPopSwitch(
    GmkBeadPopItem* pBeadPopItem,
    const char* pTags,
    bool assignHandle
) {
    if (assignHandle) {
        if (mInfo.IsEmpty()) {
            mInfo.ResetUserHandles(pBeadPopItem);
        } else {
            mInfo.SetUserHandle(pBeadPopItem);
        }
    }

    pBeadPopItem->SetStateForTaggedObjects(ON, pTags);
}

GmkBeadManager::GmkBeadManager_Info* GmkBeadManager::GetInfoIfHandlePresent(
    FlfHandleObj* pHandleObj
) {
    if (mInfo.HasHandle(pHandleObj)) {
        return &mInfo;
    }

    return nullptr;
}

extern "C" Gimmick* CutFunction(Gimmick*);

void GmkBeadManager::fn_8051D854(bool arg1) {
    if (GmkMng::Instance() == nullptr) {
        return;
    }

    std::list<Gimmick*>& gmkList = GmkMng::Instance()->mGimmicks;

    for (std::list<Gimmick*>::iterator it = GmkMng::Instance()->mGimmicks.begin(); it != gmkList.end(); it++) {
        Gimmick* gmk = *it;

        if (GimmickUtil::IsBead(gmk->GetGimmickID())) {
            CutFunction(gmk)->SetIsInMission(arg1);
        }
    }
}
