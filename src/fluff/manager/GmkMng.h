#ifndef FLUFF_GMKMNG_H
#define FLUFF_GMKMNG_H


#include "types.h"

#include <nw4r/math.h>
#include <string>
#include <vector>

#include "gfl/gflTask.h"
#include "gfl/gflLinkedList.h"
#include "object/FlfHandleObj.h"
#include "manager/CameraManager.h"
#include "object/Gimmick.h"

class GimmickResource;
class Mapdata;

class GmkMng {
private:
    static GmkMng* sInstance;
public:
    ENUM_CLASS(State,
        None = 0,
        CreateCommonGimmicks = 1,
        CutAction2 = 2, // this action doesnt do anything
        ConstructMapdataObjects = 3,
        CutAction4 = 4,
        ManageGimmickCulling = 5, // spawn or despawn gimmicks based on culling
    );
    
    static GmkMng* Instance() { return sInstance; }

    GmkMng();
    ~GmkMng();

    void SetupGimmicks(Mapdata* mapdata);
    void SetMapdata(Mapdata* mapdata);
    void AddGimmick(Gimmick* gmk);
    void RemoveGimmick(Gimmick* gmk);
    void ClearAll(bool arg1);
    void GetGimmicksByGimmickID(int gimmickID, std::vector<Gimmick*>& dest);
    void GetCommonGimmicksByID(int gimmickID, std::vector<Gimmick::GimmickBuildInfo*>& dest);
    Gimmick* GetGimmickByCommonTag(const std::string& query);
    Gimmick::GimmickBuildInfo* GetCommonGimmickBuildInfoByCommonTag(const char* query);
    void RegisterResources(const char* name, Gimmick* gimmick);
    void CreateGimmick(Gimmick::GimmickBuildInfo* buildInfo);
    void CreateGimmicksFromMapdata();
    void fn_8005174C();
    void AddEffect(Gimmick::GimmickBuildInfo* buildInfo);
    bool IsGimmickInSpawnRadius(nw4r::math::VEC2& offset, Gimmick::GimmickBuildInfo* buildInfo);
    bool IsGimmickOnScreen(nw4r::math::VEC2& offset, Gimmick* gimmick);
    // calls vf68 on every gimmick
    void fn_80051B3C();
    
    bool fn_801C1A60();
private:
    int mState;
    uint mNumCommonGimmicks;
    gfl::LinkedList<Gimmick*> mGimmicks;
    gfl::LinkedList<FlfHandle> mEffects;
    gfl::LinkedList<GimmickResource*> mGimmickResources;
    Mapdata* mMapdata;
    gfl::Pointer<gfl::Task> mTask;
};
#endif
