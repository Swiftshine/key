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
private:
    static inline void GetMTXTranslation(nw4r::math::MTX34& mtx, nw4r::math::VEC3& dst) {
        dst.x = mtx[0][3];
        dst.y = mtx[1][3];
        dst.z = mtx[2][3];
    }

    static inline void SetMTXTranslation(nw4r::math::MTX34& mtx, nw4r::math::VEC3& src) {
        mtx[0][3] = src.x;
        mtx[1][3] = src.y;
        mtx[2][3] = src.z;
    }
public:
    static GmkCandleStick* Build(GimmickBuildInfo* buildInfo);
    GmkCandleStick(GimmickBuildInfo* buildInfo) DONT_INLINE_CLASS;
    virtual ~GmkCandleStick();

    void UpdateModelMatrices(nw4r::math::VEC2& vec) DONT_INLINE_CLASS;
    void UpdateGraphics(bool createEffect);

    /* FlfGameObj */
    void SetState(FlfGameObj* setter, const std::string& state);

    

private:
    float mRadius;
    bool mEffectCreated;
    gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry; // @ 0x13C
    gfl::Pointer<FlfMdlDraw> mFlfMdlDraw; // @ 0x140
    gfl::Pointer<MoguraLight> mMoleLight; // @ 0x144
};

#endif
