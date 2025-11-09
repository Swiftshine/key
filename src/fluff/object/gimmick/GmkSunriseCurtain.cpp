#include "object/gimmick/GmkSunriseCurtain.h"
#include "object/gimmick/GmkTurtle.h"

GmkSunriseCurtain* GmkSunriseCurtain::Build(GimmickBuildInfo* buildInfo) {
    return new (gfl::HeapID::Work) GmkSunriseCurtain(buildInfo);
}

// unmatched
GmkSunriseCurtain::GmkSunriseCurtain(GimmickBuildInfo* buildInfo)
    : Gimmick(buildInfo, "GmkSunriseCurtain")
{ }

GmkSunriseCurtain::~GmkSunriseCurtain() {

}

void GmkSunriseCurtain::SetBGSTEntriesBasedOnMission() {
    if (GameManager::IsInMission()) {
        SetBGSTEntries(TimeType::Day);
    } else {
        SetBGSTEntries(TimeType::Night);
    }
}

void GmkSunriseCurtain::SwitchStates() {
    mFlfMdl1->ResetNURBSAnimation(1, true);
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

void GmkSunriseCurtain::SetBGSTEntries(bool day) {
    LevelManager* mgr = Stage::Instance()->GetLevelManager();

    if (day) {
        mgr->SetBGSTEntryEnabled(mNightMainBGSTIndex, false);
        mgr->SetBGSTEntryEnabled(mNightShadowBGSTIndex, false);
        mgr->SetBGSTEntryEnabled(mDayMainBGSTIndex, true);
        mgr->SetBGSTEntryEnabled(mDayShadowBGSTIndex, true);
    } else {
        mgr->SetBGSTEntryEnabled(mNightMainBGSTIndex, true);
        mgr->SetBGSTEntryEnabled(mNightShadowBGSTIndex, true);
        mgr->SetBGSTEntryEnabled(mDayMainBGSTIndex, false);
        mgr->SetBGSTEntryEnabled(mDayShadowBGSTIndex, false);
    }
}
