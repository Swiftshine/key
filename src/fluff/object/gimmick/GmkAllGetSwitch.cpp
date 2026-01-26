#include "object/gimmick/GmkAllGetSwitch.h"

GmkAllGetSwitch* GmkAllGetSwitch::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkAllGetSwitch(buildInfo);
}

// https://decomp.me/scratch/ae6x5
GmkAllGetSwitch::GmkAllGetSwitch(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, "GmkAllGetSwitch")
    , m_130(nw4r::math::VEC2(0.0f, 0.0f))
    , mState(State::NotActivated)
{
    GimmickBuildInfo* bInfo = mBuildInfoPtr;
    FlfMsgMng::SplitCommonTags(bInfo->GetStringParam(ParameterID::FIRST).c_str(), mTags);
    FlfMsgMng::SplitCommonTags(bInfo->GetStringParam(ParameterID::SECOND).c_str(), mTags);
    SetCullThreshold(30.0f);
}

GmkAllGetSwitch::~GmkAllGetSwitch() { }

void GmkAllGetSwitch::Update() {
    // not decompiled
}
