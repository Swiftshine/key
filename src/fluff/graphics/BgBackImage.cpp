#include <nw4r/g3d/res/g3d_resfile.h>

#include "GX/GXTypes.h"
#include "GX/GXVert.h"
#include "gflResFileInfo.h"
#include "graphics/BgBackImage.h"
#include "types.h"
#include "util/FullSortSceneUtil.h"
#include "graphics/FullSortScene.h"
#include "manager/Stage.h"
#include "manager/CamMng.h"

BgBackImage::BgBackImage()
    : CustomRenderObj(true, false, "BgBackImage")
    , mResFileObject(nullptr)
{
    mResFileObject = gfl::ResFileObject::FromArchive("gimmick/bgTex/bgTex.brtex");

    nw4r::g3d::ResFile resfile(mResFileObject.IsValid() ? mResFileObject->GetGfArch() : nullptr);

    NW4R_G3D_RESFILE_AC_ASSERT(resfile);

    nw4r::g3d::ResTex tex = resfile.GetResTex("2pend");

    void* image;
    u16 width;
    u16 height;
    GXTexFmt format;
    float minLod;
    float maxLod;
    GXBool mipMap;

    tex.GetTexObjParam(&image, &width, &height, &format, &minLod, &maxLod, &mipMap);
    GXInitTexObj(&mTexObj, image, width, height, format, GX_REPEAT, GX_REPEAT, mipMap);

    mWidth = static_cast<float>(width);
    mHeight = static_cast<float>(height);

    MTX34 matrix; // never used
    ZERO_MTX_34(matrix);
    PSMTXIdentity(matrix);

    float zOrder = FullSortSceneUtil::GetZOrder(0, 1) - 105.0f - 100.0f;
    
    gfl::Vec3 vec(0.0f);
    vec.z = zOrder;
    
    matrix[0][3] = vec.x;
    matrix[1][3] = vec.y;
    matrix[2][3] = vec.z;

    FullSortScene* fss = Stage::Instance()->GetFullSortSceneByID(0);
    fss->AddRenderObj(static_cast<gfl::RenderObj*>(this));
}

BgBackImage::~BgBackImage() { }

#define FLOOR(x) static_cast<float>(static_cast<int>(x))
#define SCALE_FACTOR 46.0f

void BgBackImage::DrawXlu() {
    nw4r::math::MTX34 mtx;
    ZERO_MTX_34(mtx);

    nw4r::g3d::ScnObj::GetMtx(MTX_VIEW, &mtx);
    GXLoadPosMtxImm(mtx, 0);
    GXSetCurrentMtx(0);
    GXLoadTexObj(&mTexObj, GX_TEXMAP0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, false, GX_SRC_REG, GX_SRC_REG, (GXLightID)0, GX_DF_NONE, GX_AF_NONE);
    GXSetZCompLoc(true);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetColorUpdate(true);
    GXSetAlphaUpdate(true);
    GXSetTexCoordGen2((GXTexCoordID)0, GX_TG_MTX2x4, (GXTexGenSrc)4, 0x3C, false, 0x7D);
    GXSetNumTexGens(1);
    GXSetNumIndStages(0);
    GXSetTevDirect((GXTevStageID)0);
    GXSetTevDirect((GXTevStageID)1);
    GXSetBlendMode((GXBlendMode)0, (GXBlendFactor)4, (GXBlendFactor)5, (GXLogicOp)0);
    GXSetZMode(false, (GXCompare)3, false);
    GXSetCullMode((GXCullMode)0);
    GXSetNumTevStages(1);
    GXSetTevOrder((GXTevStageID)0, (GXTexCoordID)0, (GXTexMapID)0, (GXChannelID)0xff);
    GXSetTevSwapMode((GXTevStageID)0, (GXTevSwapSel)0, (GXTevSwapSel)0);
    GXSetTevColorOp((GXTevStageID)0, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, false, (GXTevRegID)0);
    GXSetTevColorIn((GXTevStageID)0, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)0xf, (GXTevColorArg)8);
    GXSetTevAlphaOp((GXTevStageID)0, (GXTevOp)0, (GXTevBias)0, (GXTevScale)0, false, (GXTevRegID)0);
    GXSetTevAlphaIn((GXTevStageID)0, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7, (GXTevAlphaArg)7);
    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, (GXAttrType)1);
    GXSetVtxAttrFmt((GXVtxFmt)0, (GXAttr)9, (GXCompCnt)1, (GXCompType)4, 0);
    GXSetVtxDesc((GXAttr)0xd, (GXAttrType)1);
    GXSetVtxAttrFmt((GXVtxFmt)0, (GXAttr)0xd, (GXCompCnt)1, (GXCompType)4, 0);

    struct Vec2f_swapped {
        float y;
        float x;
    };
    
    Vec2f_swapped pos;
    Vec2f_swapped offs;

    // rect instead maybe?

    CamMng::Instance()->fn_800548AC(&pos.x, &pos.y, &offs.x, &offs.y, 6);

    float width = mWidth / SCALE_FACTOR;
    float height = mHeight / SCALE_FACTOR;

    float minX = pos.x / width - FLOOR(pos.x / width);
    float minY = 1.0f - (pos.y / height - FLOOR(pos.y / height));

    float w = offs.x / width;
    float h = offs.y / height;

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);

    GXPosition3f32(pos.x, pos.y, 0.0f);
    GXTexCoord2f32(minX, minY); // top left?

    GXPosition3f32(pos.x + offs.x, pos.y, 0.0f);
    GXTexCoord2f32(minX + w, minY); // top right?

    GXPosition3f32(pos.x + offs.x, pos.y - offs.y, 0.0f);
    GXTexCoord2f32(minX + w, minY + h); // bottom right?

    GXPosition3f32(pos.x, pos.y - offs.y, 0.0f);
    GXTexCoord2f32(minX, minY + h); // bottom left?
    
    GXEnd();
}
