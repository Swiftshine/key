#ifndef FLUFF_HENSHINSUBMARINE_H
#define FLUFF_HENSHINSUBMARINE_H

#include "object/player/HenshinCtrl.h"

/// @note Size: `0xEC`
class HenshinSubmarine : public HenshinCtrl {
public:
    /* Structures */

    struct Substruct1 {
        int m_0;
        int m_4;
        int m_8;
        int m_C;
    };

    /* Class Members */

    int m_58;
    int m_5C;
    Substruct1 m_60;
    STRUCT_FILL(0xEC - 0x70);
};

#endif