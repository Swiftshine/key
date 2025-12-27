#ifndef FLUFF_FB2TEX_H
#define FLUFF_FB2TEX_H

#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflScene.h"


/// @brief Stands for "Frame Buffer to Texture."
class FB2Tex : public gfl::CustomRenderObj {
public:
    

    FB2Tex(gfl::Scene* pScene, u16 sourceW, u16 sourceH, u16 destW, u16 destH, bool arg6, int translucency, GXTexFmt texFormat, bool refreshTexture, const char* pName);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FB2Tex();
    /* 0xC4 */ virtual void DrawXlu() override;

    /* Class Methods */

    void Blit(bool setBlendMode);
    void RefreshTexture();
    void InitTexObj();
    void DoRender();
    void DisableFrameBuffer();

    /* Class Members */

    /* 0x104 */ gfl::Scene* mScene;
    /* 0x108 */ GXTexObj mTexObj;
    /* 0x128 */ void* mImage;
    /* 0x12C */ u16 mSourceWidth;
    /* 0x12E */ u16 mSourceHeight;
    /* 0x130 */ u16 mDestWidth;
    /* 0x132 */ u16 mDestHeight;
    /* 0x134 */ u8 m_134;
    /* 0x135 */ bool m_135;
    /* 0x136 */ bool mShouldRender;
    /* 0x137 */ bool mRefreshTexture;
    /* 0x138 */ GXTexFmt mTextureFormat;
};

ASSERT_SIZE(FB2Tex, 0x13C);

#endif
