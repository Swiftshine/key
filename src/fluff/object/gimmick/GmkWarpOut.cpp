#include "object/gimmick/GmkWarpOut.h"
#include "util/FullSortSceneUtil.h"
#include "manager/Stage.h"

GmkWarpOut* GmkWarpOut::Build(GimmickBuildInfo* pBuildInfo) {
    return new (gfl::HeapID::Work) GmkWarpOut(pBuildInfo);
}

GmkWarpOut::GmkWarpOut(GimmickBuildInfo* pBuildInfo)
    : Gimmick(pBuildInfo, "GmkWarp")
    , mAnmCtrl(nullptr)
{
    mPosition.z = FullSortSceneUtil::GetZOrder(pBuildInfo->mSceneID, 4);
    FlfGameObj::UpdateMatrix();
    
    gfl::ResFileObject resFileObject;
    GetResFileObject(resFileObject, this);

    const char* name = "warp_02";
    mAnmCtrl.Create(new (gfl::HeapID::Work) NwAnmCtrl(1, resFileObject, name));
    mAnmCtrl->PlayAnimationByNameAndIndex(0, "warp_02_000");

    NwAnmCtrl* anmCtrl = mAnmCtrl;
    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(pBuildInfo->mSceneID);

    anmCtrl->SetFullSortSceneModelWrapper(scene, 0);
    mAnmCtrl->mScnMdlWrapper->SetMatrix_thunk(mMatrix);
}

GmkWarpOut::~GmkWarpOut() { }