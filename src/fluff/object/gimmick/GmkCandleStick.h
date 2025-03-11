#ifndef FLUFF_GMKCANDLESTICK_H
#define FLUFF_GMKCANDLESTICK_H

#include "object/Gimmick.h"
#include "object/collision/CollisionEntry.h"
#include "object/collision/IObjHitCB.h"
#include "graphics/MoguraLight.h"
#include "graphics/FlfMdlDraw.h"
#include "misc/ScopedPointers.h"

// size: 0x148
class GmkCandleStick : public Gimmick, public IObjHitCB {
public:
    static GmkCandleStick* Build(GimmickBuildInfo* buildInfo);
    GmkCandleStick(GimmickBuildInfo* buildInfo) DONT_INLINE_CLASS;
    virtual ~GmkCandleStick();

    void UpdateModelMatrices(nw4r::math::VEC2& vec) DONT_INLINE_CLASS;
    void UpdateGraphics(bool createEffect);

    /* FlfGameObj */
    void SetState(FlfGameObj* setter, std::string& state);

private:
    gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry; // @ 0x13C
    gfl::Pointer<FlfMdlDraw> mFlfMdlDraw; // @ 0x140
    gfl::Pointer<MoguraLight> mMoleLight; // @ 0x144
};

#endif
