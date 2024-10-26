#include "object/gmk/GmkVictoryStand.h"

extern "C" {
    nw4r::math::VEC3 lbl_808FDCC0;
}

void GmkVictoryStand::AddDecolativeBallResources() {
    StageResources::Instance()->AddResourceName("decorativeBall_101");
    StageResources::Instance()->AddResourceName("decorativeBall_102");
    StageResources::Instance()->AddResourceName("decorativeBall_103");
}

GmkVictoryStand* GmkVictoryStand::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkVictoryStand(buildInfo, "GmkVictoryStand");
}

// unfinished
GmkVictoryStand::GmkVictoryStand(GimmickBuildInfo* buildInfo, const char* taskName)
    : Gimmick(buildInfo, taskName)
    , mPreviousState(mCurrentState)
    , mCurrentState(0)
    , mBeadAwardState(0)
    , m_13C(0)
    , m_140(0)
    , mPlayerRanking(0)
    , mBeadAwardPosition(lbl_808FDCC0)
    , mTotalAwardedBeads(0)
    , mResources(nullptr)
    , mColObj(nullptr)
    , mDecolativeBallBuildInfo()
{
    sInstance = this;
}

GmkVictoryStand::~GmkVictoryStand() {
    sInstance = nullptr;
}

void GmkVictoryStand::Update() {
    if (1 == mCurrentState) {
        AwardBeads();
    }
}

void GmkVictoryStand::AwardBeads() {
    
}
