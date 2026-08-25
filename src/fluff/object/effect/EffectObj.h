#ifndef FLUFF_EFFECTOBJ_H
#define FLUFF_EFFECTOBJ_H

#include "object/FlfHandleObj.h"

// size: 0xEC
class EffectObj : public FlfHandleObj {
public:
    

    EffectObj(s32 arg1, s32 arg2, s32 arg3, s32 arg4);

    /* Class Methods */
    void SetPosition(const nw4r::math::VEC3&);
    void fn_800a8268(const nw4r::math::VEC3&);
    void SetMatrix(const nw4r::math::MTX34&);
private:
    STRUCT_FILL(0xEC - sizeof(FlfHandleObj));
};

#endif
