#include "gfl/gflMtx34.h"

#include "object/GimmickList.h"
#include "object/gimmick/GmkGate3.h"
#include "object/gimmick/GmkSunriseCurtain.h"
#include "object/gimmick/GmkTurtle.h"
#include "object/gimmick/GmkUpdownWater.h"

GmkSunriseCurtain* GmkSunriseCurtain::Build(GimmickBuildInfo* pBuildInfo) {
    return new (gfl::HeapID::Work) GmkSunriseCurtain(pBuildInfo);
}

// rodata
const int lbl_8080AA20 = 0; // 0
const int lbl_8080AA24 = 1; // 1
const int lbl_8080AA28 = 2; // 2

// sdata2
int lbl_808EA238; // 3

// https://decomp.me/scratch/8CZ4w
GmkSunriseCurtain::GmkSunriseCurtain(GimmickBuildInfo* pBuildInfo)
    : Gimmick(pBuildInfo, "GmkSunriseCurtain")
    , mState(State::Start)
    , mStateFrames(0)
    , mTimeChanged(false)
    , mScreenTintColor()
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

    int indices[] = {
        lbl_8080AA20,
        lbl_8080AA24,
        lbl_8080AA28
    };
    
    mFlfMdlDraw1->LoadNURBSFromFileList(indices, ARRAY_LENGTH(indices));

    mPosition.z = FullSortSceneUtil::GetZOrder(pBuildInfo->mFullSortSceneIndex, pBuildInfo->m_2C);
    UpdateMatrix();
    mFlfMdlDraw1->SetWoolDrawMatrix(mMatrix);

    scene = Stage::Instance()->GetFullSortSceneByID(FullSortSceneUtil::SceneID::Near_05);
    mFlfMdlDraw2.Create(new (gfl::HeapID::Work) FlfMdlDraw(scene, "gimmick/SunriseCurtain_01", nullptr, false));

    int index = lbl_808EA238;
    mFlfMdlDraw2->LoadNURBSFromFileList(&index, 1);

    gfl::Mtx34 mtx1;
    float z = FullSortSceneUtil::GetZOrder(FullSortSceneUtil::SceneID::Far_05, 4);
    PSMTXIdentity(mtx1);
    
    gfl::Vec3 tmp1 = mPosition;
    tmp1.z = z;
    mtx1.SetTranslation(tmp1);

    mFlfMdlDraw2->SetWoolDrawMatrix(mtx1);
    mFlfMdlDraw2->SetVisibility(false);

    mNightBackgroundBGSTLayer = pBuildInfo->GetIntParam(Parameter::NightBackgroundBGSTLayer) + 6;
    mNightForegroundBGSTLayer = pBuildInfo->GetIntParam(Parameter::NightForegroundBGSTLayer) + 6;
    mDayBackgroundBGSTLayer = pBuildInfo->GetIntParam(Parameter::DayBackgroundBGSTLayer) + 6;
    mDayForegroundBGSTLayer = pBuildInfo->GetIntParam(Parameter::DayForegroundBGSTLayer) + 6;
    
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

    mScreenTintColor = gfl::Color(0, 0x35, 0x67, 0x50);

    mFbAlpha->SetColor(mScreenTintColor);

    mStateFrames = 4;
    mShouldUpdateWater = false;

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

