#ifndef FLUFF_PLCONFLUENCEMNG_H
#define FLUFF_PLCONFLUENCEMNG_H

#include "util/StateObject.h"
#include "object/FlfHandleObj.h"
#include "gfl/gflVec2.h"

/// @brief Used for managing transformations that involve
/// two players.
/// @note Size: `0x2C`
class PlConfluenceMng {
public:
    virtual ~PlConfluenceMng();

    /* Class Members */

    /* 0x04 */ StateObject mState;
    /* 0x18 */ FlfHandle mPlayerHandle;
    /* 0x20 */ gfl::Vec2 m_20;
    /* 0x28 */ int m_28;
};

#endif