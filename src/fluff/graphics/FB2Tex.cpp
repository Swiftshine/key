#include "graphics/FB2Tex.h"

// https://decomp.me/scratch/WjWND
FB2Tex::FB2Tex(gfl::Scene* scene, u16 sourceW, u16 sourceH, u16 destW, u16 destH, bool arg6, int translucency, GXTexFmt texFormat, bool refreshTexture)
    : gfl::CustomRenderObj(false, true)
    , mScene(scene)
    , mImage(nullptr)
    , mSourceWidth(sourceW)
    , mSourceHeight(sourceH)
    , mDestWidth(destW)
    , mDestHeight(destH)
    , m_135(arg6)
    , mShouldRender(true)
    , mTextureFormat(texFormat) 
{
    mRefreshTexture = refreshTexture;
    m_134 = -1;
    SetPriorityDrawXlu(translucency);
    mScene->AddRenderObj(this);
    InitTexObj();
}

FB2Tex::~FB2Tex() {
    DisableFrameBuffer();
    mScene->RemoveRenderObj(this);
}

void FB2Tex::Blit(bool setBlendMode) {
    nw4r::g3d::Camera cam = mScene->GetScnRoot()->GetCurrentCamera();
    nw4r::math::MTX34 camMtx;
    nw4r::math::MTX44 projMtx;
    cam.GetCameraMtx(&camMtx);
    cam.GetProjectionMtx(&projMtx);

    GXCullMode cullMode;
    GXGetCullMode(&cullMode);
    nw4r::math::MTX34 mtx1;
    ZeroMTX(mtx1);

    PSMTXIdentity(mtx1);
    mtx1[2][3] = -1000.0f;
    nw4r::math::MTX34 mtx2;
    PSMTXCopy(mtx1, mtx2);
    GXLoadPosMtxImm(mtx2, 0);
    GXSetCurrentMtx(0);
    nw4r::math::MTX44 proj;

    float one = 1.0f;

    C_MTXOrtho(proj, one, -one, -one, one, 0.0, 10000.0f);
    GXSetProjection(proj, (GXProjectionType)1);

    GXSetChanCtrl((GXChannelID)4, FALSE, (GXColorSrc)0, (GXColorSrc)1, (GXLightID)0, (GXDiffuseFn)0, (GXAttnFn)2);
    GXInvalidateTexAll();
    GXLoadTexObj(&mTexObj, (GXTexMapID)0);
    GXSetNumTexGens(1);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetTexCoordGen2((GXTexCoordID)0, (GXTexGenType)1, (GXTexGenSrc)4, 0x3C, FALSE, 0x7D);
    GXSetTevOp((GXTevStageID)0, (GXTevMode)3);
    GXSetTevColorIn((GXTevStageID)0, (GXTevColorArg)8, (GXTevColorArg)0xF, (GXTevColorArg)0xF, (GXTevColorArg)0xF);
    GXSetTevColorOp((GXTevStageID)0, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, FALSE, (GXTevRegID)0);
    GXSetTevOrder((GXTevStageID)0, (GXTexCoordID)0, (GXTexMapID)0, (GXChannelID)4);
    GXSetAlphaCompare((GXCompare)7, 0, (GXAlphaOp)1, (GXCompare)7, 0);
    GXSetZMode(TRUE, (GXCompare)7, TRUE);
    GXSetVtxAttrFmt((GXVtxFmt)0, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxAttrFmt((GXVtxFmt)0, (GXAttr)0xD, (GXCompCnt)1, (GXCompType)4, 0);

    if (setBlendMode) {
        GXSetBlendMode((GXBlendMode)1, (GXBlendFactor)4, (GXBlendFactor)5, (GXLogicOp)0);
    } else {
        GXSetBlendMode((GXBlendMode)0, (GXBlendFactor)0, (GXBlendFactor)0, (GXLogicOp)0);
    }

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, (GXAttrType)1);
    GXSetVtxDesc((GXAttr)0xD, (GXAttrType)1);
    GXSetCullMode((GXCullMode)1);
    GXBegin(GX_TRIANGLESTRIP, (GXVtxFmt)0, 4);

    WGPIPE.f = -1.0f;
    WGPIPE.f = 1.0f;
    WGPIPE.f = 0.0f;
    WGPIPE.f = 0.0f;
    WGPIPE.f = 0.0f;
    WGPIPE.f = -1.0f;
    WGPIPE.f = -1.0f;
    WGPIPE.f = 0.0f;
    WGPIPE.f = 0.0f;
    WGPIPE.f = 1.0f;
    WGPIPE.f = 1.0f;
    WGPIPE.f = 1.0f;
    WGPIPE.f = 0.0f;
    WGPIPE.f = 1.0f;
    WGPIPE.f = 0.0f;
    WGPIPE.f = 1.0f;
    WGPIPE.f = -1.0f;
    WGPIPE.f = 0.0f;
    WGPIPE.f = 1.0f;
    WGPIPE.f = 1.0f;

    cam.SetCameraMtxDirectly(camMtx);
    cam.SetProjectionMtxDirectly(&projMtx);
    cam.GXSetProjection();
    GXSetCullMode(cullMode);
}

