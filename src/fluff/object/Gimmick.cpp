#pragma ipa file

#include "object/Gimmick.h"
#include "manager/GmkMng.h"

typedef gfl::FunctorClassMethod0<void, Gimmick*, void (Gimmick::*)() const> FunctorType;

Gimmick::Gimmick(int gimmickID)
    : FlfGameObj(ObjectCategory::Gimmick)
    , mGimmickID(gimmickID)
    , mBuildInfoPtr(nullptr)
    , mStageModCtrl(nullptr)
    , mTask(nullptr)
    , mCommand(nullptr)
{
    GmkMng::Instance()->AddGimmick(this);
    InitCommand();
}

Gimmick::Gimmick(int gimmickID, const char* pTaskName)
    : FlfGameObj(ObjectCategory::Gimmick)
    , mGimmickID(gimmickID)
    , mBuildInfoPtr(nullptr)
    , mStageModCtrl(nullptr)
    , mTask(nullptr)
    , mCommand(nullptr)
{
    mTask.Create(
        new (gfl::HeapID::Work) gfl::Task(this, Gimmick::Update, pTaskName)
    );

    GmkMng::Instance()->mTask->MakeChild(mTask);
    GmkMng::Instance()->AddGimmick(this);
    InitCommand();
}

// nonmatching
Gimmick::Gimmick(GimmickBuildInfo* pBuildInfo, const char* pTaskName)
    : FlfGameObj(ObjectCategory::Gimmick)
    , mStageModCtrl(nullptr)
    , mTask(nullptr)
    , mCommand(nullptr)
{
    if (pBuildInfo != nullptr) {
        mBuildInfo = *pBuildInfo;
        mBuildInfoPtr = &mBuildInfo;
        SetPosition(mBuildInfoPtr->mPosition);
        mRotation = mBuildInfoPtr->mRotation;
        mGimmickID = pBuildInfo->mGimmickID;
        if (mBuildInfoPtr->mGimmickInfo != nullptr) {
            mBuildInfoPtr->mGimmickInfo->mGimmick = this;
        }
    } else {
        mGimmickID = 0;
        mBuildInfoPtr = nullptr;
    }

    mTask.Create(
        new (gfl::HeapID::Work) gfl::Task(this, Gimmick::Update, pTaskName)
    );

    GmkMng::Instance()->mTask->MakeChild(mTask);
    GmkMng::Instance()->AddGimmick(this);
    InitCommand();
}

void Gimmick::Update() const { }

// nonmatching
Gimmick::Gimmick(GimmickBuildInfo* pBuildInfo)
    : FlfGameObj(ObjectCategory::Gimmick)
    , mStageModCtrl(nullptr)
    , mTask(nullptr)
    , mCommand(nullptr)
{
    if (pBuildInfo != nullptr) {
        mBuildInfo = *pBuildInfo;
        mBuildInfoPtr = &mBuildInfo;
        SetPosition(mBuildInfoPtr->mPosition);
        mRotation = mBuildInfoPtr->mRotation;
        mGimmickID = pBuildInfo->mGimmickID;
        if (mBuildInfoPtr->mGimmickInfo != nullptr) {
            mBuildInfoPtr->mGimmickInfo->mGimmick = this;
        }
    } else {
        mGimmickID = 0;
        mBuildInfoPtr = nullptr;
    }

    GmkMng::Instance()->AddGimmick(this);
    InitCommand();
}

Gimmick::~Gimmick() {
    GmkMng::Instance()->RemoveGimmick(this);
    ClearGimmickCommands();

    if (mBuildInfoPtr != nullptr) {
        GimmickInfo* info = mBuildInfoPtr->mGimmickInfo;
        if (info != nullptr) {
            info->mGimmick = nullptr;
        }
    }
}


void Gimmick::vfB0(int arg0) { /*(this->*state1)();*/ return; }

template <>
gfl::FunctorBase0<void>* FunctorType::Clone(const gfl::FunctorBase0<void>* pSrc) {
    const FunctorType* functor = static_cast<const FunctorType*>(pSrc);
    return new (gfl::HeapID::LIB1) FunctorType(functor->mOwner, functor->mFunction);
}

template <>
void FunctorType::operator()() {
    
}
/*
expression preceding parentheses of apparent call must have (pointer-to-) function typeC/C++(109)
void (Gimmick::*FunctorType::mFunction)() const
*/