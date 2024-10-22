#ifndef FLUFF_BGIMAGE2_H
#define FLUFF_BGIMAGE2_H

#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflVec3.h"
#include "gfl/gflVec2.h"
#include "gfl/gflParam.h"

class BGSTFile;

// size: 0x130
class BgImage2 : public gfl::CustomRenderObj {
public:
    BgImage2(BGSTFile* bgst, uint sortSceneID);
    ~BgImage2();

    void fn_80168DA0(nw4r::math::VEC3& arg1);
    void fn_80168E3C(float& xScale, nw4r::math::VEC2& arg2);
    void fn_80168EE8(float& xScale, nw4r::math::VEC2& arg2);
    void fn_80168F94(nw4r::math::VEC2& arg1, nw4r::math::VEC2& arg2);
    void fn_80169054();
    void fn_80169150();
private:
    nw4r::math::VEC3 m_104;
    uint mSceneID;
    BGSTFile* mBGSTFile;
    nw4r::math::VEC2 mImagePosition;
    void* m_120;
    gfl::ParamS32* mShadowOffsetParam;
    gfl::ParamS32* mShadowColorParam;
    gfl::ParamBool* mShadowStateParam;
};

#endif
