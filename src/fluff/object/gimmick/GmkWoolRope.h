#ifndef FLUFF_GMKWOOLROPE_H
#define FLUFF_GMKWOOLROPE_H

#include "object/wool/WoolLinkObj.h"
#include "object/wool/WoolLinkObjBase.h"
#include "gfl/gflPointer.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/FlfMdlDraw.h"
#include "object/Gimmick.h"
#include "object/gimmick/GmkWoolHook.h"

class WoolLinkObjBase;

// size: 0x160
class GmkWoolRope : public Gimmick {
public:
    ENUM_CLASS(Color,
        Brown = 0,
        Pink = 1,
        White = 2,
        Red = 3,
        Orange = 4,
        Yellow = 5,
        LightBlue = 6,
        RedWhiteBlue = 7,
        LightGreen = 8,
        Black = 9,
        Tan = 10,
        Cyan = 11,
        Lavender = 12,
        Silver = 13,

        GreenCoil = 50,
        PinkZipper = 51,
    );

    static GimmickBuildInfo GBuildInfo;
    static WoolBaseTask::WoolBuildInfo WBuildInfo;

public:
    GmkWoolRope(GmkWoolHook* firstHook, GmkWoolHook* secondHook, int woolColorIndex, uint arg4, void* arg5, const char* taskName);

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

    /* 0x130 */ int m_130;
    /* 0x134 */ int m_134;
    /* 0x138 */ int m_138;
    /* 0x13C */ int m_13C;
    /* 0x140 */ int m_140;
    /* 0x144 */ WoolLinkObjBase* mWoolLink;
    /* 0x148 */ int mWoolColor;
    /* 0x14C */ uint m_14C;
    /* 0x150 */ GmkWoolHook* mFirstWoolHook;
    /* 0x154 */ GmkWoolHook* mSecondWoolHook;
    /* 0x158 */ void* m_158;
    /* 0x15C */ gfl::ResFileObject mResFileObject;
};

// ASSERT_SIZE(GmkWoolRope, 0x160);

#endif
