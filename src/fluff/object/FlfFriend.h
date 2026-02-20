#ifndef FLUFF_FLUFFFRIEND_H
#define FLUFF_FLUFFFRIEND_H

#include "object/FlfGameObj.h"
#include "object/collision/IObjHitCB.h"
#include <nw4r/g3d/g3d_calcworld.h>

#include "gfl/gflTask.h"
#include "graphics/FlfMdlDraw.h"
#include "graphics/FullSortScene.h"
#include "graphics/MoguraLight.h"
#include "graphics/effect/FriendEffect.h"
#include "mapdata/Mapdata.h"
#include "misc/ScopedPointers.h"
#include "util/ScreenPosition.h"
#include "util/StateObject.h"
#include <tree>

class PlayerBase;
class GmkBackDoor;
class GmkBackDoorCancel;

/// @brief Base class for friend objects.
/// @note Size: `0x178`
class FlfFriend : public FlfGameObj, public IObjHitCB, public nw4r::g3d::ICalcWorldCallback {
public:
    FlfFriend(gfl::Task* pParentTask, FullSortScene* pScene, uint friendID, const char* pTaskName);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfFriend();

    /* New Virtuals */

    /* 0x08C */ virtual bool IsPlayerSavedPositionInFront() const;
	/* 0x090 */ virtual bool IsPositionInFront(const gfl::Vec2& rPos) const;
	/* 0x094 */ virtual bool vf94(const gfl::Vec2& rPos) const; // related to checking position against some camera bounds
	/* 0x098 */ virtual bool vf98(float, float, const gfl::Vec2&) const;
	/* 0x09C */ virtual bool IsInRange(const gfl::Vec3& rTarget, float* pDistance) const;
	/* 0x0A0 */ virtual void vfA0();
	/* 0x0A4 */ virtual void vfA4();
	/* 0x0A8 */ virtual void vfA8();
	/* 0x0AC */ virtual void vfAC();
	/* 0x0B0 */ virtual void ResetScreen(const ScreenPosition& rPos);
	/* 0x0B4 */ virtual void ResetCollision();
	/* 0x0B8 */ virtual void ResetRoomLocator();
	/* 0x0BC */ virtual void vfBC(void* pArg1, bool arg2);
	/* 0x0C0 */ virtual void vfC0(void* pArg1);
	/* 0x0C4 */ virtual void vfC4();
	/* 0x0C8 */ virtual void vfC8();
	/* 0x0CC */ virtual void vfCC();
	/* 0x0D0 */ virtual void StartMission(PlayerBase* pPlayer, bool) = 0;
	/* 0x0D4 */ virtual void vfD4(float, const gfl::Vec3&);
	/* 0x0D8 */ virtual bool vfD8() const;
	/* 0x0DC */ DECL_WEAK virtual int vfDC();
	/* 0x0E0 */ virtual bool vfE0() const;
	/* 0x0E4 */ virtual bool vfE4() const;
	/* 0x0E8 */ DECL_WEAK virtual int vfE8();
	/* 0x0EC */ DECL_WEAK virtual bool vfEC();
	/* 0x0F0 */ virtual void vfF0(FlfGameObj* pObj);
	/* 0x0F4 */ virtual PlayerBase* GetPlayer() const;
	/* 0x0F8 */ virtual void SetPlayer(PlayerBase* pPlayer);
	/* 0x0FC */ virtual gfl::Vec3 vfFC();
	/* 0x100 */ virtual void vf100();
	/* 0x104 */ virtual void SetScene(FullSortScene* pScene);
	/* 0x108 */ virtual void SetVisibility(bool vis);
	/* 0x10C */ virtual bool IsVisible() const;
	/* 0x110 */ virtual void SetNURBSAnimationInfo(int id, bool isReset);
	/* 0x114 */ virtual uint GetCurrentNURBSAnimationID() const;
	/* 0x118 */ virtual void PlayNURBSAnimation(int, bool);
	/* 0x11C */ virtual void SetCurrentNURBSAnimationFrame(float frame);
	/* 0x120 */ DECL_WEAK virtual uint GetCurrentAnimationID() const;
	/* 0x124 */ virtual void vf124();
	/* 0x128 */ virtual bool vf128() const;
	/* 0x12C */ virtual void vf12C(int);
	/* 0x130 */ virtual bool vf130() const;
	/* 0x134 */ virtual void vf134();
	/* 0x138 */ virtual bool vf138() const;
	/* 0x13C */ virtual void vf13C();
	/* 0x140 */ virtual bool vf140() const;
	/* 0x144 */ virtual void SetPositionToPlayerSavedPosition();
	/* 0x148 */ virtual void vf148();
	/* 0x14C */ virtual void StartMission();
	/* 0x150 */ virtual void vf150();
	/* 0x154 */ virtual void vf154();
	/* 0x158 */ virtual void vf158();
	/* 0x15C */ virtual void vf15C();
	/* 0x160 */ virtual void vf160();
	/* 0x164 */ virtual void Update() const;
	/* 0x168 */ virtual void vf168();
	/* 0x16C */ virtual void vf16C();
	/* 0x170 */ virtual void GetTransform(gfl::Mtx34& rMtx, gfl::Vec3& rPos, gfl::Vec3& rRot, gfl::Vec3& rScale) const;
	/* 0x174 */ virtual void vf174();
	/* 0x178 */ virtual void vf178();
	/* 0x17C */ virtual void vf17C();
	/* 0x180 */ virtual void vf180();
	/* 0x184 */ virtual void vf184();
	/* 0x188 */ virtual void vf188();
	/* 0x18C */ virtual void vf18C();
	/* 0x190 */ virtual void vf190();
	/* 0x194 */ virtual void vf194();
	/* 0x198 */ virtual void vf198();
	/* 0x19C */ virtual void vf19C();
	/* 0x1A0 */ virtual void vf1A0();
	/* 0x1A4 */ virtual void vf1A4();
	/* 0x1A8 */ virtual void vf1A8();
	/* 0x1AC */ virtual void vf1AC();
	/* 0x1B0 */ virtual void vf1B0();
	/* 0x1B4 */ virtual void vf1B4();
	/* 0x1B8 */ virtual void vf1B8();
	/* 0x1BC */ virtual void vf1BC();
	/* 0x1C0 */ virtual void vf1C0();
	/* 0x1C4 */ virtual void vf1C4();
	/* 0x1C8 */ virtual void vf1C8();
	/* 0x1CC */ virtual void vf1CC();
	/* 0x1D0 */ virtual void vf1D0();
	/* 0x1D4 */ virtual void vf1D4();
	/* 0x1D8 */ virtual void vf1D8();
	/* 0x1DC */ virtual void vf1DC();
	/* 0x1E0 */ virtual void vf1E0();
	/* 0x1E4 */ virtual void vf1E4();
	/* 0x1E8 */ virtual void vf1E8();
	/* 0x1EC */ virtual void vf1EC();
	/* 0x1F0 */ virtual void vf1F0();
	/* 0x1F4 */ virtual void vf1F4();
	/* 0x1F8 */ virtual void vf1F8();
	/* 0x1FC */ virtual void vf1FC();
	/* 0x200 */ virtual void vf200();
	/* 0x204 */ virtual void vf204();
	/* 0x208 */ virtual void vf208();
	/* 0x20C */ virtual void vf20C(bool);
	/* 0x210 */ virtual void vf210(int);
	/* 0x214 */ virtual void vf214();
	/* 0x218 */ DECL_WEAK virtual bool vf218();
	// Switch direction to face the target.
	/* 0x21C */ virtual void LookAt(const ScreenPosition& rPos);
	/* 0x220 */ DECL_WEAK virtual void vf220(/* unk args (it's not void) */);
	/* 0x224 */ virtual void vf224(float arg1);
	/* 0x228 */ virtual float vf228() const;
	/* 0x22C */ virtual void vf22C(float arg1);
	/* 0x230 */ virtual float vf230() const;
	/* 0x234 */ virtual void vf234(float arg1);
	/* 0x238 */ virtual float vf238() const;
	/* 0x23C */ virtual void vf23C(float arg1);
	/* 0x240 */ virtual void vf240();
	/* 0x244 */ virtual bool IsAnimationDone() const;
	/* 0x248 */ virtual void vf248();
	/* 0x24C */ virtual void SwitchDirection();

