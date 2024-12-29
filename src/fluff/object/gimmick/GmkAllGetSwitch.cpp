#include "object/gimmick/GmkAllGetSwitch.h"

GmkAllGetSwitch* GmkAllGetSwitch::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkAllGetSwitch(buildInfo);
}

GmkAllGetSwitch::GmkAllGetSwitch(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, "GmkAllGetSwitch")
{ }

GmkAllGetSwitch::~GmkAllGetSwitch() {

}

void GmkAllGetSwitch::Update() {
    
}
