#ifndef FLUFF_STATEOBJECT_H
#define FLUFF_STATEOBJECT_H

/// @brief A collection of different state types.
/// Not all of them have to be used.
/// @note Note the difference between the terms "state" and "current state."
/// They are distinct.
/// @note Size: `0x14`
struct StateObject {
    // note to self: if you ever have to make a ctor with an identical signature,
    // you're better off making single-value structs for all the members of this structure
    // and using *them* in the ctor
    
    inline StateObject(int curState) {
        SetCurrentStateAndClearOthers(curState);
    }

    inline int GetCurrentState() const {
        return mCurrentState;
    }

    inline void SetCurrentState(int state) {
        mPreviousState = mCurrentState;
        mCurrentState = mPreviousState;
    }

    inline void SetCurrentStateAndClearOthers(int state) {
        mPreviousState = mCurrentState;
        mCurrentState = state;

        mState = 0;
        mDefaultState = 0;
        mCounter = 0;
    }

    inline void SetStateAndResetCounter(int state) {
        mState = state;
        mCounter = 0;
    }

    // v generally used together
    /* 0x00 */ int mCurrentState;
    /* 0x04 */ int mPreviousState;

    // v generally used together
    /* 0x08 */ int mState;
    /* 0x0C */ int mDefaultState;

    /* 0x10 */ int mCounter;
};

#endif