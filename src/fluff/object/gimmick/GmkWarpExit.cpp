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

// https://decomp.me/scratch/Vutit
GmkWarpExit::GmkWarpExit(GimmickBuildInfo* buildInfo) 
    : Gimmick(buildInfo, "GmkWarpExit")
    , mAnimCtrl(nullptr)
    , mFbMokoMoko(nullptr)
{
    uint index = buildInfo->mFullSortSceneIndex + 5;
    mZOrder3 = FullSortSceneUtil::GetZOrder(index, 3);
    float zOrder = FullSortSceneUtil::GetZOrder(index, 4);
    mZOrder4 = zOrder;
    mPosition.z = zOrder;

    UpdateMatrix();
    gfl::ResFileObject resFileObject;
    GetResFileInfo(resFileObject, this);

    NwAnmCtrl* animCtrl = new (gfl::HeapID::Work) NwAnmCtrl(0, resFileObject, "warpExit_01");
    mAnimCtrl.Create(animCtrl);

    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(mFullSortSceneIndex);
    animCtrl->SetFullSortSceneModelWrapper(scene, 0x204);
    animCtrl->GetScnMdlWrapper()->SetMatrix_thunk(mMatrix);
    mAnimCtrl->GetScnMdlWrapper()->vf30(5.0f);

    gfl::ScnMdlWrapper* modelWrapper = mAnimCtrl->GetScnMdlWrapper();

    FbMokoMoko* fbMokoMoko = nullptr;

    // im supposed to use the operator new to specify a heap ID
    // but am i also supposed to use the G3dObj operator new somehow?

    // fbMokoMoko = new (gfl::HeapID::Work) FbMokoMoko(mZOrder3, 10.0f, 10.0f, "GmkWarpExit", modelWrapper, mFullSortSceneIndex, &Names[0], &Names[1]);
    fbMokoMoko = new (fbMokoMoko) FbMokoMoko(mZOrder3, 10.0f, 10.0f, "GmkWarpExit", modelWrapper, mFullSortSceneIndex, &Names[0], &Names[1]);
    mFbMokoMoko.Create(fbMokoMoko);

    nw4r::math::VEC2 vec(mPosition);
    fbMokoMoko->UpdateMatrix(vec);
    fbMokoMoko->SetUnk150(true);
    fbMokoMoko->vf30(5.0f);
}

GmkWarpExit::~GmkWarpExit() { }

void GmkWarpExit::vf64(bool arg1) {
    Gimmick::vf64(arg1);
}

void GmkWarpExit::Update() {
    return;
}
