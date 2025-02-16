#ifndef FLUFF_ENVUTILFRAMEBUFFER_H
#define FLUFF_ENVUTILFRAMEBUFFER_H

#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflScene.h"
#include "graphics/FB2Tex.h"

namespace env {
    class EnvUtil_FrameBuffer : public gfl::CustomRenderObj {
    public:
        static EnvUtil_FrameBuffer* Build(gfl::Scene* scene, int tranlucency, GXTexFmt texFormat, bool refreshTexture);
        EnvUtil_FrameBuffer(gfl::Scene* scene, int translucency, GXTexFmt texFormat, bool refreshTexture);

        virtual ~EnvUtil_FrameBuffer();
    private:
        gfl::Scene* mScene;
        FB2Tex* mFB2Tex;
        bool mIsActive;
        bool mShouldBlit;
    };

    ASSERT_SIZE(EnvUtil_FrameBuffer, 0x110);
}

#endif