    /* Overrides */

    /* 0x70 */ virtual bool OnCollision(CollisionInfo* pColSelf, CollisionInfo* pColOther) override;

    /* 0x80 */ DECL_WEAK virtual void ExecCallbackA(nw4r::g3d::ChrAnmResult* pResult, nw4r::g3d::ResMdl mdl, nw4r::g3d::FuncObjCalcWorld* pFuncObj) override;
    /* 0x84 */ DECL_WEAK virtual void ExecCallbackB(nw4r::g3d::WorldMtxManip* pManip, nw4r::g3d::ResMdl mdl, nw4r::g3d::FuncObjCalcWorld* pFuncObj) override;
    /* 0x88 */ virtual void ExecCallbackC(nw4r::math::MTX34* pMtxArray, nw4r::g3d::ResMdl mdl, nw4r::g3d::FuncObjCalcWorld* pFuncObj) override;


    /* Class Methods */

	void SetTaskFlags(bool set, bool arg2, uint flag);
    void ProcessCollision() DONT_INLINE_CLASS;
    void SetCallbackTiming();
	bool fn_8033BD68(const gfl::Vec3& rV1, const gfl::Vec3& rV2, const gfl::Vec3& rV3) const;
	bool fn_8033BE24(const gfl::Vec3& rV1, const gfl::Vec3& rV2) const;
	bool fn_8033BE64() DONT_INLINE_CLASS;
    void fn_8033BF8C(int);
    void fn_8033BFC8(int targetState, int currentState);
	bool fn_8033C004(float arg1, const gfl::Vec2& rVec) const DONT_INLINE_CLASS;
	void SetTransform(gfl::Mtx34& rMtx);
	void fn_8033C488();
	void fn_8033C580(uint);
	int fn_8033C5B4();
	void SetScreenPosition(int* pDirection) DONT_INLINE_CLASS;
	PlayerBase* GetClosestPlayer() const;
	bool fn_8033E25C() const;
	void TryStartMission(GmkBackDoor* pDoor, bool arg2);
	void fn_8033E3DC();
	void TryCancelMission(GmkBackDoorCancel* pDoor, const gfl::Vec3& rPos);
	void fn_8033E570();
	bool fn_8033E648();
	bool fn_8033E84C() const;
	bool fn_8033E870() const;
	bool fn_8033E8A8() const DONT_INLINE_CLASS;
	gfl::Vec3 fn_8033E940() const;

