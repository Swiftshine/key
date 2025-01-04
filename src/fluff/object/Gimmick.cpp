#include "object/Gimmick.h"
#include "manager/GmkMng.h"

Gimmick::Gimmick(int gmkID)
    : FlfGameObj(1)
    , mGimmickID(gmkID)
    , mBuildInfoPtr(0)

{
    m_124 = 0;
    mTask = nullptr;
    mCommand = nullptr;

    GmkMng::Instance()->AddGimmick(this);
    InitCommand();
}

Gimmick::Gimmick(int gmkID, const char* taskName)
    : FlfGameObj(1)
    , mGimmickID(gmkID)
    , mBuildInfoPtr(0)
{
    m_124 = 0;
    mTask = nullptr;
    mCommand = nullptr;
    

    // "gfl::FunctorClassMethod0<void, Gimmick *, void (Gimmick::*)()const >"

    mTask = new gfl::Task;
    if (mTask) {
        mTask->Init(taskName);
    } else {
        delete mTask;
        mTask = nullptr;
    }

    if (!mTask) {
        delete mTask;
        mTask = nullptr;
    }

    GmkMng::Instance()->AddGimmick(this);
}

void Gimmick::vfB0() { /*(this->*state1)();*/ return; }
