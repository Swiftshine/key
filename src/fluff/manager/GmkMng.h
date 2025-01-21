#ifndef FLUFF_GMKMNG_H
#define FLUFF_GMKMNG_H


#include "types.h"
#include "gfl/gflTask.h"
#include "gfl/gflLinkedList.h"

#include <string>
#include <vector>

class Gimmick;
class GimmickBuildInfo;
class GimmickResource;
class Mapdata;

class GmkMng {
private:
    static GmkMng* sInstance;
public:
    static GmkMng* Instance() { return sInstance; }

    GmkMng();
    ~GmkMng();

    void SetupGimmicks(Mapdata* mapdata);
    void SetMapdata(Mapdata* mapdata);
    void AddGimmick(Gimmick* gmk);
    void RemoveGimmick(Gimmick* gmk);
    void ClearAll(bool arg1);
    void GetGimmicksByGimmickID(int gimmickID, std::vector<Gimmick>& dest);
    void GetCommonGimmicksByID(int gimmickID, std::vector<Gimmick>& dest);
    Gimmick* GetGimmickByCommonTag(std::string& query);
    GimmickBuildInfo* GetCommonGimmickBuildInfoByCommonTag(const char* query);
    void RegisterResources(const char* name, Gimmick* gimmick);
    void CreateGimmick(GimmickBuildInfo* buildInfo);
    void CreateGimmicksFromMapdata();
    void fn_8005174C();
    void AddEffect(GimmickBuildInfo* buildInfo);
    bool IsInSpawnRadius(nw4r::math::VEC2& offset, GimmickBuildInfo* buildInfo);
    bool IsOnGimmickOnScreen(nw4r::math::VEC2& offset, Gimmick* gimmick);
    // calls vf68 on every gimmick
    void fn_80051B3C();
    
    bool fn_801C1A60();
private:
    int mState;
    uint m_4;
    gfl::LinkedList<Gimmick*> mGimmicks;
    gfl::LinkedList<FlfHandle> mEffects;
    gfl::LinkedList<GimmickResource> mGimmickResources;
    Mapdata* mMapdata;
    gfl::Task* mCurrentTask;
};
#endif