void GmkSunriseCurtain::Update() {
    switch (mState) {
        case State::Start: {
            if (mStateFrames != 0) {
                mStateFrames--;
            } else {
                std::vector<Gimmick*> gates;
                GmkMng::Instance()->GetGimmicksByGimmickID(0x42, gates);
    
                if (!gates.empty()) {
                    // only care about the first one
    
                    GmkGate3* gate = dynamic_cast<GmkGate3*>(gates.front());
    
                    if (gate != nullptr) {
                        mGateHandle.SetObject(gate->GetHandleObject());
                        mGateHandle.SetID(gate->GetHandleID());
                    } else {
                        mGateHandle = FlfHandle();
                    }
                }
    
                if (GameManager::IsInMission()) {
                    DoTimeSwitch();
                    mState = State::Day;
                } else {
                    SetStateForTaggedObjects(
                        "ON",
                        mBuildInfoPtr->GetStringParam(ParameterID::FIRST).c_str()
                    );
                    SetStateForTaggedObjects(
                        "OFF",
                        mBuildInfoPtr->GetStringParam(ParameterID::SECOND).c_str()
                    );
                    mState = State::State_1;
                }
            }

            break;
        }

        case State::State_2: {
            if (mFlfMdlDraw1->GetCurrentFrame() == 37.0f) {
                Game::Sound::PlaySoundEffect(mPosition, 0xF5, 0, 0);
            }

            if (mFlfMdlDraw1->GetCurrentFrame() == 125.0f) {
                mMainSoundHandle = Game::Sound::PlaySoundEffect(mPosition, 0x199, 0, 0);
            }
            
            if (mFlfMdlDraw1->GetCurrentFrame() == 220.0f) {
                if (mMainSoundHandle.HandlePositionValid()) {
                    gfl::Sound::Instance()->ManageSoundHandleInner(
                        mMainSoundHandle.GetInnerSoundHandle(),
                        0xF,
                        false
                    );
                }
            }

            if (mFlfMdlDraw1->GetCurrentFrame() == 305.0f) {
                Game::Sound::PlaySoundEffect(mPosition, 0x1EF, 0, 0);
            }

            if (mFlfMdlDraw1->IsAnimationDone()) {
                mColorChangeFrames = 0;
                mState = State::AfterNight;
            }

            break;
        }

        case State::AfterNight: {
            if (mColorChangeFrames < 30) {
                gfl::Color from = 0xFFFFFFFF;
                gfl::Color color;
        
                float frame = static_cast<float>(mColorChangeFrames);
                
                color.Interpolate(
                    frame / 30.0f,
                    1.0f - frame / 30.0f,
                    from,
                    mScreenTintColor
                );
                
                mFbAlpha->SetColor(color);
                mColorChangeFrames++;
            } else {
                DoTimeSwitch();
                mStateFrames = 20;
                mState = State::Wait;
            }

            break;
        }

        case State::Wait: {
            if (!Stage::Instance()->fn_80044C88()) {
                if (mStateFrames != 0) {
                    mStateFrames--;
                } else {
                    mColorChangeFrames = 0;
                    mState = State::BeforeDay;
                }
            }

            break;
        }

        case State::BeforeDay: {
            if (mColorChangeFrames < 60) {
                gfl::Color from = 0xFFFFFFFF;
                gfl::Color to = 0xFFFFFFFF;
                to.a = 0;
                gfl::Color color;
                
                float frame = static_cast<float>(mColorChangeFrames);
                
                color.Interpolate(
                    frame / 30.0f,
                    1.0f - frame / 30.0f,
                    to,
                    from
                );
                mFbAlpha->SetColor(color);
                mColorChangeFrames++;
            } else {
                mFbAlpha->SetUpdate(false);
                mState = State::Day;
            }

            break;
        }

        case State::Day: {
            if (mFlfMdlDraw2->fn_80023B1C() && mFlfMdlDraw2->IsAnimationDone()) {
                mFlfMdlDraw2->SetVisibility(false);
            }
            break;
        }
    }

    RemoveSoundHandle();
}

// https://decomp.me/scratch/e0weB - regswaps
const char* star07 = "star07";

