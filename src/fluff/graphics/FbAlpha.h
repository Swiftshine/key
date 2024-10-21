#ifndef FLUFF_FBALPHA_H
#define FLUFF_FBALPHA_H

#include "gfl/gflCustomRenderObj.h"

class FbAlpha : public gfl::CustomRenderObj {
public:
    FbAlpha();
    virtual ~FbAlpha();


private:
    GXColor mColor;
};

ASSERT_SIZE(FbAlpha, 0x108);

#endif
