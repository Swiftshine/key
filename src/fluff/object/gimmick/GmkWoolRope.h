#ifndef FLUFF_GMKWOOLROPE_H
#define FLUFF_GMKWOOLROPE_H

#include "gfl/gflPointer.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/FlfMdlDraw.h"
#include "mapdata/Mapdata.h"
#include "object/wool/WoolLinkObj.h"
#include "object/wool/WoolLinkObjBase.h"
#include "object/Gimmick.h"
#include "object/gimmick/GmkWoolHook.h"

class WoolLinkObjBase;

// size: 0x160
class GmkWoolRope : public Gimmick {
public:
    enum WoolTextureType {
        eWoolTextureType_Brown           = 0,
        eWoolTextureType_Pink            = 1,
        eWoolTextureType_White           = 2,
        eWoolTextureType_Red             = 3,
        eWoolTextureType_Orange          = 4,
        eWoolTextureType_Yellow          = 5,
        eWoolTextureType_LightBlue       = 6,
        eWoolTextureType_RedWhiteBlue    = 7,
        eWoolTextureType_LightGreen      = 8,
        eWoolTextureType_Black           = 9,
        eWoolTextureType_Tan             = 10,
        eWoolTextureType_Cyan            = 11,
        eWoolTextureType_Lavender        = 12,
        eWoolTextureType_Silver          = 13,
        eWoolTextureType_GreenCoil       = 50,
        eWoolTextureType_PinkZipper      = 51,
    };

    enum HookType {
        Standard        = 0,
        Flower          = 1,
        WhiteBow        = 2,
        RedWhiteBlueBow = 3,
        RedButton       = 4,
        BrownSquare     = 8,
        Gizmo           = 49,
    };

    static GimmickBuildInfo GBuildInfo;
    static WoolBaseTask::WoolBuildInfo WBuildInfo;

public:
    GmkWoolRope(
        GmkWoolHook* pFirstHook,
        GmkWoolHook* pSecondHook,
        s32 woolColor,
        s32 hookType,
        Mapdata::MapdataGimmick* pMapdataGimmick,
        const char* pTaskName
    );

    /* Virtual Methods */

    /* GmkWoolRope */

    /* 0x08 */ virtual ~GmkWoolRope();
    /* 0xC4 */ virtual void LoadTextures(WoolBaseTask::WoolBuildInfo* wBuildInfo, const char* path);
    /* 0xC8 */ virtual void vfC8() DONT_INLINE_CLASS;
    /* 0xCC */ virtual void vfCC() DONT_INLINE_CLASS;
    /* 0xD0 */ virtual void SetHooks(GmkWoolHook* first, GmkWoolHook* second) DONT_INLINE_CLASS;
    /* 0xD4 */ virtual void vfD4() DONT_INLINE_CLASS;
    /* 0xD8 */ virtual void vfD8() DONT_INLINE_CLASS;

    /* Overrides */

    /* FlfGameObj */

    /* 0x38 */ virtual ScreenPosition GetScreenPosition() override;

    /* Gimmick */

    /* 0xBC */ virtual void Update() override;

    /* Class Members */

    /* 0x130 */ s32 m_130;
    /* 0x134 */ s32 m_134;
    /* 0x138 */ s32 m_138;
    /* 0x13C */ s32 m_13C;
    /* 0x140 */ s32 m_140;
    /* 0x144 */ WoolLinkObjBase* mWoolLink;
    /* 0x148 */ s32 mWoolTextureType;
    /* 0x14C */ s32 mWoolHookType;
    /* 0x150 */ GmkWoolHook* mFirstWoolHook;
    /* 0x154 */ GmkWoolHook* mSecondWoolHook;
    /// The associated "WoolBridge" gimmick. The position of the gimmick in mapdata
    /// MUST be the same as the position of the first path node in order to bind.
    /* 0x158 */ Mapdata::MapdataGimmick* mMapdataGimmick;
    /* 0x15C */ gfl::ResFileObject mResFileObject;
};



// ASSERT_SIZE(GmkWoolRope, 0x160);

#endif
