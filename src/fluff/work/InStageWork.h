#ifndef FLUFF_INSTAGEWORK_H
#define FLUFF_INSTAGEWORK_H

#include "types.h"

#include "stage/Stage.h"

// size: 0x1E4
class InStageWork {
private:
    struct InStageWork_struct {
        STRUCT_FILL(0x30);
    };

public:
    InStageWork();
    DECL_WEAK virtual ~InStageWork();

    void Reset();
    void CopyStage(const Stage& stage, void* arg2);
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
    int GetMaxZekeFound();
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
    void ResetMission(int arg1);
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

    union {
        struct {
            int mNumBeadsCollected;
            int m_24;
        };

        struct {
            int mBeadCollection_2[2];
        };

        struct {
            bool mBeadsCounted;
            int mBeadsCollected_3;
        };
    };

    int m_28;
    int m_2C;
    bool m_30;
    bool m_31;
    bool m_32;
    int m_34;
    bool m_38;
    int m_3C;
    int m_40;
    int m_44;
    int mNumZekeFound; // @ 0x48
    int mMaxZekeFound; // @ 0x4C
    float m_50;
    float m_54;
    float m_58;
    int m_5C;
    int mBeadThresholds[4]; // @ 0x60; the number of beads needed to get a wood, bronze, silver, or gold medal
    int m_70;
    int m_74;
    u8 m_78[0x18];
    bool m_90;
    bool m_91;
    bool m_92;
    bool m_93;
    
    // todo: the rest of this struct
    STRUCT_FILL(0x1E4 - 0x94);
};

ASSERT_SIZE(InStageWork, 0x1E4);

#endif
