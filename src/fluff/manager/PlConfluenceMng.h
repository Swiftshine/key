#ifndef FLUFF_PLCONFLUENCEMNG_H
#define FLUFF_PLCONFLUENCEMNG_H

#include "object/FlfHandleObj.h"
#include "gfl/gflVec2.h"

/// @brief Used for managing transformations that involve
/// two players.
/// @note Size: `0x2C`
class PlConfluenceMng {
public:
    virtual ~PlConfluenceMng();

    /* Class Members */

    /* 0x04 */ int mCurrentState;
    /* 0x08 */ int mPreviousState;
    /* 0x0C */ int m_C;
    /* 0x10 */ int m_10;
    /* 0x14 */ int m_14;
    /* 0x18 */ FlfHandle mPlayerHandle;
    /* 0x20 */ gfl::Vec2 m_20;
    /* 0x28 */ int m_28;
};

#endif