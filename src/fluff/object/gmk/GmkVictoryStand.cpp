#include "object/gmk/GmkVictoryStand.h"
#include "object/gmk/GmkDecolativeBall.h"
#include "gfl/gflVec3.h"

extern "C" {
    nw4r::math::VEC3 lbl_808FDCC0;
}

void GmkVictoryStand::AddDecorativeBallResources() {
    StageResources::Instance()->AddResourceName("decorativeBall_101");
    StageResources::Instance()->AddResourceName("decorativeBall_102");
    StageResources::Instance()->AddResourceName("decorativeBall_103");
}

GmkVictoryStand* GmkVictoryStand::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkVictoryStand(buildInfo, "GmkVictoryStand");
}

void GmkVictoryStand::SpawnDecorativeBall(uint rank) {
    if (rank - 1 > 2) {
        return;
    }

    nw4r::math::VEC2 vec2;
    fn_804F1BDC(vec2, rank);
    gfl::Vec3 vec3 = vec2;
    GmkVictoryStand* stand = Instance();
    vec3.y += 5.0f;
    Instance()->mDecorativeBallBuildInfo.mGimmickID = GimmickIDs::DecorativeBall;
    stand->mDecorativeBallBuildInfo.mPosition.x = vec3.x;
    stand->mDecorativeBallBuildInfo.mPosition.y = vec3.y;
    stand->mDecorativeBallBuildInfo.mPosition.z = vec3.z;
    stand->mDecorativeBallBuildInfo.mFullSortSceneIndex = stand->mBuildInfoPtr->mFullSortSceneIndex;
    stand->mDecorativeBallBuildInfo.m_2C = stand->mBuildInfoPtr->m_2C;

    int num;
    switch (rank) {
        case 1:
            num = 101;
            break;
        case 2:
            num = 102;
            break;
        case 3:
            num = 103;
            break;
    }

    stand->mDecorativeBallBuildInfo.mIntParams[0] = num;
    stand->mDecorativeBallBuildInfo.mIntParams[1] = 1;

    GmkDecorativeBall::Build(&stand->mDecorativeBallBuildInfo);
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
    , mDecorativeBallBuildInfo()
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
