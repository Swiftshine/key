#include "manager/GmkBeadManager.h"
#include "manager/GmkMng.h"
#include "object/gimmick/GmkBeadPopItem.h"
#include "util/GimmickUtil.h"

// #pragma inline off

void GmkBeadManager::InitInstance(gfl::Task* parentTask) {
    sInstance = new (gfl::HeapID::Work) GmkBeadManager(parentTask);
}

void GmkBeadManager::DestroyInstance() {
    delete sInstance;
    sInstance = nullptr;
}

GmkBeadManager* GmkBeadManager::GetInstance() {
    return sInstance;
}

GmkBeadManager::GmkBeadManager(gfl::Task* parentTask) {
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

void GmkBeadManager::EnableBeadPopSwitch(GmkBeadPopItem* popItem, const char* tags, bool assignHandle) {
    if (assignHandle) {
        if (mInfo.IsEmpty()) {
            mInfo.ResetUserHandles(popItem);
        } else {
            mInfo.SetUserHandle(popItem);
        }
    }

    popItem->SetStateForTaggedObjects("ON", tags);
}

GmkBeadManager::GmkBeadManager_Info* GmkBeadManager::GetInfoIfHandlePresent(FlfHandleObj* object) {
    if (mInfo.HasHandle(object)) {
        return &mInfo;
    }

    return nullptr;
}

extern "C" void TRKUARTInterruptHandler(void*);

inline void CutFunction(void* a) {
    // a temporary workaround for code merging
    TRKUARTInterruptHandler(a);
}

// nonmatching
void GmkBeadManager::fn_8051D854(bool arg1) {
    if (GmkMng::Instance() == nullptr) {
        return;
    }

    gfl::LinkedList<Gimmick*>& gimmickList = GmkMng::Instance()->GetGimmickList();

    gfl::LinkedList<Gimmick*>::NodeBase* node = GmkMng::Instance()->GetGimmickList().GetNode()->GetNext();
    gfl::LinkedList<Gimmick*>::NodeBase* end = gimmickList.GetNode();

    while (node != end) {
        Gimmick* gmk = node->ToNode()->GetData();

        if (GimmickUtil::IsBead(gmk->GetGimmickID())) {
            CutFunction(gmk);
            gmk->vf50(arg1);
        }

        node = node->GetNext();
    }
}