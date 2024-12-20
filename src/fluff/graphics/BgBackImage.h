#ifndef FLUFF_BGBACKIMAGE_H
#define FLUFF_BGBACKIMAGE_H

#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflResFileInfo.h"
#include "gfl/gflPointer.h"
#include <revolution/GX.h>

// used as the "missing texture" image when
// BGST data fails to load
class BgBackImage : public gfl::CustomRenderObj {
public:
    BgBackImage();
    virtual ~BgBackImage();
    virtual void Render();

private:
    GXTexObj mTexObj;
    float mWidth;
    float mHeight;
    gfl::ResFileObject mResFileInfo;
};

ASSERT_SIZE(BgBackImage, 0x130);

#endif
