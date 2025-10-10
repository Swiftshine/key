#ifndef FLUFF_BGBACKIMAGE_H
#define FLUFF_BGBACKIMAGE_H

#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflResFileInfo.h"
#include "gfl/gflPointer.h"
#include <revolution/GX.h>

/// @brief This class is used as the "missing texture" image when BGST data is not loaded.
class BgBackImage : public gfl::CustomRenderObj {
public:
    /* Constructor */

    BgBackImage();

    /* Virtual Methods */

    /* 0x08 */ virtual ~BgBackImage();

    /* 0xB4 */ virtual void Render() override;

    /* Class Members */

    /* 0x104 */ GXTexObj mTexObj;
    /* 0x124 */ float mWidth;
    /* 0x128 */ float mHeight;
    /* 0x12C */ gfl::ResFileObject mResFileInfo;
};

ASSERT_SIZE(BgBackImage, 0x130);

#endif
