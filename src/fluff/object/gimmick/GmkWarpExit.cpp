#include "object/gimmick/GmkWarpExit.h"
#include "util/FullSortSceneUtil.h"
#include "graphics/FullSortScene.h"
#include "manager/StageManager.h"

const char* exit_B_MT = "exit_B_MT";
const char* exit_F_MT = "exit_F_MT";

GmkWarpExit* GmkWarpExit::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkWarpExit(buildInfo);
}

GmkWarpExit::GmkWarpExit(GimmickBuildInfo* buildInfo) 
    : Gimmick(buildInfo, "GmkWarpExit")
    , mAnimCtrl(nullptr)
    , mFbMokoMoko(nullptr)
{
    uint index = buildInfo->GetIntParam(Parameter::FullsortSceneIndex) + 5;
    mFullSortSceneIndex = index;
    mZOrder3 = FullSortSceneUtil::GetZOrder(index, 3);
    mZOrder4 = FullSortSceneUtil::GetZOrder(index, 4);
    mPosition.z = mZOrder4;

    UpdateMatrix();
    gfl::ResFileObject resFileObject;
    GetResFileInfo(resFileObject, this);

    NwAnmCtrl* animCtrl = new (gfl::HeapID::Work) NwAnmCtrl(0, resFileObject, "warpExit_01");
    mAnimCtrl.Create(animCtrl);
    animCtrl = mAnimCtrl.Get();

    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(mFullSortSceneIndex);
    animCtrl->SetFullSortSceneModelWrapper(scene, 0x204);
    mAnimCtrl->GetScnMdlWrapper()->SetMatrix_thunk(mMatrix);
    mAnimCtrl->GetScnMdlWrapper()->vf30(5.0f);

    gfl::ScnMdlWrapper* modelWrapper = mAnimCtrl->GetScnMdlWrapper();

    // note to self; this calls a thunk to the version of operator new seen above
    FbMokoMoko* fbMokoMoko = ::new (gfl::HeapID::Work) FbMokoMoko(mZOrder3, 10.0f, 10.0f, "GmkWarpExit", modelWrapper, mFullSortSceneIndex, exit_B_MT, exit_F_MT);
    mFbMokoMoko.Create(fbMokoMoko);
    fbMokoMoko = mFbMokoMoko.Get();

    fbMokoMoko->UpdateMatrix(nw4r::math::VEC2(mPosition));
    mFbMokoMoko->SetUnk150(true);
    mFbMokoMoko->vf30(5.0f);
}

GmkWarpExit::~GmkWarpExit() { }

void GmkWarpExit::vf64(bool arg1) {
    Gimmick::vf64(arg1);
}

void GmkWarpExit::Update() {
    return;
}
