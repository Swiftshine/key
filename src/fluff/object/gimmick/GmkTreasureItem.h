#ifndef FLUFF_GMKTREASUREITEM_H
#define FLUFF_GMKTREASUREITEM_H

#include "gfl/gflResFileInfo.h"

#include "object/Gimmick.h"
#include "object/collision/IObjHitCB.h"

#include "graphics/FlfMdlDraw.h"
#include "graphics/GmkPartsMdlSet.h"
#include "graphics/NwAnm.h"

#include "util/PercentageWrapper.h"

#include "misc/ScopedPointers.h"

/// @brief A treasure for the player to collect.
/// @note Size: `0x184`
class GmkTreasureItem : public Gimmick, public IObjHitCB {
public:
    static GmkTreasureItem* Build(GimmickBuildInfo* pBuildInfo);

    GmkTreasureItem(GimmickBuildInfo* pBuildInfo, const char* pTaskName);

    /* Virtual Methods */

    /* 0x08 */ virtual ~GmkTreasureItem();

    /* 0x4C */ virtual void SetState(FlfGameObj* pSetter, const std::string& rState) override;
    /* 0xBC */ virtual void Update();

    /* 0xD0 */ virtual bool OnCollision(CollisionInfo* pSolSelf, CollisionInfo* pColOther, const gfl::Vec3& rPosition) override;


    /* Class Methods */
    void CreateEffect();
    void Init() DONT_INLINE_CLASS;
    void fn_803D4E4C();
    void ProcessClothPull();

    /* Class Members */

    /* 0x134 */ StateObject mState;
    /* 0x148 */ gfl::Pointer<FlfMdlDraw> mFlfMdlDraw;
    /* 0x14C */ gfl::Pointer<PercentageWrapper> mPercentageWrapper;
    /* 0x150 */ gfl::Pointer<pvd8_t> m_150;
    /* 0x154 */ int m_154;
    /* 0x158 */ bool mPlayAnimation;
    /* 0x15C */ gfl::Pointer<GmkPartsMdlSet> mGmkPartsMdlSet;
    /* 0x160 */ gfl::Pointer<NwAnm> mNwAnm1;
    /* 0x164 */ gfl::Pointer<NwAnm> mNwAnm2;
    /* 0x168 */ gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry;
    /* 0x16C */ gfl::ResFileObject mResFileObject;
    /* 0x170 */ bool m_170;
    /* 0x171 */ bool mClothPatchPulled;
    /* 0x174 */ FlfGameObj* mClothPatch;
    /* 0x178 */ std::string mClothPatchState;
};

#endif