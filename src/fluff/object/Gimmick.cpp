#pragma ipa file

#include "object/Gimmick.h"
#include "manager/GmkMng.h"

Gimmick::Gimmick(int gimmickID)
    : FlfGameObj(ObjectCategory::Gimmick)
    , mGimmickID(gimmickID)
    , mBuildInfoPtr(0)
{
    m_124 = 0;
    mTask = nullptr;
    mCommand = nullptr;

    GmkMng::Instance()->AddGimmick(this);
    InitCommand();
}

Gimmick::Gimmick(int gimmickID, const char* pTaskName)
    : FlfGameObj(ObjectCategory::Gimmick)
    , mGimmickID(gimmickID)
    , mBuildInfoPtr(0)
{
    m_124 = 0;
    mTask = nullptr;
    mCommand = nullptr;

    mTask.Create(
        new (gfl::HeapID::Work) gfl::Task(this, Gimmick::Update, pTaskName)
    );

    GmkMng::Instance()->mTask->MakeChild(mTask);
    GmkMng::Instance()->AddGimmick(this);
    InitCommand();
}

void Gimmick::vfB0(int arg0) { /*(this->*state1)();*/ return; }
