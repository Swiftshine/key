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

inline void GmkMng::CreateGimmickConditionally(
    const nw4r::math::VEC2& rPos,
    Gimmick::GimmickBuildInfo* pBuildInfo
) {
    if (Mapdata::MapdataCommonGimmick::fn_8004f604(pBuildInfo)) {
        if (GimmickUtil::CheckCommonByGimmickID(pBuildInfo->GetGimmickID())
            && pBuildInfo->mGimmickInfo != nullptr) {
            pBuildInfo->mGimmickInfo->mIsCommon = true;
        }
    } else {
        if (GimmickUtil::CheckCommonByGimmickID(pBuildInfo->GetGimmickID())) {
            if (IsGimmickInSpawnRadius(rPos, pBuildInfo)) {
                CreateGimmick(pBuildInfo);
            }
        } else {
            CreateGimmick(pBuildInfo);
        }
    }
}


// https://decomp.me/scratch/KVSCV - regswaps
void GmkMng::CreateGimmicksFromMapdata(Mapdata* pMapdata) {
    // this will not work if you put the declaration and assignment in the same line
    nw4r::math::VEC2 pos;
    pos = CameraManager::Instance()->GetCurrentPosition();

    for (uint i = 0; i < pMapdata->mNumCommonGimmicks; i++) {
        Gimmick::GimmickBuildInfo* buildInfo = pMapdata->GetCommonGimmickBuildInfo(i);
        CreateGimmickConditionally(pos, buildInfo);
    }
    
    pMapdata->ConstructObjects();
    mMapdata = pMapdata;
    fn_80051B3C();
}

void GmkMng::SetMapdata(Mapdata* pMapdata) {
    mMapdata = pMapdata;
    mNumCommonGimmicks = 0;
    mState = State::CreateCommonGimmicks;
}

void GmkMng::AddGimmick(Gimmick* pGimmick) {
    gfl::LinkedList<Gimmick*>::Modifier mod;
    mod.SetNode1(mGimmicks.GetNode());
    mod.AddToListAfterNode2(mGimmicks, pGimmick);
}

void GmkMng::RemoveGimmick(Gimmick* pGimmick) {
    // not matched due to gfl::LinkedList
    mGimmicks.Remove(pGimmick);
}

void GmkMng::ClearAll(bool arg1) {
    // not decompiled
}

// https://decomp.me/scratch/g7Bxu - regswaps
void GmkMng::GetGimmicksByGimmickID(int gimmickID, std::vector<Gimmick*>& rDest) {
    gfl::LinkedList<Gimmick*>::NodeBase* node = mGimmicks.GetNode()->GetNext();
    gfl::LinkedList<Gimmick*>::NodeBase* end = mGimmicks.GetNode();
    
    while (node != end) {
        Gimmick* gimmick = node->ToNode()->GetData();
        int id = gimmick->GetGimmickID();

        if (gimmickID == id) {
            rDest.push_back(gimmick);
        }
        
        node = node->GetNext();
    }
}

void GmkMng::GetCommonGimmicksByID(int gimmickID, std::vector<Gimmick::GimmickBuildInfo*>& rDest) {
    Mapdata* mapdata = StageManager::Instance()->GetCurrentLevelSection();

    for (uint i = 0; i < mapdata->mNumCommonGimmicks; i++) {
        Gimmick::GimmickBuildInfo* buildInfo = mapdata->GetCommonGimmickBuildInfo(i);
        int id = buildInfo->GetGimmickID();
        if (id == gimmickID) {
            rDest.push_back(buildInfo);
        }
    }
}

Gimmick* GmkMng::GetGimmickByCommonTag(const std::string& rTag) {
    gfl::LinkedList<Gimmick*>::NodeBase* node = mGimmicks.GetNode()->GetNext();
    gfl::LinkedList<Gimmick*>::NodeBase* end = mGimmicks.GetNode();

    Gimmick* result = nullptr;

    GFL_LINK_LIST_WHILE_2(mGimmicks, Gimmick*, node, end, {
        Gimmick* gimmick = node->ToNode()->GetData();

        if (gimmick->GetGimmickBuildInfoPtr() != nullptr &&
            rTag.compare(gimmick->GetGimmickBuildInfoPtr()->GetCommonTag()) == 0
        ) {
            result = gimmick;
            break;
        }
    })

    return result;
}

