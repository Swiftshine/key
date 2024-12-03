#ifndef FLUFF_FB2TEX_H
#define FLUFF_FB2TEX_H

#include "gfl/gflCustomRenderObj.h"

// presumably "Frame Buffer to Texture", since it's used by
// env::EnvUtil_FrameBuffer
class FB2Tex : public gfl::CustomRenderObj {
public:
    FB2Tex(int arg1, u16 sourceW, u16 sourceH, u16 destW, u16 destH, bool arg6, int translucency, GXTexFmt texFormat, bool refreshTexture);
    virtual ~FB2Tex();

    /* gfl::CustomRenderObj */
    virtual void Render();

    // funcs
    void InitTexObj();
    void DoRender();
    void fn_80029AF0();
    void SetPriorityDrawTranslucency(int translucency);
private:
    int m_104;
    GXTexObj mTexObj;
    void* mImage;
    u16 mSourceWidth;
    u16 mSourceHeight;
    u16 mDestWidth;
    u16 mDestHeight;
    bool m_134;
    bool m_135;
    bool mShouldRender;
    bool mRefreshTexture;
    GXTexFmt mTextureFormat;
};

ASSERT_SIZE(FB2Tex, 0x13C);

#endif
