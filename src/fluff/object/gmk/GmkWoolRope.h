#ifndef FLUFF_GMKWOOLROPE_H
#define FLUFF_GMKWOOLROPE_H

#include "object/wool/WoolLinkObj.h"
#include "gfl/gflScopedPointer.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/FlfMdlDraw.h"
#include "object/Gimmick.h"
#include "object/gmk/GmkWoolHook.h"

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
    virtual ~GmkWoolRope();

    /* FlfGameObj */
    virtual gfl::Vec3 GetScreenPos() override;

    /* Gimmick */
    virtual void Update() override;

    /* GmkWoolRope */
    virtual void LoadTextures(WoolBaseTask::WoolBuildInfo* wBuildInfo, const char* path);
    virtual void vfC8() DONT_INLINE_CLASS;
    virtual void vfCC() DONT_INLINE_CLASS;
    virtual void SetHooks(GmkWoolHook* first, GmkWoolHook* second) DONT_INLINE_CLASS;
    virtual void vfD4() DONT_INLINE_CLASS;
    virtual void vfD8() DONT_INLINE_CLASS;
private:
    uint m_130;
    uint m_134;
    uint m_138;
    uint m_13C;
    uint m_140;

    // mWoolLink is actually a `WoolLinkObjBase`, not a `WoolLinkObj`.
    // `WoolLinkObj` does *not* inherit from `WoolLinkObjBase`, however
    WoolLinkObj* mWoolLink;

    int mWoolColorIndex;
    uint m_14C;
    GmkWoolHook* mFirstWoolHook;
    GmkWoolHook* mSecondWoolHook;
    void* m_158;
    gfl::ResFileInfoPointer mResFileInfo;
};

// ASSERT_SIZE(GmkWoolRope, 0x160);

#endif
