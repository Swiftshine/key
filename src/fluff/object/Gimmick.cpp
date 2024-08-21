#include "object/Gimmick.h"
#include "manager/GimmickManager.h"

Gimmick::Gimmick(int gmkID)
    : FlfGameObj(1)
    , mGimmickID(gmkID)
    , m_84(0)
{
    m_124 = 0;
    mTask = nullptr;
    m_12C = nullptr;

    GimmickManager::Instance()->AddGimmick(this);
    fn_8004EC4C();
}

Gimmick::Gimmick(int gmkID, const char* taskName)
    : FlfGameObj(1)
    , mGimmickID(gmkID)
    , m_84(0)
{
    m_124 = 0;
    mTask = nullptr;
    m_12C = nullptr;
    
    mTask = new gfl::Task();
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

    GimmickManager::Instance()->AddGimmick(this);
}

void Gimmick::vfB0() { /*(this->*state1)();*/ return; }