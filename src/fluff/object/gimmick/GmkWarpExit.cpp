#include "object/gimmick/GmkWarpExit.h"
#include "util/FullSortSceneUtil.h"
#include "graphics/FullSortScene.h"
#include "manager/StageManager.h"

const char* Names[2] = {
    "exit_B_MT",
    "exit_F_MT"
};

GmkWarpExit* GmkWarpExit::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkWarpExit(buildInfo);
}

// https://decomp.me/scratch/zxrCd
GmkWarpExit::GmkWarpExit(GimmickBuildInfo* buildInfo) 
    : Gimmick(buildInfo, "GmkWarpExit")
    , mAnimCtrl(nullptr)
    , mFbMokoMoko(nullptr)
{
    uint index = buildInfo->mFullSortSceneIndex + 5;
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
    FbMokoMoko* fbMokoMoko = (FbMokoMoko*) new (::new (gfl::HeapID::Work) FbMokoMoko(mZOrder3, 10.0f, 10.0f, "GmkWarpExit", modelWrapper, mFullSortSceneIndex, Names[0], Names[1]));
    mFbMokoMoko.Create(fbMokoMoko);

    fbMokoMoko = mFbMokoMoko.Get();
    nw4r::math::VEC2 vec = mPosition;
    fbMokoMoko->UpdateMatrix(vec);
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
