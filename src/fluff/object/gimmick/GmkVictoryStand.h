#ifndef FLUFF_GMKVICTORYSTAND_H
#define FLUFF_GMKVICTORYSTAND_H

#include "gfl/gflVec3.h"
#include "graphics/GmkPartsMdlSet.h"
#include "misc/ScopedPointers.h"
#include "object/Gimmick.h"
#include "object/collision/ColObj.h"
#include "util/BeadUtil.h"
#include "util/StateObject.h"
#include "stage/StageResources.h"

// size: 0x1FC
class GmkVictoryStand : public Gimmick {
private:
    static GmkVictoryStand* sInstance;
public:
    static GmkVictoryStand* Instance() {
        return sInstance;
    }

    static void AddDecorativeBallResources();
    static GmkVictoryStand* Build(GimmickBuildInfo* buildInfo);
    static void fn_804F1BDC(nw4r::math::VEC2& arg1, s32 rank);
    static void SpawnDecorativeBall(u32 rank);
    static void SetRankingInfo(u32 rank, nw4r::math::VEC2& position);

    GmkVictoryStand(GimmickBuildInfo* buildInfo, const char* taskName);
    virtual ~GmkVictoryStand();

    /* Gimmick */
    virtual void Update();

    void AwardBeads() DONT_INLINE_CLASS;
private:
    StateObject mBeadAwardState;
    u32 mPlayerRanking;
    gfl::Vec3 mBeadAwardPosition;
    s32 mTotalAwardedBeads;
    gfl::Pointer<GmkPartsMdlSet> mModel;
    gfl::Pointer<ColObjTrans> mColObj;
    GimmickBuildInfo mDecorativeBallBuildInfo;
};

#endif
