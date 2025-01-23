#include "manager/GmkMng.h"
#include "object/Gimmick.h"
#include "mapdata/Mapdata.h"
#include "util/GimmickUtil.h"

GmkMng::GmkMng()
    : mState(State::None)
    , mMapdata(nullptr)
    , mTask(nullptr)
{
    sInstance = this;
    // incomplete
}

GmkMng::~GmkMng() {
    // not decompiled
}

// https://decomp.me/scratch/dIugv - regswap
void GmkMng::SetupGimmicks(Mapdata* mapdata) {
    nw4r::math::VEC2 pos;
    pos = CameraManager::Instance()->GetCurrentPosition();

    for (uint i = 0; i < mapdata->GetNumCommonGimmicks(); i++) {
        Gimmick::GimmickBuildInfo* buildInfo = mapdata->GetCommonGimmickBuildInfo(i);

        if (Mapdata::MapdataCommonGimmick::fn_8004f604(buildInfo)) {
            if (GimmickUtil::CheckCommonByGimmickID(buildInfo->GetGimmickID()) && buildInfo->mExtension != nullptr) {
                buildInfo->mExtension->first = true;
            }
        } else {
            if (GimmickUtil::CheckCommonByGimmickID(buildInfo->GetGimmickID())) {
                if (IsGimmickInSpawnRadius(pos, buildInfo)) {
                    CreateGimmick(buildInfo);
                }
            } else {
                CreateGimmick(buildInfo);
            }
        }
    }
    
    mapdata->ConstructObjects();
    mMapdata = mapdata;
    fn_80051B3C();
}

void GmkMng::SetMapdata(Mapdata* mapdata) {
    mMapdata = mapdata;
    mNumCommonGimmicks = 0;
    mState = State::CreateCommonGimmicks;
}

void GmkMng::AddGimmick(Gimmick* gimmick) {
    // not matched due to gfl::LinkedList
    mGimmicks.Insert(gimmick);
}

void GmkMng::RemoveGimmick(Gimmick* gimmick) {
    // not matched due to gfl::LinkedList
    mGimmicks.Remove(gimmick);
}

void GmkMng::ClearAll(bool arg1) {
    // not decompiled
}

void GmkMng::GetGimmicksByGimmickID(int gimmickID, std::vector<Gimmick*>& dst) {
    for (gfl::LinkedList<Gimmick*>::NodeBase* node = mGimmicks.GetNode(); node != mGimmicks.GetNode(); node = node->GetNext()) {
        Gimmick* gimmick = node->ToNode()->GetData();
        int id = gimmick->GetGimmickID();

        // nonmatching due to vector
        if (gimmickID == id) {
            dst.push_back(gimmick);
        }
    }
}