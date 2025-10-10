#include "util/SimpleMdlCommon.h"
#include "gfl/gflMemoryUtil.h"
#include "util/GimmickUtil.h"
#include "stage/StageResources.h"
#include <rand.h>

const char NurbsPrefix[] = "N_";

Gimmick* SimpleMdlCommon::Build(Gimmick::GimmickBuildInfo* pBuildInfo) {
    std::string prefix(pBuildInfo->GetStringParam(Parameter::Name), 0, 2);

    bool cmp = prefix.compare(NurbsPrefix) == 0;
    if (cmp) {
        return new (gfl::HeapID::Work) GmkSimpleNurbs(pBuildInfo);
    } else if (pBuildInfo->GetIntParam(Parameter::UnkInt1) < 10) {
        return new (gfl::HeapID::Work) GmkSimpleMdl(pBuildInfo);
    }
    
    return new (gfl::HeapID::Work) GmkColAnimMdl(pBuildInfo);
}

void SimpleMdlCommon::AddGimmickName(Gimmick::GimmickBuildInfo* pBuildInfo) {
    StageResources* resources = StageResources::Instance();
    
    std::string prefix(pBuildInfo->GetStringParam(Parameter::Name), 0, 2);

    if (NurbsPrefix == prefix) {
        GimmickUtil::AddGimmickName(pBuildInfo);
        return;
    } else if (pBuildInfo->GetIntParam(Parameter::UnkInt1) < 10) {
        resources->AddGimmickName(pBuildInfo->GetStringParam(Parameter::Name).c_str());
    } else {
        GimmickUtil::AddGimmickName(pBuildInfo);
        return;
    }
}

float SimpleMdlCommon::GetInitialAnimFrame(int frameIndex) {
    // simple model gimmicks set an initial frame index.
    // this is usually set to zero, but it can be set to
    // an actual frame index (index > 0) or something random (index < 0).

    float frame;

    if (frameIndex >= 0) {
        frame = static_cast<float>(frameIndex);
    } else {
        return static_cast<float>(rand() % -frameIndex);
    }

    return frame;
}
