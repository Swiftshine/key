#ifndef FLUFF_BGIMAGE2_H
#define FLUFF_BGIMAGE2_H

#include "gfl/gflCustomRenderObj.h"


#include "gfl/gflParam.h"

class BGSTFile;

// size: 0x130
class BgImage2 : public gfl::CustomRenderObj {
public:
    /* Constructor */

    BgImage2(BGSTFile* bgst, uint sortSceneID);

    /* Virtual Methods */

    /* 0x08 */ virtual ~BgImage2();

    /* Class Methods */

    void fn_80168DA0(nw4r::math::VEC3& rArg1);
    void fn_80168E3C(float& rXScale, nw4r::math::VEC2& rArg2);
    void fn_80168EE8(float& rXScale, nw4r::math::VEC2& rArg2);
    void fn_80168F94(nw4r::math::VEC2& rArg1, nw4r::math::VEC2& rArg2);
    void fn_80169054();
    void fn_80169150();

    /* Class Members */

    /* 0x104 */ nw4r::math::VEC3 mMatrixTranslation;
    /* 0x110 */ uint mSceneID;
    /* 0x114 */ BGSTFile* mBGSTFile;
    /* 0x118 */ nw4r::math::VEC2 mImagePosition;
    /* 0x120 */ void* mImageData;
    /* 0x124 */ gfl::ParamS32* mShadowOffsetParam;
    /* 0x128 */ gfl::ParamS32* mShadowColorParam;
    /* 0x12C */ gfl::ParamBool* mShadowStateParam;
};

#endif
