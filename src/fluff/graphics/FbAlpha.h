#ifndef FLUFF_FBALPHA_H
#define FLUFF_FBALPHA_H

#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflColor.h"
class FbAlpha : public gfl::CustomRenderObj {
public:
    /* Constructor */

    FbAlpha();

    /* Virtual Methods */

    /* 0x08 */ virtual ~FbAlpha();

    /* Class Methods */
    void SetColor(const gfl::Color& rColor);

    /* Class Members */

    /* 0x104 */ gfl::Color mColor;
};

ASSERT_SIZE(FbAlpha, 0x108);

#endif
