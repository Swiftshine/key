#include "gfl/gflMemoryUtil.h"

#include "object/gimmick/GmkCamRectCtrl.h"
#include "manager/CamMng.h"

GmkCamRectCtrl* GmkCamRectCtrl::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkCamRectCtrl(buildInfo);
}

Gimmick* GmkCamRectCtrl::SetCameraZoom(GimmickBuildInfo* buildInfo) {
    CamMng::Instance()->fn_800544B4(buildInfo, buildInfo->GetFloatParam(ParameterID::FIRST));
    return nullptr;
}

GmkCamRectCtrl::GmkCamRectCtrl(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, "GmkCamRectCtrl")
{
    CamMng::Instance()->fn_80056974();
}

GmkCamRectCtrl::~GmkCamRectCtrl() { }
