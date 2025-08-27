#ifndef FLUFF_FBALPHA_H
#define FLUFF_FBALPHA_H

#include "gfl/gflCustomRenderObj.h"

class FbAlpha : public gfl::CustomRenderObj {
public:
    /* Constructor */

    FbAlpha();

    /* Virtual Methods */

    /* 0x08 */ virtual ~FbAlpha();

    /* Class Members */

    /* 0x104 */ GXColor mColor;
};

ASSERT_SIZE(FbAlpha, 0x108);

#endif
