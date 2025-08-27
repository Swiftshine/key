#ifndef FLUFF_FBMOKOMOKO_H
#define FLUFF_FBMOKOMOKO_H

#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflScnMdlWrapper.h"

// size: 0x154
class FbMokoMoko : public gfl::CustomRenderObj {
public:
    /* Constructor */
    FbMokoMoko(float, float, float, const char*, gfl::ScnMdlWrapper*, uint, const char*, const char*);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FbMokoMoko();

    /* Class Methods */

    void UpdateMatrix(nw4r::math::VEC2 const &);
    
    inline void SetUnk150(bool value) {
        *(reinterpret_cast<bool*>(this) + 0x150) = value;
    }

    /* Class Members */

    /* 0x104 */ STRUCT_FILL(0x154 - sizeof(gfl::CustomRenderObj));
};

#endif
