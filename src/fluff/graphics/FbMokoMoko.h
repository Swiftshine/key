#ifndef FLUFF_FBMOKOMOKO_H
#define FLUFF_FBMOKOMOKO_H

#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflScnMdlWrapper.h"

// size: 0x154
class FbMokoMoko : public gfl::CustomRenderObj {
public:
    FbMokoMoko(float, float, float, const char*, gfl::ScnMdlWrapper*, uint, const char*, const char*);
    virtual ~FbMokoMoko();
    void UpdateMatrix(nw4r::math::VEC2&);
    
    inline void SetUnk150(bool value) {
        *(reinterpret_cast<bool*>(this) + 0x150) = value;
    }
private:
    STRUCT_FILL(0x154 - sizeof(gfl::CustomRenderObj));
};

#endif
