#ifndef FLUFF_INSTAGEWORK_H
#define FLUFF_INSTAGEWORK_H

#include "types.h"
#include "stage/Stage.h"

// size: 0x1E4
class InStageWork {
public:
    InStageWork();
    DECL_WEAK virtual ~InStageWork();

    void Reset();
    void CopyStage(Stage& stage, void* arg2);
    void Init();
    void fn_801FEEB8(int arg1);
    void SetTimeLimit(int limit);
    void SetTimeRemaining(int time);
    void SetBeadCount(int index, int max);
    void fn_801FEF74(int arg1, int arg2, int arg3);
    void fn_801FF0A4(int arg1, int arg2);
    void fn_801FF194(int arg1);
    void fn_801FF294(int arg1);
    void fn_801FF3B0(int arg1);
    void fn_801FF3B8(int arg1);
    int GetTimeElapsed(int arg1);
    void fn_801FF3E8(int arg1);
    void fn_801FF3F8(int arg1);
    int fn_801FF400();
    void AddNumZekeFound(int num);
    void SetMaxZekeFound(int max);
    int GetNumZekeFound();
    void fn_801FF428(float& arg1, int arg2);
    float fn_801FF448(int arg1);
    int fn_801FF46C(int arg1);
    float fn_801FF4CC(int arg1);
    int fn_801FF4D4();
    void fn_801FF4DC();
    void fn_801FF544(int arg1, int arg2);
    void fn_801FF55C(int arg1);
    int fn_801FF57C();
    void fn_801FF600();
    void fn_801FF628();
    void fn_801FF6B0(int arg1, int arg2, int arg3);
    void fn_801FF6CC();
    void fn_801FF7B0(int arg1);
    int fn_801FF7C0();
    void fn_801FF7DC();
    int fn_801FF83C();
    void fn_801FF964();
    void fn_801FF9A4();
    int fn_801FFA24();
    void ResetMission();
    void fn_801FFA84(int resourceID);
    bool fn_801FFAA0(int stageID);

    inline int GetTimeLimit() {
        return mTimeLimit;
    }

    inline int GetTimeRemaining() {
        return mTimeRemaining;
    }

    inline int GetNumBeadsCollected() {
        return mNumBeadsCollected;
    }

    inline int GetUnk24() {
        return m_24;
    }
private:
    Stage mStage;
    void* m_10;
    int m_14;
    int mTimeLimit; // milliseconds
    int mTimeRemaining; // milliseconds
    int mNumBeadsCollected;
    int m_24;

    // todo; research the rest
    STRUCT_FILL(0x1E4 - 0x28);
};

ASSERT_SIZE(InStageWork, 0x1E4);

#endif
