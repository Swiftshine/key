#ifndef FLUFF_HENSHINSUBMARINE_H
#define FLUFF_HENSHINSUBMARINE_H

#include "object/player/HenshinCtrl.h"

/// @note Size: `0xEC`
class HenshinSubmarine : public HenshinCtrl {
public:
    /* Structures */

    struct Substruct1 {
        s32 m_0;
        s32 m_4;
        s32 m_8;
        s32 m_C;
    };

    /* Class Members */

    s32 m_58;
    s32 m_5C;
    Substruct1 m_60;
    STRUCT_FILL(0xEC - 0x70);
};

#endif
