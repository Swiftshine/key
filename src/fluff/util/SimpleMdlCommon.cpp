#include "util/SimpleMdlCommon.h"
#include "gfl/gflMemoryUtil.h"
#include <rand.h>

const char NurbsPrefix[] = "N_";

Gimmick* SimpleMdlCommon::Build(Gimmick::GimmickBuildInfo* buildInfo) {
    std::string prefix(buildInfo->GetStringParam(Parameter::Name), 0, 2);

    bool cmp = prefix.compare(NurbsPrefix) == 0;
    if (cmp) {
        return new (gfl::HeapID::Work) GmkSimpleNurbs(buildInfo);
    } else if (buildInfo->GetIntParam(Parameter::UnkInt1) < 10) {
        return new (gfl::HeapID::Work) GmkSimpleMdl(buildInfo);
    }
    
    return new (gfl::HeapID::Work) GmkColAnimMdl(buildInfo);
}

extern "C" void fn_800D5960(Gimmick::GimmickBuildInfo*);
extern "C" void fn_80052060(void*, const char*);
extern "C" void* lbl_808E4DC8;
void SimpleMdlCommon::fn_80052C8C(Gimmick::GimmickBuildInfo* buildInfo) {
    void* list = lbl_808E4DC8;

    std::string prefix(buildInfo->GetStringParam(Parameter::Name), 0, 2);

    bool cmp = prefix.compare(NurbsPrefix) == 0;

    if (cmp) {
        // GimmickUtil::AddToNameList(buildInfo);
        fn_800D5960(buildInfo);
        return;
    } else if (buildInfo->GetIntParam(Parameter::UnkInt1) < 10) {
        // GimmickUtil::AddToNameList(buildInfo->GetStringParam(Parameter::Name).begin());
        fn_80052060(list, buildInfo->GetStringParam(Parameter::Name).c_str());
    } else {
        fn_800D5960(buildInfo);
        return;
    }

    // GimmickUtil::AddToNameList(buildInfo)
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