#ifndef FLUFF_GMKMEKURI2_H
#define FLUFF_GMKMEKURI2_H

#include "object/Gimmick.h"

/// @brief The cloth patch gimmick.
/// @note Size: `0x264`
class GmkMekuri2 : public Gimmick {
public:
    /* 0x130 */ STRUCT_FILL(0x1A4 - 0x130);
    /* 0x1A4 */ int mSceneID;
    /* 0x1A8 */ int m_1A8;
    /* 0x1AC */ STRUCT_FILL(0x264 - 0x1AC);
};

#endif