void GmkSunriseCurtain::DoTimeSwitch() {
    std::vector<Gimmick*> gimmicks;
    GmkMng::Instance()->GetGimmicksByGimmickID(GimmickID::GmkTurtle, gimmicks);

    for (std::vector<Gimmick*>::iterator it = gimmicks.begin(); it != gimmicks.end(); it++) {
        GmkTurtle* turtle = dynamic_cast<GmkTurtle*>(*it);

        if (turtle != nullptr) {
            turtle->BecomeActive();
        }
    }
    
    gimmicks.clear();
    GmkMng::Instance()->GetGimmicksByGimmickID(GimmickID::GmkUpdownWater, gimmicks);

    for (std::vector<Gimmick*>::iterator it = gimmicks.begin(); it != gimmicks.end(); it++) {
        GmkUpdownWater* water = dynamic_cast<GmkUpdownWater*>(*it);

        if (water != nullptr) {
            water->fn_80212B60(0);
        }
    }

    std::vector<GimmickBuildInfo*> stars;
    GmkMng::Instance()->GetCommonGimmicksByID(GimmickID::GmkSimpleMdl, stars);

    for (std::vector<GimmickBuildInfo*>::iterator it = stars.begin(); it != stars.end(); it++) {
        GimmickBuildInfo* buildInfo = *it;

        if (
            buildInfo->GetStringParam(ParameterID::FIRST) == star07
            && buildInfo->mGimmickInfo != nullptr
        ) {
            Gimmick* gmk = buildInfo->mGimmickInfo->mGimmick;
            
            if (gmk != nullptr) {
                delete gmk;
            }

            buildInfo->mGimmickInfo->mIsDeleted1 = true;
        }
    } 

    SetStateForTaggedObjects("OFF", mBuildInfoPtr->GetStringParam(ParameterID::FIRST).c_str());
    SetStateForTaggedObjects("ON", mBuildInfoPtr->GetStringParam(ParameterID::SECOND).c_str());

    if (GameManager::IsInMission()) {
        mFbAlpha->SetUpdate(false);
    } else {
        mFbAlpha->SetColor(0xFFFFFFFF);
    }

    mFlfMdlDraw1->ResetNURBSAnimation(2, true);
    mFlfMdlDraw2->ResetNURBSAnimation(3, true);
    mFlfMdlDraw2->SetVisibility(true);

    SetBGSTLayers(true);

    if (!GameManager::IsInMission()) {
        gfl::SoundHandle::CreateSoundHandle(0x10C, 0);
        gfl::SoundHandle::CreateSoundHandle(0x11F, 0);
        gfl::Sound::fn_8000781C(0x15, 60);
    }

    mTimeChanged = true;
}

void GmkSunriseCurtain::SetState(FlfGameObj* pSetter, const std::string& rState) {
    if (rState == "ON" && State::State_1 == mState) {
        SwitchStates();
    }
}

// https://decomp.me/scratch/wiAl5
void GmkSunriseCurtain::RemoveSoundHandle() {
    StageInfo stageInfo = Stage::Instance()->mStageInfo;

    if (stageInfo.GetStageID() == StageIDs::SplashBeach) {
        gfl::Vec2 pos2 = CameraManager::Instance()->GetCurrentPosition();

        if (pos2.y > 29.0f) {
            pos2.y = 29.0f;
        }

        gfl::Vec3 pos3 = pos2;
        mSD3DActorWrapper.SetPosition((const nw4r::math::VEC2&)pos3);

        FlfHandleObj** objPtr;
        FLFHANDLEOBJ_DO_IF_VALID(mGateHandle, objPtr) {
            if (static_cast<GmkGate3*>(*objPtr)->fn_8037EFF8() == 2) {
                bool valid;
                if (mSplashBeachSoundHandle.HandlePositionValid()) {
                    valid = mSplashBeachSoundHandle.GetInnerSoundHandle()->mSoundHandle.IsAttachedSound() &&
                        mSplashBeachSoundHandle.GetInnerSoundHandle()->mEnabled;
                }

                if (valid) {
                    if (mSplashBeachSoundHandle.HandlePositionValid()) {
                        gfl::Sound::Instance()->ManageSoundHandleInner(
                            mSplashBeachSoundHandle.GetInnerSoundHandle(),
                            120,
                            false
                        );
                    }

                    mSplashBeachSoundHandle.SetPosition(nullptr);
                    mSplashBeachSoundHandle.SetInnerSoundHandle(nullptr);
                }
            }
        }
    }
}

void GmkSunriseCurtain::SetBGSTLayers(bool day) {
    LevelManager* mgr = Stage::Instance()->GetLevelManager();

    if (day) {
        mgr->SetBGSTLayerEnabled(mNightBackgroundBGSTLayer, false);
        mgr->SetBGSTLayerEnabled(mNightForegroundBGSTLayer, false);
        mgr->SetBGSTLayerEnabled(mDayBackgroundBGSTLayer, true);
        mgr->SetBGSTLayerEnabled(mDayForegroundBGSTLayer, true);
    } else {
        mgr->SetBGSTLayerEnabled(mNightBackgroundBGSTLayer, true);
        mgr->SetBGSTLayerEnabled(mNightForegroundBGSTLayer, true);
        mgr->SetBGSTLayerEnabled(mDayBackgroundBGSTLayer, false);
        mgr->SetBGSTLayerEnabled(mDayForegroundBGSTLayer, false);
    }
}
