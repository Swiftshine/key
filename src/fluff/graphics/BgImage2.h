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

    void fn_80168DA0(gfl::Vec3& arg1);
    void fn_80168E3C(float& xScale, gfl::Vec2& arg2);
    void fn_80168EE8(float& xScale, gfl::Vec2& arg2);
    void fn_80168F94(gfl::Vec2& arg1, gfl::Vec2& arg2);
    void fn_80169054();
    void fn_80169150();
private:
    gfl::Vec3 m_104;
    uint mSceneID;
    BGSTFile* mBGSTFile;
    gfl::Vec2 mImagePosition;
    void* m_120;
    gfl::ParamS32* mShadowOffsetParam;
    gfl::ParamS32* mShadowColorParam;
    gfl::ParamBool* mShadowStateParam;
};

#endif