    /* Static Methods */

    static float Square(float val);
    static float fn_8033B710();
	static int fn_8033BEFC(std::tree<placeholder_t>& rTree, int*);

	/* Inline Helper Methods */
	inline const ScreenPosition& GetScreenPosition() const {
	    return mScreenPosition;
	}
    /* Class Members */

    /* 0x088 */ gfl::Task mTask;
    /* 0x0A0 */ FullSortScene* mScene;
    /* 0x0A4 */ FlfMdlDraw* mFlfMdlDraw;
    /* 0x0A8 */ uint mNextAnimationID;
    /* 0x0AC */ bool mIsAnimationReset;
    /* 0x0B0 */ uint mCurrentAnimationID;
    /* 0x0B4 */ int m_B4;
    /* 0x0B8 */ int m_B8;
    /* 0x0BC */ gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry;
    /* 0x0C0 */ int m_C0;
    /* 0x0C4 */ StateObject mState;
    /* 0x0D8 */ std::tree<placeholder_t> m_D8;
    /* 0x0E4 */ gfl::Vec3 m_E4;
    /* 0x0F0 */ float m_F0;
    /* 0x0F4 */ gfl::Vec3 m_F4;
    /* 0x100 */ float m_100;
    /* 0x104 */ float m_104;
    /* 0x108 */ float m_108;
    /* 0x10C */ float m_10C;
    /* 0x110 */ float m_110;
    /* 0x114 */ float m_114;
    /* 0x118 */ ScreenPosition mScreenPosition;
    /* 0x124 */ float m_124;
    /* 0x128 */ float m_128;
    /* 0x12C */ float m_12C;
    /* 0x130 */ float m_130;
    /* 0x134 */ int m_134;
    /* 0x138 */ bool mUpdateFrame;
    /* 0x139 */ bool m_139;
    /* 0x13C */ Mapdata::MapdataGimmick* mMapdataGimmick;
    /* 0x140 */ int m_140;
    /* 0x144 */ uint m_144;
    /* 0x148 */ bool m_148;
    /* 0x149 */ bool m_149;
    /* 0x14C */ FlfHandle mBackDoorHandle;
    /* 0x154 */ bool mMissionState;
    /* 0x155 */ bool mMissionStarted;
    /* 0x158 */ MoguraLight* mMoleLight;
    /* 0x15C */ FlfHandle mPlayerHandle;
    /* 0x164 */ gfl::Vec3 m_164;
    /* 0x170 */ FriendEffect* mEffect;
    /* 0x174 */ uint mFriendID;
};

#endif
