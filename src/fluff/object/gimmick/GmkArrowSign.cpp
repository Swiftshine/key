#include "object/gimmick/GmkArrowSign.h"
#include "stage/StageResources.h"

const char arrowsign_template[] = "arrowsign_%02d";
const char arrow_01[] = "arrow_01";
const char arrow_02[] = "arrow_02";
const char GimmickName[] = "GmkArrowSign";

void GmkArrowSign::AddResourceName(GimmickBuildInfo* buildInfo) {
    std::string resourceName = GetResourceName(buildInfo);
    StageResources::Instance()->AddResourceName(resourceName.c_str());
}

GmkArrowSign* GmkArrowSign::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkArrowSign(buildInfo, GimmickName);
}

GmkArrowSign::GmkArrowSign(GimmickBuildInfo* buildInfo, const char* taskName)
    : Gimmick(buildInfo, taskName)
{
    // not decompiled
}

// https://decomp.me/scratch/FAOOK
GmkArrowSign::~GmkArrowSign() {

}

void GmkArrowSign::Update() {
    return;
}


const char* GmkArrowSign::GetOrientationAnimationName() {
    float angle = static_cast<float>(mBuildInfoPtr->GetIntParam(Parameter::Angle));

    while (angle < 0.0f) {
        angle += 360.0f;
    }

    while (angle >= 360.0f) {
        angle -= 360.0f;
    }

    if (angle >= 45.0f && angle <= 225.0f) {
        return arrow_02;
    }

    return arrow_01;
}


// https://decomp.me/scratch/RjVt9
std::string GmkArrowSign::GetResourceName(GimmickBuildInfo* buildInfo) {
    char buf[0x80];
    std::string result;

    int texID = buildInfo->GetIntParam(Parameter::Texture);
    snprintf(buf, 0x80, arrowsign_template, buildInfo->GetIntParam(Parameter::Texture) + 1);

    result = buf;

    return result;
}
