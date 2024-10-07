#ifndef FLUFF_INSTAGEWORK_H
#define FLUFF_INSTAGEWORK_H

#include "types.h"
#include "stage/Stage.h"

// size: 0x1E4
class InStageWork {
public:
    InStageWork();
    virtual ~InStageWork();

    void SetBeadCount(int index, int max);
    void SetTimeRemaining(uint time);
    
    inline uint GetTimeLimit() {
        return mTimeLimit;
    }

    inline uint GetTimeRemaining() {
        return mTimeRemaining;
    }

    inline uint GetTimeElapsed() {
        return mTimeLimit - mTimeRemaining;
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
    uint mTimeLimit; // milliseconds
    uint mTimeRemaining; // milliseconds
    int mNumBeadsCollected;
    int m_24;

    // todo; research the rest
    STRUCT_FILL(0x1E4 - 0x28);
};

ASSERT_SIZE(InStageWork, 0x1E4);

#endif
