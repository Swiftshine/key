#include "manager/GmkMng.h"
#include "manager/StageManager.h"
#include "manager/GameManager.h"
#include "object/Gimmick.h"
#include "mapdata/Mapdata.h"
#include "util/GimmickUtil.h"
#include "util/GimmickResource.h"
#include "util/FullSortSceneUtil.h"


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

inline void GmkMng::CreateGimmickConditionally(const nw4r::math::VEC2& pos, Gimmick::GimmickBuildInfo* buildInfo) {
    if (Mapdata::MapdataCommonGimmick::fn_8004f604(buildInfo)) {
        if (GimmickUtil::CheckCommonByGimmickID(buildInfo->GetGimmickID()) && buildInfo->mGimmickInfo != nullptr) {
            buildInfo->mGimmickInfo->mIsCommon = true;
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


// https://decomp.me/scratch/KVSCV - regswaps
void GmkMng::CreateGimmicksFromMapdata(Mapdata* mapdata) {
    // this will not work if you put the declaration and assignment in the same line
    nw4r::math::VEC2 pos;
    pos = CameraManager::Instance()->GetCurrentPosition();

    for (uint i = 0; i < mapdata->GetNumCommonGimmicks(); i++) {
        Gimmick::GimmickBuildInfo* buildInfo = mapdata->GetCommonGimmickBuildInfo(i);
        CreateGimmickConditionally(pos, buildInfo);
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
    mod.SetNode1(mGimmicks.GetNode());
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
    mod.SetNode1(mGimmickResources.GetNode());
    mod.AddToListAfterNode1(mGimmickResources);
}

void GmkMng::CreateGimmick(Gimmick::GimmickBuildInfo* buildInfo) {
    GimmickBuildFunction func = GimmickUtil::GetBuildFunctionByGimmickID(buildInfo->GetGimmickID());

    if (func != nullptr) {
        func(buildInfo);
    }
}

// https://decomp.me/scratch/tulOa - regswap
void GmkMng::CreateGimmicksFromMapdata() {
    switch (mState) {
        case State::CreateCommonGimmicks: {
            nw4r::math::VEC2 pos;
            pos = CameraManager::Instance()->GetCurrentPosition();

            uint a = mNumCommonGimmicks;
            uint b = mMapdata->GetNumCommonGimmicks();

            uint limit;
            limit = a + 30;
            if (a + 30 > b) {
                limit = b;
            }
            
            
            for (; a < limit; a++) {
                Gimmick::GimmickBuildInfo* buildInfo = mMapdata->GetCommonGimmickBuildInfo(a);
                CreateGimmickConditionally(pos, buildInfo);
            }

            if (limit >= mMapdata->GetNumCommonGimmicks()) {
                mState = 2;
            } else {
                mNumCommonGimmicks = limit;
            }

            GameManager::fn_8000F7CC(1);
            break;
        }

        case 2: {
            mState = State::ConstructMapdataObjects;
            break;
        }

        case State::ConstructMapdataObjects: {
            mMapdata->ConstructObjects();
            GameManager::fn_8000F7CC(1);
            mState = 4;
            break;
        }

        case 4: {
            mState = State::ManageGimmickCulling;
            break;
        }

        case State::ManageGimmickCulling: {
            ManageOnScreenGimmicks();
            break;
        }
    }
}

// https://decomp.me/scratch/5kVxc
void GmkMng::ManageOnScreenGimmicks() {
    if (StageManager::Instance() != nullptr && !StageManager::Instance()->fn_80044C6C()) {
        Mapdata* mapdata = StageManager::Instance()->GetCurrentLevelSection();

        nw4r::math::VEC2 pos;
        pos = CameraManager::Instance()->GetCurrentPosition();
        
        CameraManager* camMgr = CameraManager::Instance();

        for (uint i = 0; i < mapdata->GetNumCommonGimmicks(); i++) {
            Gimmick::GimmickBuildInfo* buildInfo = mapdata->GetCommonGimmickBuildInfo(i);
            Gimmick::GimmickInfo* gimmickInfo = buildInfo->mGimmickInfo;

            if (GimmickUtil::CheckCommonByGimmickID(buildInfo->GetGimmickID())) {
                Gimmick* gimmick = gimmickInfo->mGimmick;
                if (gimmick != nullptr || gimmickInfo->mIsCommon) {
                    // either there are multiple redundancies
                    // or this is the result of some inlining

                    if (gimmick != nullptr && IsGimmickOnScreen(pos, gimmick)) {
                        gimmick = gimmickInfo->mGimmick;

                        if (gimmick != nullptr) {
                            delete gimmick;
                        }

                        gimmickInfo->mIsDeleted = true;
                        break;
                    }
                } else {
                    if (IsGimmickInSpawnRadius(pos, buildInfo)) {
                        CreateGimmick(buildInfo);
                        break;
                    }
                }
            }
        }


        for (
            gfl::LinkedList<Gimmick*>::NodeBase* node = mGimmicks.GetNode()->GetNext();
            node != mGimmicks.GetNode();
            node = node->GetNext()
        ) {
            Gimmick* gimmick = node->ToNode()->GetData();
            gimmick->SetCulled(gimmick->ShouldCull(camMgr));
        }


        gfl::LinkedList<GimmickResource*>::NodeBase* node = mGimmickResources.GetNode()->GetNext();

        while (node != mGimmickResources.GetNode()) {
            GimmickResource* resource = node->ToNode()->GetData();

            if (resource->GetNumGimmickHandles() == 0) {
                gfl::LinkedList<GimmickResource*>::Modifier mod;
                mod.SetNode2(node);
                mod.RemoveNode2FromList(mGimmickResources);
                node = mod.GetNode1();
                delete resource;
            } else {
                resource->Clear();
                node = node->GetNext();
            }
        }

    }
}


void GmkMng::AddEffect(Gimmick::GimmickBuildInfo* buildInfo) {
    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(buildInfo->mFullSortSceneIndex);

    const char* effectName = buildInfo->GetStringParam(0).c_str();

    EffectObj* effect = scene->CreateEffectObject(effectName, 0, 0);
    nw4r::math::VEC3 pos;
    pos.x = buildInfo->mPosition.x;
    pos.y = buildInfo->mPosition.y;
    pos.z = buildInfo->mPosition.z;
    pos.z = FullSortSceneUtil::GetZOrder(buildInfo->mFullSortSceneIndex, buildInfo->m_2C);
    effect->SetPosition(pos);

    nw4r::math::VEC3 unk(0.0f, 0.0f, 0.0f);
    unk.z = (buildInfo->GetFloatParam(0) / 180.0f);
    unk.z *= 3.1415927f;
    effect->fn_800a8268(unk);

    gfl::LinkedList<FlfHandle>::Modifier mod;

    if (effect != nullptr) {
        mod.GetData().SetObject(effect->GetHandleObject());
        mod.GetData().SetID(effect->GetHandleID());
    } else {
        mod.GetData().SetObject(nullptr);
        mod.GetData().SetID(0);
    }

    mod.SetNode2(mEffects.GetNode());
    mod.AddToListAfterNode2(mEffects);
}

// included in this TU is a thunk dtor. it belongs to 
// a small subset of enemies. it's not clear why it's here.

// https://decomp.me/scratch/oFMdl
bool GmkMng::IsGimmickInSpawnRadius(const nw4r::math::VEC2& offs, Gimmick::GimmickBuildInfo* buildInfo) {
    nw4r::math::VEC2 pos = buildInfo->mPosition;
    pos.x -= offs.x;
    pos.y -= offs.y;
    return (pos.x * pos.x) + (pos.y * pos.y) < 1393.7777f;
}

// https://decomp.me/scratch/flFmV
bool GmkMng::IsGimmickOnScreen(const nw4r::math::VEC2& offs, Gimmick* gimmick) {
    nw4r::math::VEC3 pos;
    pos = gimmick->GetScreenPosition();
    const float x = pos.x - offs.x;
    const float y = pos.y - offs.y;

    return 5575.1108f < (x * x) + (y * y);
}

void GmkMng::fn_80051B3C() {
    gfl::LinkedList<Gimmick*>::NodeBase* node = mGimmicks.GetNode()->GetNext();
    gfl::LinkedList<Gimmick*>::NodeBase* end = mGimmicks.GetNode();

    while (node != end) {
        node->ToNode()->GetData()->vf68();
        node = node->GetNext();
    }
}
