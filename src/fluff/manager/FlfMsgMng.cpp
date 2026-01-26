#include "manager/FlfMsgMng.h"
#include "gfl/gflAlloc.h"

void FlfMsgMng::InitInstance() {
    sInstance = new (gfl::HeapID::Work) FlfMsgMng;
}

void FlfMsgMng::DestroyInstance() {
    delete sInstance;
    sInstance = nullptr;
}

void FlfMsgMng::ReleaseAll() {
    FlfMsgMng* mng = sInstance;

    for (size_t i = 0; i < mng->m_4.size(); i++) {
        delete mng->m_4[i];
    }

    mng->m_4.clear();
}

FlfMsgMng::FlfMsgMng()
    : m_4()
{ }

FlfMsgMng::~FlfMsgMng() {
    ReleaseAll();
}

// void FlfMsgMng::SplitCommonTags(const char* pTagList, std::vector<std::string>& rDst) {
//     // not decompiled
// }
