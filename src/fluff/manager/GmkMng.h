#ifndef FLUFF_GMKMNG_H
#define FLUFF_GMKMNG_H


#include "types.h"

#include <nw4r/math.h>
#include <string>
#include <vector>

#include "gfl/gflTask.h"
#include "gfl/gflLinkedList.h"
#include "object/FlfHandleObj.h"
#include "manager/CamMng.h"
#include "object/Gimmick.h"

class GimmickResource;
class Mapdata;

class GmkMng {
public:
    /* Static Variables */

    static GmkMng* sInstance;

    static inline GmkMng* Instance() {
        return sInstance;
    }

    /* Enums */

    enum State {
        eState_None                     = 0,
        eState_CreateCommonGimmicks     = 1,
        eState_Cut2 = 2,
        eState_ConstructMapdataObjects  = 3,     // Construct paths, zones, and friend gimmicks.
        eState_Cut4 = 4,
        eState_ManageGimmickCulling,            // Spawn or cull gimmicks based on position relative to the camera.
    };

    GmkMng();
    ~GmkMng();

    /* Class Methods */

    void CreateGimmicksFromMapdata(Mapdata* pMapdata);
    void SetMapdata(Mapdata* pMapdata);
    void AddGimmick(Gimmick* pGmk);
    void RemoveGimmick(Gimmick* pGmk);
    void ClearAll(bool arg1);
    void GetGimmicksByGimmickID(s32 gimmickID, std::vector<Gimmick*>& rDest);
    void GetCommonGimmicksByID(s32 gimmickID, std::vector<Gimmick::GimmickBuildInfo*>& rDest);
    Gimmick* GetGimmickByIdentifier(const std::string& rQuery);
    Gimmick::GimmickBuildInfo* GetCommonGimmickBuildInfoByIdentifier(const char* pQuery);
    void RegisterResources(const char* pName, Gimmick* pGmk);
    void CreateGimmick(Gimmick::GimmickBuildInfo* pBuildInfo) DONT_INLINE_CLASS;
    void CreateGimmicksFromMapdata();
    void ManageOnScreenGimmicks();
    void AddEffect(Gimmick::GimmickBuildInfo* pBuildInfo);
    bool IsGimmickInSpawnRadius(const nw4r::math::VEC2& rOffset, Gimmick::GimmickBuildInfo* pBuildInfo);
    bool IsGimmickOnScreen(const nw4r::math::VEC2& pGmk, Gimmick* gimmick);
    // calls vf68 on every gimmick
    void fn_80051B3C();

    bool fn_801C1A60();

    inline void CreateGimmickConditionally(const nw4r::math::VEC2& rPos, Gimmick::GimmickBuildInfo* pBuildInfo);

    /* Class Members */

    /* 0x00 */ s32 mState;
    /* 0x04 */ uint mNumCommonGimmicks;
    /* 0x08 */ std::list<Gimmick*> mGimmicks;
    /* 0x14 */ std::list<FlfHandle> mEffects;
    /* 0x20 */ std::list<GimmickResource*> mGimmickResources;
    /* 0x2C */ Mapdata* mMapdata;
    /* 0x30 */ gfl::Pointer<gfl::Task> mTask;
};

ASSERT_SIZE(GmkMng, 0x34);

#endif
