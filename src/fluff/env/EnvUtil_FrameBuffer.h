#ifndef FLUFF_ENVUTILFRAMEBUFFER_H
#define FLUFF_ENVUTILFRAMEBUFFER_H

#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflScene.h"
#include "graphics/FB2Tex.h"

namespace env {
    class EnvUtil_FrameBuffer : public gfl::CustomRenderObj {
    public:
        

        EnvUtil_FrameBuffer(gfl::Scene* pScene, int translucency, GXTexFmt texFormat, bool refreshTexture);

        /* Virtual Methods */

        /* 0x08 */ virtual ~EnvUtil_FrameBuffer();

        /* Static Methods */

        static EnvUtil_FrameBuffer* Build(gfl::Scene* pScene, int tranlucency, GXTexFmt texFormat, bool refreshTexture);

        /* Class Members */

        /* 0x104 */ gfl::Scene* mScene;
        /* 0x108 */ FB2Tex* mFB2Tex;
        /* 0x10C */ bool mIsActive;
        /* 0x10D */ bool mShouldBlit;
    };

    ASSERT_SIZE(EnvUtil_FrameBuffer, 0x110);
}

#endif
