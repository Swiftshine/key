#include "object/gimmick/GmkAllGetSwitch.h"

GmkAllGetSwitch* GmkAllGetSwitch::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::eHeapID_Work) GmkAllGetSwitch(buildInfo);
}

// https://decomp.me/scratch/ae6x5
GmkAllGetSwitch::GmkAllGetSwitch(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, "GmkAllGetSwitch")
    , m_130(nw4r::math::VEC2(0.0f, 0.0f))
    , mState(GmkAllGetSwitch::eState_Deactivated)
{
    GimmickBuildInfo* bInfo = mBuildInfoPtr;
    FlfMsgMng::SplitIdentifiers(bInfo->GetStringParam(Gimmick::eParameterID_Param0).c_str(), mTags);
    FlfMsgMng::SplitIdentifiers(bInfo->GetStringParam(Gimmick::eParameterID_Param1).c_str(), mTags);
    SetCullThreshold(30.0f);
}

GmkAllGetSwitch::~GmkAllGetSwitch() { }

void GmkAllGetSwitch::Update() {
    // not decompiled
}
