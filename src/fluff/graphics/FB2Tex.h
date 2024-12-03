#ifndef FLUFF_FB2TEX_H
#define FLUFF_FB2TEX_H

#include "gfl/gflCustomRenderObj.h"

// presumably "Frame Buffer to Texture", since it's used by
// env::EnvUtil_FrameBuffer
class FB2Tex : public gfl::CustomRenderObj {
public:
    FB2Tex(int arg1, u16 arg2, u16 arg3, u16 imageWidth, u16 imageHeight, bool arg6, int arg7, GXTexFmt texFormat, bool arg9);
    virtual ~FB2Tex();

    /* gfl::CustomRenderObj */
    virtual void Render();

    // funcs
    void InitTexObj();
    void DoRender();
    void fn_80029AF0();
    
private:
    int m_104;
    GXTexObj mTexObj;
    void* mImage;
    u16 m_12C;
    u16 m_12E;
    u16 mImageWidth;
    u16 mImageHeight;
    bool m_134;
    bool m_135;
    bool mShouldRender;
    bool m_137;
    GXTexFmt mTextureFormat;
};

ASSERT_SIZE(FB2Tex, 0x13C);

#endif
