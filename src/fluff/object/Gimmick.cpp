// note; can't link this file (or assign rodata) until SpringBase is linked

#pragma ipa file

#include "object/Gimmick.h"
#include "manager/GmkMng.h"
#include "manager/Stage.h"
#include "util/GimmickUtil.h"
#include "util/ModelUtil.h"
#include <nw4r/g3d/res/g3d_resfile.h>

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


gfl::Task* Gimmick::InitTask(const char* pTaskName) {
    mTask.Create(
        new (gfl::HeapID::Work) gfl::Task(this, Gimmick::Update, pTaskName)
    );

    GmkMng::Instance()->mTask->MakeChild(mTask);

    return mTask;
}

void Gimmick::GetResFileInfo(gfl::ResFileObject& rDst, Gimmick* pGimmick) {
    GetResFileInfo(rDst, pGimmick, pGimmick->mBuildInfoPtr->mGimmickID);
}

const char Slash[] = "/";
const char BRRES[] = ".brres";

void Gimmick::GetResFileInfo(gfl::ResFileObject& rDst, Gimmick* pGimmick, int gimmickID) {
    std::string path = "gimmick/";
    
    path += GimmickUtil::GetResourceNameByGimmickID(gimmickID);
    path += Slash;
    path += GimmickUtil::GetResourceNameByGimmickID(gimmickID);
    path += BRRES;

    ModelUtil::GetFileInfoFromArchive(rDst, path.c_str());
}


// nonmaatching
gfl::ScnMdlWrapper* Gimmick::CreateScnMdlWrapper(
    nw4r::g3d::ResFile resFile,
    const char* pResMdlName,
    uint flags,
    FullSortScene* pScene
) {
    /* something missing here */

    NW4R_G3D_RESFILE_AC_ASSERT(resFile);

    resFile.Release();
    resFile.Bind();

    nw4r::g3d::ResMdl resMdl = resFile.GetResMdl(pResMdlName);

    gfl::ScnMdlWrapper* scnMdlWrapper
        = new (gfl::HeapID::Work) gfl::ScnMdlWrapper(resMdl, flags);

    scnMdlWrapper->SetUpdate(true);

    if (pScene == nullptr) {
        pScene = Stage::Instance()->GetFullSortSceneByID(6); // game
    }
    
    pScene->AddRenderObj(scnMdlWrapper);
    FlfGameObj::UpdateMatrix();
    scnMdlWrapper->SetMatrix_thunk(mMatrix);
    return scnMdlWrapper;
}



void Gimmick::vfB0(int arg0) { /*(this->*state1)();*/ return; }

// nonmatching
template <>
gfl::FunctorBase0<void>* FunctorType::Clone(const gfl::FunctorBase0<void>* pSrc) {
    const FunctorType* functor = static_cast<const FunctorType*>(pSrc);
    return new (gfl::HeapID::LIB1) FunctorType(functor->mOwner, functor->mFunction);
}
