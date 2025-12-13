#ifndef FLUFF_FBDOF_H
#define FLUFF_FBDOF_H

#include "types.h"
#include <revolution/GX.h>
#include "gfl/gflCustomRenderObj.h"

/// @brief Frame Buffer Depth of Field
class FbDof : public gfl::CustomRenderObj {
public:
    /* Constructor */

    FbDof();

    /* Virtual Methods */

    /* 0x08 */ virtual ~FbDof();

    /* 0x9C */ virtual void vf9C() override;
    /* 0xC4 */ virtual void DrawXlu() override; // calls CheckRender()

    /* Class Methods */

    void CheckRender();
    void DoRender();

    /* Class Members */

    /* 0x104 */ u16 mWidth;
    /* 0x106 */ u16 mHeight;
    /* 0x108 */ GXTexFmt mFormat;
    /* 0x10C */ u16 mYPosition;
    /* 0x110 */ void* mImage;
    /* 0x114 */ float m_114;
    /* 0x118 */ bool m_118;
};

ASSERT_SIZE(FbDof, 0x11C);

#endif
