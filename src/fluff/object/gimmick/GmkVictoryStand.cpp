#include "object/gimmick/GmkVictoryStand.h"
#include "object/gimmick/GmkDecolativeBall.h"
#include "util/FullSortSceneUtil.h"
#include "graphics/FullSortScene.h"
#include "manager/StageManager.h"

extern "C" {
    float lbl_808E697C;
}

void GmkVictoryStand::AddDecorativeBallResources() {
    StageResources::Instance()->AddResourceName("decorativeBall_101");
    StageResources::Instance()->AddResourceName("decorativeBall_102");
    StageResources::Instance()->AddResourceName("decorativeBall_103");
}

GmkVictoryStand* GmkVictoryStand::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkVictoryStand(buildInfo, "GmkVictoryStand");
}

void GmkVictoryStand::SetRankingInfo(uint playerRanking, nw4r::math::VEC2& position) {
    GmkVictoryStand* stand = Instance();
    Instance()->mPlayerRanking = playerRanking;
    stand->mBeadAwardPosition = position;
    stand->mPreviousState = stand->mCurrentState;
    stand->mCurrentState = 1;
    stand->mBeadAwardState = 0;
    stand->m_13C = 0;
    stand->m_140 = 0;
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

const char victoryStand[] = "victoryStand";
const char victoryStand_01[] = "victoryStand_01";
const char hitColbin[] = "gimmick/%s/hit.colbin";

GmkVictoryStand::GmkVictoryStand(GimmickBuildInfo* buildInfo, const char* taskName)
    : Gimmick(buildInfo, taskName)
    , mPreviousState(mCurrentState)
    , mCurrentState(0)
    , mBeadAwardState(0)
    , m_13C(0)
    , m_140(0)
    , mPlayerRanking(0)
    , mDecorativeBallBuildInfo()
{
    mBeadAwardPosition.x = gfl::Vec3::Zero.x;
    mBeadAwardPosition.y = gfl::Vec3::Zero.y;
    mBeadAwardPosition.z = gfl::Vec3::Zero.z;
    mTotalAwardedBeads = 0;
    mModel = nullptr;
    mColObj = nullptr;

    sInstance = this;
    GimmickBuildInfo* buildInfoPtr = mBuildInfoPtr;
    int sceneID = buildInfoPtr->mFullSortSceneIndex;

    mPosition.z = FullSortSceneUtil::GetZOrder(sceneID, buildInfoPtr->m_2C);
    UpdateMatrix();
    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(sceneID);

    gfl::ResFileInfoPointer fileInfo;
    GetResFileInfo(fileInfo, this);

    mModel.Create(gfl::HeapID::Work);
    mModel->RegisterResources(fileInfo, victoryStand, 0, scene, 0);
    mModel->SetMatrix(lbl_808E697C, mMatrix, true);
    mModel->SetUpdate(false);

    mColObj.Create(gfl::HeapID::Work);

    char colbinPath[0x200];
    snprintf(colbinPath, sizeof(colbinPath), hitColbin, victoryStand_01);
    mColObj->SetColbin(colbinPath);
    mColObj->AddToTree();
    nw4r::math::VEC2 position(mMatrix[0][3], mMatrix[1][3]);
    nw4r::math::VEC2 colbinPos = position;
    mColObj->SetPosition(colbinPos);
    mColObj->SetOwner(this);
    mColObj->SetEnabled(true);
    mColObj->GetCollisionData()->fn_800D0128(0x20000000, 0, 0x20000010);
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
    if (0 == mBeadAwardState) {
        uint playerRanking = mPlayerRanking;
        int beadWinnings;
        switch (mPlayerRanking) {
            case 1:
                beadWinnings = 300;
                break;
            case 2:
                beadWinnings = 200;
                break;
            case 3:
                beadWinnings = 100;
                break;
        }

        int beadColor = rand();
        int beadType = GmkBead::Type::Medium;

        if (beadWinnings - mTotalAwardedBeads > 9 && playerRanking % 2 == 0) {
            beadType = GmkBead::Type::Large;
        }

        nw4r::math::VEC2 beadPosition(0.0f, 0.0f);
        GmkBead* bead = BeadUtil::CreateBead(beadType, beadColor % 7, beadPosition);
        bead->fn_800B0658((float)rand());
        bead->SetPosition(*(nw4r::math::VEC3*)&beadPosition);

        // unfinished
    }
}
