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
    void SetTimeRemaining(int time);
    
    inline int GetTimeLimit() {
        return mTimeLimit;
    }

    inline int GetTimeRemaining() {
        return mTimeRemaining;
    }

    inline int GetTimeElapsed() {
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
    int mTimeLimit; // milliseconds
    int mTimeRemaining; // milliseconds
    int mNumBeadsCollected;
    int m_24;

    // todo; research the rest
    STRUCT_FILL(0x1E4 - 0x28);
};

ASSERT_SIZE(InStageWork, 0x1E4);

#endif
