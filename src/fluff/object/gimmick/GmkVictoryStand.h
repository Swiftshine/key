#ifndef FLUFF_GMKVICTORYSTAND_H
#define FLUFF_GMKVICTORYSTAND_H

#include "object/Gimmick.h"
#include "util/BeadUtil.h"
#include "graphics/ModelWrapper.h"
#include "object/collision/ColObj.h"
#include "misc/ScopedPointers.h"
#include "stage/StageResources.h"
#include "gfl/gflVec3.h"

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
    static void fn_804F1BDC(nw4r::math::VEC2& arg1, int rank);
    static void SpawnDecorativeBall(uint rank);
    static void SetRankingInfo(uint rank, nw4r::math::VEC2& position);

    GmkVictoryStand(GimmickBuildInfo* buildInfo, const char* taskName);
    virtual ~GmkVictoryStand();

    /* Gimmick */
    virtual void Update();

    void AwardBeads() DONT_INLINE_CLASS;
private:
    int mCurrentState;
    int mPreviousState; // guessed
    int mBeadAwardState;
    int m_13C;
    int m_140;
    uint mPlayerRanking;
    gfl::Vec3 mBeadAwardPosition;
    int mTotalAwardedBeads;
    gfl::ScopedPointer<ModelWrapper> mModel;
    gfl::ScopedPointer<ColObjTrans> mColObj;
    GimmickBuildInfo mDecorativeBallBuildInfo;
};

#endif