// https://decomp.me/scratch/VH6w7 - regswaps
Gimmick::GimmickBuildInfo* GmkMng::GetCommonGimmickBuildInfoByCommonTag(const char* pTag) {
    Mapdata* mapdata = StageManager::Instance()->GetCurrentLevelSection();

    uint i = 0;
    const uint count = mapdata->mNumCommonGimmicks;
    
    while (i < count) {
        Gimmick::GimmickBuildInfo* buildInfo = mapdata->GetCommonGimmickBuildInfo(i);
        if (strcmp(buildInfo->GetCommonTag(), pTag) == 0) {
            return buildInfo;
        }
        i++;
    }
    
    return nullptr;
}

void GmkMng::RegisterResources(const char* pGimmickName, Gimmick* pGimmick) {
    
    gfl::LinkedList<GimmickResource*>::NodeBase* node;
    
    GFL_LINK_LIST_WHILE(mGimmickResources, GimmickResource*, node, {
        GimmickResource* resource = node->ToNode()->GetData();
        const char* resourceName = resource->GetResourceName().c_str();

        if (strcmp(pGimmickName, resourceName) == 0) {
            resource->RegisterGimmick(pGimmick);
            return;
        }
    })

    gfl::LinkedList<GimmickResource*>::Modifier mod;
    mod.SetData(new (gfl::HeapID::Work) GimmickResource(pGimmickName));
    mod.GetData()->RegisterGimmick(pGimmick);
    mod.SetNode1(mGimmickResources.GetNode());
    mod.AddToListAfterNode1(mGimmickResources);
}

void GmkMng::CreateGimmick(Gimmick::GimmickBuildInfo* pBuildInfo) {
    GimmickBuildFunction func = GimmickUtil::GetBuildFunctionByGimmickID(
        pBuildInfo->GetGimmickID()
    );

    if (func != nullptr) {
        func(pBuildInfo);
    }
}

// https://decomp.me/scratch/tulOa - regswap
void GmkMng::CreateGimmicksFromMapdata() {
    switch (mState) {
        case State::CreateCommonGimmicks: {
            nw4r::math::VEC2 pos;
            pos = CameraManager::Instance()->GetCurrentPosition();

            uint a = mNumCommonGimmicks;
            uint b = mMapdata->mNumCommonGimmicks;

            uint limit;
            limit = a + 30;
            if (a + 30 > b) {
                limit = b;
            }
            
            
            for (; a < limit; a++) {
                Gimmick::GimmickBuildInfo* buildInfo = mMapdata->GetCommonGimmickBuildInfo(a);
                CreateGimmickConditionally(pos, buildInfo);
            }

            if (limit >= mMapdata->mNumCommonGimmicks) {
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

        for (uint i = 0; i < mapdata->mNumCommonGimmicks; i++) {
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


void GmkMng::AddEffect(Gimmick::GimmickBuildInfo* pBuildInfo) {
    FullSortScene* scene = StageManager::Instance()->GetFullSortSceneByID(
        pBuildInfo->mFullSortSceneIndex
    );

    const char* effectName = pBuildInfo->GetStringParam(0).c_str();

    EffectObj* effect = scene->CreateEffectObject(effectName, 0, 0);
    nw4r::math::VEC3 pos;
    pos.x = pBuildInfo->mPosition.x;
    pos.y = pBuildInfo->mPosition.y;
    pos.z = pBuildInfo->mPosition.z;
    pos.z = FullSortSceneUtil::GetZOrder(pBuildInfo->mFullSortSceneIndex, pBuildInfo->m_2C);
    effect->SetPosition(pos);

    nw4r::math::VEC3 unk(0.0f, 0.0f, 0.0f);
    unk.z = (pBuildInfo->GetFloatParam(0) / 180.0f);
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
bool GmkMng::IsGimmickInSpawnRadius(
    const nw4r::math::VEC2& rOffs,
    Gimmick::GimmickBuildInfo* pBuildInfo
) {
    nw4r::math::VEC2 pos = pBuildInfo->mPosition;
    pos.x -= rOffs.x;
    pos.y -= rOffs.y;
    return (pos.x * pos.x) + (pos.y * pos.y) < 1393.7777f;
}

// https://decomp.me/scratch/flFmV
bool GmkMng::IsGimmickOnScreen(const nw4r::math::VEC2& rOffs, Gimmick* pGimmick) {
    nw4r::math::VEC3 pos;
    pos = pGimmick->GetScreenPosition();
    const float x = pos.x - rOffs.x;
    const float y = pos.y - rOffs.y;

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
