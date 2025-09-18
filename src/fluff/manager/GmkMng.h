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
public:
    /* Static Variables */

    static GmkMng* sInstance;

    static inline GmkMng* Instance() {
        return sInstance;
    }

    /* Enums */

    ENUM_CLASS(State,
        None = 0,
        CreateCommonGimmicks = 1,
        CutAction2 = 2,
        ConstructMapdataObjects = 3, // Construct paths, zones, and friend gimmicks.
        CutAction4 = 4,
        ManageGimmickCulling = 5, // Spawn or cull gimmicks based on position relative to the camera.
    );
    

    /* Constructor + Destructor */

    GmkMng();
    ~GmkMng();

    /* Class Methods */

    void CreateGimmicksFromMapdata(Mapdata* pMapdata);
    void SetMapdata(Mapdata* pMapdata);
    void AddGimmick(Gimmick* pGmk);
    void RemoveGimmick(Gimmick* pGmk);
    void ClearAll(bool arg1);
    void GetGimmicksByGimmickID(int gimmickID, std::vector<Gimmick*>& rDest);
    void GetCommonGimmicksByID(int gimmickID, std::vector<Gimmick::GimmickBuildInfo*>& rDest);
    Gimmick* GetGimmickByCommonTag(const std::string& rQuery);
    Gimmick::GimmickBuildInfo* GetCommonGimmickBuildInfoByCommonTag(const char* pQuery);
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

    inline Gimmick* GetGimmickByTag(const std::string& rTag) {
        gfl::LinkedList<Gimmick*>::NodeBase* node = mGimmicks.GetNode()->GetNext();
        gfl::LinkedList<Gimmick*>::NodeBase* end = mGimmicks.GetNode();

        Gimmick* gimmick = nullptr;

        while (node != end) {
            gimmick = node->ToNode()->GetData();
    
            if (gimmick->GetGimmickBuildInfoPtr() != nullptr &&
                rTag == gimmick->GetGimmickBuildInfoPtr()->GetCommonTag()
            ) {
                break;
            } 
    
            node = node->GetNext();
        }
    
        return gimmick;
    }
    

    /* Class Members */

    /* 0x00 */ int mState;
    /* 0x04 */ uint mNumCommonGimmicks;
    /* 0x08 */ gfl::LinkedList<Gimmick*> mGimmicks;
    /* 0x14 */ gfl::LinkedList<FlfHandle> mEffects;
    /* 0x20 */ gfl::LinkedList<GimmickResource*> mGimmickResources;
    /* 0x2C */ Mapdata* mMapdata;
    /* 0x30 */ gfl::Pointer<gfl::Task> mTask;
};

ASSERT_SIZE(GmkMng, 0x34);

#endif
