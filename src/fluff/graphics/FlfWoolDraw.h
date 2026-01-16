#ifndef FLUFF_WOOLDRAW_H
#define FLUFF_WOOLDRAW_H

#include "types.h"
#include "gfl/gflResFileInfo.h"
#include "gfl/gflVec2.h"

/// @note Size: `0x60`
class FlfWoolDraw {
public:
    /* Structures */

    /// @note Size: `0x2C`
    struct Substruct {
        gfl::Vec2 m_0;
        STRUCT_FILL(0x24);
    };

    FlfWoolDraw();

    /* Virtual Methods */
    virtual ~FlfWoolDraw();

    /* Class Methods */

    /// @return Some index.
    int Register(gfl::ResFileObject* pResFileObject, const char* pWoolName1, const char* pWoolName2);
    void fn_800267B0(int index, int);
    void fn_80026A54(int);
    int fn_80026B54(int index);
    void fn_80026DFC(float);
    void fn_80026E74(float, uint index);
    void fn_80026E88(int);
    void fn_80026AB0(int, uint);
    void fn_80026A9C(uint index, nw4r::math::VEC2*);
    gfl::Vec2* fn_80026A60(uint index1, uint index2);
    void fn_80026B68(nw4r::math::MTX34* pMtx, bool);

    /* Class Members */

    /* 0x00 */ STRUCT_FILL(0x14);
    /* 0x18 */ float m_18;
    /* 0x1C */ float m_1C;
    /* 0x20 */ STRUCT_FILL(0x48 - 0x20);
    /* 0x48 */ Substruct* m_48;
    /* 0x4C */ STRUCT_FILL(0xC);
    /* 0x58 */ int m_58;
    /* 0x5C */ float m_5C;
};

#endif