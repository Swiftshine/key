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

    /* Constructor */

    FlfWoolDraw();

    /* Virtual Methods */
    virtual ~FlfWoolDraw();

    /* Class Methods */

    /// @return Some index.
    int Register(gfl::ResFileObject& rResFileObject, const char* pWoolName1, const char* pWoolName2);
    void fn_800267B0(int index, int);
    void fn_80026A54(int);
    void fn_80026DFC(float);

    gfl::Vec2* fn_80026A60(uint index1, uint index2);

    /* Class Members */

    STRUCT_FILL(0x14);
    float m_18;
    float m_1C;
    STRUCT_FILL(0x48 - 0x20);
    Substruct* m_48;
    STRUCT_FILL(0x60 - 0x4C);
};

#endif