extern "C" {
    /* GX */
    u32 GXGetTexBufferSize(u16, u16, GXTexFmt, int, int);

    /* Fluff */
    void* GetFrameBufferData(int, u32, bool);
    void DisableFrameBufferByID(int);
    static GXRenderModeObj** CurrentRenderModeObj;
}

void FB2Tex::RefreshTexture() {
    u32 len = GXGetTexBufferSize(mDestWidth, mDestHeight, mTextureFormat, 0, 0);

    if (!mRefreshTexture) {
        if (mTextureFormat == GX_TF_RGBA8) {
            mImage = GetFrameBufferData(7, len, false);
        } else if (mTextureFormat == GX_TF_RGB565) {
            mImage = GetFrameBufferData(8, len, false);
        }
    }

    DCFlushRange(mImage, len);
    GXRenderModeObj* obj = *CurrentRenderModeObj;
    GXSetCopyFilter(obj->aa, obj->sample_pattern, 0, obj->vfilter);
    GXSetTexCopySrc(mSourceWidth, mSourceHeight, mDestWidth, mDestHeight);
    GXSetTexCopyDst(mDestWidth, mDestHeight, mTextureFormat, FALSE);
    GXCopyTex(mImage, m_135);
    GXPixModeSync();
    GXInitTexObj(&mTexObj, mImage, mDestWidth, mDestHeight, mTextureFormat, (GXTexWrapMode)0, (GXTexWrapMode)0, FALSE);
    float zero = 0.0f;
    GXInitTexObjLOD(&mTexObj, (GXTexFilter)1, (GXTexFilter)0, zero, zero, zero, FALSE, FALSE, (GXAnisotropy)0);
}

void FB2Tex::Render() {
    if (mShouldRender) {
        RefreshTexture();
    }
}

void FB2Tex::InitTexObj() {
    GXInitTexObj(&mTexObj, mImage, mDestWidth, mDestHeight, mTextureFormat, (GXTexWrapMode)0, (GXTexWrapMode)0, FALSE);
    float zero = 0.0f;
    GXInitTexObjLOD(&mTexObj, (GXTexFilter)1, (GXTexFilter)0, zero, zero, zero, FALSE, FALSE, (GXAnisotropy)0);
    u32 len = GXGetTexBufferSize(mDestWidth, mDestHeight, mTextureFormat, 0, 0);

    if (mTextureFormat == GX_TF_RGBA8) {
        mImage = GetFrameBufferData(7, len, mRefreshTexture);
    } else if (mTextureFormat == GX_TF_RGB565) {
        mImage = GetFrameBufferData(8, len, mRefreshTexture);
    }

    DCInvalidateRange(mImage, len);
}

void FB2Tex::DisableFrameBuffer() {
    if (mTextureFormat == GX_TF_RGBA8) {
        DisableFrameBufferByID(7);
    } else if (mTextureFormat == GX_TF_RGB565) {
        DisableFrameBufferByID(8);
    }
}
