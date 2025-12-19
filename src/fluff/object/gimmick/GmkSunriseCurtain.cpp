#include "object/gimmick/GmkSunriseCurtain.h"
#include "object/gimmick/GmkTurtle.h"
#include "gfl/gflMtx34.h"

GmkSunriseCurtain* GmkSunriseCurtain::Build(GimmickBuildInfo* pBuildInfo) {
    return new (gfl::HeapID::Work) GmkSunriseCurtain(pBuildInfo);
}

// https://decomp.me/scratch/551V7
GmkSunriseCurtain::GmkSunriseCurtain(GimmickBuildInfo* pBuildInfo)
    : Gimmick(pBuildInfo, "GmkSunriseCurtain")
    , mState(State::State_0)
    , m_134(0)
    , m_148(false)
    , mTintR(0xFF)
    , mTintG(0xFF)
    , mTintB(0xFF)
    , mTintA(0xFF)
    , mMainSoundHandle(nullptr, nullptr)
    , mSplashBeachSoundHandle(nullptr, nullptr)
    , mSD3DActorWrapper()
    , mGateHandle()
    , mFlfMdlDraw1(nullptr)
    , mFlfMdlDraw2(nullptr)
    , mFbAlpha(nullptr)
{    
    FullSortScene* scene = Stage::Instance()->GetFullSortSceneByID(pBuildInfo->mFullSortSceneIndex);
    mFlfMdlDraw1.Create(new (gfl::HeapID::Work) FlfMdlDraw(scene, "gimmick/SunriseCurtain_01", nullptr, false));

    int indices[] = {0, 1, 2};
    mFlfMdlDraw1->LoadNURBSFromFileList(indices, ARRAY_LENGTH(indices));

    mPosition.z = FullSortSceneUtil::GetZOrder(pBuildInfo->mFullSortSceneIndex, pBuildInfo->m_2C);
    UpdateMatrix();
    mFlfMdlDraw1->SetWoolDrawMatrix(mMatrix);

    scene = Stage::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Near_05);
    mFlfMdlDraw2.Create(new (gfl::HeapID::Work) FlfMdlDraw(scene, "gimmick/SunriseCurtain_01", nullptr, false));

    int index = 3;
    mFlfMdlDraw2->LoadNURBSFromFileList(&index, 1);

    gfl::Mtx34 mtx1;
    float z = FullSortSceneUtil::GetZOrder(FullSortSceneUtil::SceneID::Far_05, 4);
    PSMTXIdentity(mtx1);
    
    gfl::Vec3 tmp1 = mPosition;
    tmp1.z = z;
    mtx1.SetTranslation(tmp1);

    mFlfMdlDraw2->SetWoolDrawMatrix(mtx1);
    mFlfMdlDraw2->SetVisibility(false);

    mNightMainBGSTLayer = pBuildInfo->GetIntParam(Parameter::NightMainBGSTLayer) + 6;
    mNightShadowBGSTLayer = pBuildInfo->GetIntParam(Parameter::NightShadowBGSTLayer) + 6;
    mDayMainBGSTLayer = pBuildInfo->GetIntParam(Parameter::DayMainBGSTLayer) + 6;
    mDayShadowBGSTLayer = pBuildInfo->GetIntParam(Parameter::DayShadowBGSTLayer) + 6;
    
    mFbAlpha.Create(::new (gfl::HeapID::Work) FbAlpha);

    scene = Stage::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Near_05);
    scene->AddRenderObj(static_cast<gfl::RenderObj*>(mFbAlpha));

    gfl::Mtx34 mtx2;
    PSMTXIdentity(mtx2);
    
    gfl::Vec3 tmp2(0.0f);
    tmp2.z = FullSortSceneUtil::GetZOrder(FullSortSceneUtil::SceneID::Far_05, 7);
    mtx2.SetTranslation(tmp2);
    

    mFbAlpha->SetLocalMtx_thunk(&mtx2);
    mFbAlpha->SetUpdateRate(0.0f);

    mScreenTintColor.r = 0x0;
    mScreenTintColor.g = 0x35;
    mScreenTintColor.b = 0x67;
    mScreenTintColor.a = 0x50;

    mFbAlpha->SetColor(mScreenTintColor);

    m_134 = 4;
    m_6E = false;

    StageInfo stageInfo = Stage::Instance()->mStageInfo;

    if (stageInfo.GetStageID() == StageIDs::SplashBeach) {
        mSplashBeachSoundHandle = mSD3DActorWrapper.GetSoundHandle(0x18B, 0, 0);
    }
}

GmkSunriseCurtain::~GmkSunriseCurtain() { }

void GmkSunriseCurtain::SetBGSTLayersBasedOnMission() {
    if (GameManager::IsInMission()) {
        SetBGSTLayers(TimeType::Day);
    } else {
        SetBGSTLayers(TimeType::Night);
    }
}

void GmkSunriseCurtain::SwitchStates() {
    mFlfMdlDraw1->ResetNURBSAnimation(1, true);
    Game::Sound::PlaySoundEffect(0xB4, 0);
    mState = State::State_2;
}

// unmatched
void GmkSunriseCurtain::Update() { }

// unmatched
void GmkSunriseCurtain::OnTimeSwitch() { }

const char State_ON[] = "ON";

void GmkSunriseCurtain::SetState(FlfGameObj* setter, std::string& stateStr) {
    if (State_ON == stateStr && State::State_1 == mState) {
        SwitchStates();
    }
}

// unmatched
void GmkSunriseCurtain::fn_803CA82C() { }

void GmkSunriseCurtain::SetBGSTLayers(bool day) {
    LevelManager* mgr = Stage::Instance()->GetLevelManager();

    if (day) {
        mgr->SetBGSTLayerEnabled(mNightMainBGSTLayer, false);
        mgr->SetBGSTLayerEnabled(mNightShadowBGSTLayer, false);
        mgr->SetBGSTLayerEnabled(mDayMainBGSTLayer, true);
        mgr->SetBGSTLayerEnabled(mDayShadowBGSTLayer, true);
    } else {
        mgr->SetBGSTLayerEnabled(mNightMainBGSTLayer, true);
        mgr->SetBGSTLayerEnabled(mNightShadowBGSTLayer, true);
        mgr->SetBGSTLayerEnabled(mDayMainBGSTLayer, false);
        mgr->SetBGSTLayerEnabled(mDayShadowBGSTLayer, false);
    }
}
