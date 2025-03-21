#ifndef FLUFF_EFFECTOBJ_H
#define FLUFF_EFFECTOBJ_H

#include "object/FlfHandleObj.h"

// size: 0xEC
class EffectObj : public FlfHandleObj {
public:
    EffectObj(int arg1, int arg2, int arg3, int arg4);
    void SetPosition(const nw4r::math::VEC3&);
    void fn_800a8268(const nw4r::math::VEC3&);
    void SetMatrix(const nw4r::math::MTX34&);
private:
    STRUCT_FILL(0xEC - sizeof(FlfHandleObj));
};

#endif
