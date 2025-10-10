#ifndef FLUFF_SCNMDLCALLBACKBASE_H
#define FLUFF_SCNMDLCALLBACKBASE_H

#include <nw4r/g3d/g3d_calcworld.h>

/// @note Size: `0x14`
class ScnMdlCallbackBase : public nw4r::g3d::ICalcWorldCallback {
public:

    /* Virtual Methods */

    /* 0x08 */ virtual ~ScnMdlCallbackBase();
    /* 0x0C */ virtual void vfC();
    /* 0x10 */ virtual void vf10();
    /* 0x14 */ virtual void vf14();
    /* 0x18 */ virtual void DisableScnMdlCallbackTiming(void* pArg1);

    /* Class Members */

    /* 0x04 */ u32 m_4;
    /* 0x08 */ u32 m_8;
    /* 0x0C */ u32 m_C;
    /* 0x10 */ u32 m_10;
};

ASSERT_SIZE(ScnMdlCallbackBase, 0x14);

#endif
