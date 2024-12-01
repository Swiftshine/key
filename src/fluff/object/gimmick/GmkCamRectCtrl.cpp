#include "gfl/gflMemoryUtil.h"

#include "object/gimmick/GmkCamRectCtrl.h"
#include "manager/CameraManager.h"

GmkCamRectCtrl* GmkCamRectCtrl::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkCamRectCtrl(buildInfo);
}

Gimmick* GmkCamRectCtrl::SetCameraZoom(GimmickBuildInfo* buildInfo) {
    CameraManager::Instance()->fn_800544B4(buildInfo, buildInfo->GetFloatParam(ParameterID::FIRST));
    return nullptr;
}

GmkCamRectCtrl::GmkCamRectCtrl(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, "GmkCamRectCtrl")
{
    CameraManager::Instance()->fn_80056974();
}

GmkCamRectCtrl::~GmkCamRectCtrl() { }
