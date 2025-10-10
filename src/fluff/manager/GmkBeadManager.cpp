#include "manager/GmkBeadManager.h"
#include "manager/GmkMng.h"
#include "object/gimmick/GmkBeadPopItem.h"
#include "util/GimmickUtil.h"

// #pragma inline off

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

    pBeadPopItem->SetStateForTaggedObjects("ON", pTags);
}

GmkBeadManager::GmkBeadManager_Info* GmkBeadManager::GetInfoIfHandlePresent(
    FlfHandleObj* pHandleObj
) {
    if (mInfo.HasHandle(pHandleObj)) {
        return &mInfo;
    }

    return nullptr;
}

extern "C" void TRKUARTInterruptHandler();

inline void CutFunction() {
    // a temporary workaround for code merging
    TRKUARTInterruptHandler();
}

// https://decomp.me/scratch/wZpkl
void GmkBeadManager::fn_8051D854(bool arg1) {
    if (GmkMng::Instance() == nullptr) {
        return;
    }

    gfl::LinkedList<Gimmick*>& gimmickList = GmkMng::Instance()->mGimmicks;

    gfl::LinkedList<Gimmick*>::NodeBase* node = GmkMng::Instance()->mGimmicks.GetNode()->GetNext();
    gfl::LinkedList<Gimmick*>::NodeBase* end = gimmickList.GetNode();

    while (node != end) {
        Gimmick* gmk = node->ToNode()->GetData();

        if (GimmickUtil::IsBead(gmk->GetGimmickID())) {
            CutFunction();
            gmk->vf50(arg1);
        }

        node = node->GetNext();
    }
}