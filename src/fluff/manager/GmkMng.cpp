#include "manager/GmkMng.h"
#include "object/Gimmick.h"
#include "mapdata/Mapdata.h"
#include "util/GimmickUtil.h"
#include "util/GimmickResource.h"
#include "manager/StageManager.h"

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

// https://decomp.me/scratch/73YRG - regswaps
void GmkMng::SetupGimmicks(Mapdata* mapdata) {
    // this will not work if you put the declaration and assignment in the same line
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
    gfl::LinkedList<Gimmick*>::Modifier mod;
    mod.SetAfter(mGimmicks.GetNode());
    mod.AddToListAfterNode2(mGimmicks, gimmick);
}

void GmkMng::RemoveGimmick(Gimmick* gimmick) {
    // not matched due to gfl::LinkedList
    mGimmicks.Remove(gimmick);
}

void GmkMng::ClearAll(bool arg1) {
    // not decompiled
}

// https://decomp.me/scratch/g7Bxu - regswaps
void GmkMng::GetGimmicksByGimmickID(int gimmickID, std::vector<Gimmick*>& dest) {
    gfl::LinkedList<Gimmick*>::NodeBase* node = mGimmicks.GetNode()->GetNext();
    gfl::LinkedList<Gimmick*>::NodeBase* end = mGimmicks.GetNode();
    
    while (node != end) {
        Gimmick* gimmick = node->ToNode()->GetData();
        int id = gimmick->GetGimmickID();

        if (gimmickID == id) {
            dest.push_back(gimmick);
        }
        
        node = node->GetNext();
    }
}

void GmkMng::GetCommonGimmicksByID(int gimmickID, std::vector<Gimmick::GimmickBuildInfo*>& dest) {
    Mapdata* mapdata = StageManager::Instance()->GetCurrentLevelSection();

    for (uint i = 0; i < mapdata->GetNumCommonGimmicks(); i++) {
        Gimmick::GimmickBuildInfo* buildInfo = mapdata->GetCommonGimmickBuildInfo(i);
        int id = buildInfo->GetGimmickID();
        if (id == gimmickID) {
            dest.push_back(buildInfo);
        }
    }
}

Gimmick* GmkMng::GetGimmickByCommonTag(const std::string& tag) {
    gfl::LinkedList<Gimmick*>::NodeBase* node = mGimmicks.GetNode()->GetNext();
    gfl::LinkedList<Gimmick*>::NodeBase* end = mGimmicks.GetNode();
    Gimmick* result = nullptr;

    while (node != end) {
        Gimmick* gimmick = node->ToNode()->GetData();

        if (gimmick->GetGimmickBuildInfoPtr() != nullptr &&
            tag.compare(gimmick->GetGimmickBuildInfoPtr()->GetCommonTag()) == 0
        ) {
            result = gimmick;
            break;
        } 

        node = node->GetNext();
    }

    return result;
}

// https://decomp.me/scratch/VH6w7 - regswaps
Gimmick::GimmickBuildInfo* GmkMng::GetCommonGimmickBuildInfoByCommonTag(const char* tag) {
    Mapdata* mapdata = StageManager::Instance()->GetCurrentLevelSection();

    uint i = 0;
    const uint count = mapdata->GetNumCommonGimmicks();
    
    while (i < count) {
        Gimmick::GimmickBuildInfo* buildInfo = mapdata->GetCommonGimmickBuildInfo(i);
        if (strcmp(buildInfo->GetCommonTag(), tag) == 0) {
            return buildInfo;
        }
        i++;
    }
    
    return nullptr;
}

void GmkMng::RegisterResources(const char* gimmickName, Gimmick* gimmick) {
    gfl::LinkedList<GimmickResource*>::NodeBase* node = mGimmickResources.GetNode()->GetNext();
    gfl::LinkedList<GimmickResource*>::NodeBase* end = mGimmickResources.GetNode();

    while (node != end) {
        GimmickResource* resource = node->ToNode()->GetData();
        const char* resourceName = resource->GetResourceName().c_str();

        if (strcmp(gimmickName, resourceName) == 0) {
            resource->RegisterGimmick(gimmick);
            return;
        }

        node = node->GetNext();
    }

    gfl::LinkedList<GimmickResource*>::Modifier mod;
    mod.SetData(new (gfl::HeapID::Work) GimmickResource(gimmickName));
    mod.GetData()->RegisterGimmick(gimmick);
    mod.SetAfter(mGimmickResources.GetNode());
    mod.AddToListAfterNode1(mGimmickResources);
}
