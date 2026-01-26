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
#include "misc/ScopedPointers.h"
#include "util/StateObject.h"
#include <tree>

class PlayerBase;

/// @brief Base class for friend objects.
/// @note Size: `0x178`
class FlfFriend : public FlfGameObj, public IObjHitCB, public nw4r::g3d::ICalcWorldCallback {
public:
    FlfFriend(gfl::Task* pParentTask, FullSortScene* pScene, int friendID, const char* pTaskName);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfFriend();

    /* New Virtuals */

    /* 0x08C */ virtual void vf8C();
	/* 0x090 */ virtual void vf90();
	/* 0x094 */ virtual void vf94();
	/* 0x098 */ virtual void vf98();
	/* 0x09C */ virtual void vf9C();
	/* 0x0A0 */ virtual void vfA0();
	/* 0x0A4 */ virtual void vfA4();
	/* 0x0A8 */ virtual void vfA8();
	/* 0x0AC */ virtual void vfAC();
	/* 0x0B0 */ virtual void vfB0();
	/* 0x0B4 */ virtual void vfB4();
	/* 0x0B8 */ virtual void vfB8();
	/* 0x0BC */ virtual void vfBC();
	/* 0x0C0 */ virtual void vfC0();
	/* 0x0C4 */ virtual void vfC4();
	/* 0x0C8 */ virtual void vfC8();
	/* 0x0CC */ virtual void vfCC();
	/* 0x0D0 */ virtual void vfD0(PlayerBase* pPlayer, int) = 0;
	/* 0x0D4 */ virtual void vfD4();
	/* 0x0D8 */ virtual void vfD8();
	/* 0x0DC */ virtual void vfDC();
	/* 0x0E0 */ virtual void vfE0();
	/* 0x0E4 */ virtual void vfE4();
	/* 0x0E8 */ virtual void vfE8();
	/* 0x0EC */ virtual void vfEC();
	/* 0x0F0 */ virtual void vfF0(FlfGameObj* pObj);
	/* 0x0F4 */ virtual void vfF4();
	/* 0x0F8 */ virtual void vfF8();
	/* 0x0FC */ virtual void vfFC();
	/* 0x100 */ virtual void vf100();
	/* 0x104 */ virtual void vf104();
	/* 0x108 */ virtual void vf108();
	/* 0x10C */ virtual void vf10C();
	/* 0x110 */ virtual void vf110();
	/* 0x114 */ virtual void vf114();
	/* 0x118 */ virtual void vf118(int, int);
	/* 0x11C */ virtual void vf11C();
	/* 0x120 */ virtual void vf120();
	/* 0x124 */ virtual void vf124();
	/* 0x128 */ virtual void vf128();
	/* 0x12C */ virtual void vf12C();
	/* 0x130 */ virtual void vf130();
	/* 0x134 */ virtual void vf134();
	/* 0x138 */ virtual void vf138();
	/* 0x13C */ virtual void vf13C();
	/* 0x140 */ virtual void vf140();
	/* 0x144 */ virtual void vf144();
	/* 0x148 */ virtual void vf148();
	/* 0x14C */ virtual void vf14C();
	/* 0x150 */ virtual void vf150();
	/* 0x154 */ virtual void vf154();
	/* 0x158 */ virtual void vf158();
	/* 0x15C */ virtual void vf15C();
	/* 0x160 */ virtual void vf160();
	/* 0x164 */ virtual void Update() const;
	/* 0x168 */ virtual void vf168();
	/* 0x16C */ virtual void vf16C();
	/* 0x170 */ virtual void vf170();
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
	/* 0x20C */ virtual void vf20C();
	/* 0x210 */ virtual void vf210();
	/* 0x214 */ virtual void vf214();
	/* 0x218 */ virtual void vf218();
	/* 0x21C */ virtual void vf21C();
	/* 0x220 */ virtual void vf220();
	/* 0x224 */ virtual void vf224();
	/* 0x228 */ virtual void vf228();
	/* 0x22C */ virtual void vf22C();
	/* 0x230 */ virtual void vf230();
	/* 0x234 */ virtual void vf234();
	/* 0x238 */ virtual void vf238();
	/* 0x23C */ virtual void vf23C();
	/* 0x240 */ virtual void vf240();
	/* 0x244 */ virtual void vf244();
	/* 0x248 */ virtual void vf248();
	/* 0x24C */ virtual void vf24C();

    /* Overrides */

    /* 0x70 */ virtual bool OnCollision(CollisionInfo* pColSelf, CollisionInfo* pColOther) override;

    /* 0x80 */ DECL_WEAK virtual void ExecCallbackA(nw4r::g3d::ChrAnmResult* pResult, nw4r::g3d::ResMdl mdl, nw4r::g3d::FuncObjCalcWorld* pFuncObj) override;
    /* 0x84 */ DECL_WEAK virtual void ExecCallbackB(nw4r::g3d::WorldMtxManip* pManip, nw4r::g3d::ResMdl mdl, nw4r::g3d::FuncObjCalcWorld* pFuncObj) override;
    /* 0x88 */ DECL_WEAK virtual void ExecCallbackC(nw4r::math::MTX34* pMtxArray, nw4r::g3d::ResMdl mdl, nw4r::g3d::FuncObjCalcWorld* pFuncObj) override;
    

    /* Class Methods */

    void SetCallbackTiming();

    void fn_8033BF8C(int);
    void fn_8033BFC8(int targetState, int currentState);
    void ProcessCollision();

    /* Static Methods */

    static float Square(float val);
    static float fn_8033B710();

    /* Class Members */
    
    /* 0x088 */ gfl::Task mTask;
    /* 0x0A0 */ FullSortScene* mScene;
    /* 0x0A4 */ FlfMdlDraw* mFlfMdlDraw;
    /* 0x0A8 */ int m_A8;
    /* 0x0AC */ bool m_AC;
    /* 0x0B0 */ int m_B0;
    /* 0x0B4 */ int m_B4;
    /* 0x0B8 */ int m_B8;
    /* 0x0BC */ gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry;
    /* 0x0C0 */ int m_C0;
    /* 0x0C4 */ StateObject mState;
    /* 0x0D8 */ std::tree<placeholder_t> m_D8;
    /* 0x0E4 */ gfl::Vec3 m_E4;
    /* 0x0F0 */ float m_F0;
    /* 0x0F4 */ float m_F4;
    /* 0x0F8 */ float m_F8;
    /* 0x0FC */ float m_FC;
    /* 0x100 */ float m_100;
    /* 0x104 */ float m_104;
    /* 0x108 */ float m_108;
    /* 0x10C */ float m_10C;
    /* 0x110 */ float m_110;
    /* 0x114 */ float m_114;
    /* 0x118 */ float m_118;
    /* 0x11C */ float m_11C;
    /* 0x120 */ float m_120;
    /* 0x124 */ float m_124;
    /* 0x128 */ float m_128;
    /* 0x12C */ float m_12C;
    /* 0x130 */ float m_130;
    /* 0x134 */ int m_134;
    /* 0x138 */ bool m_138;
    /* 0x139 */ bool m_139;
    /* 0x13C */ int m_13C;
    /* 0x140 */ int m_140;
    /* 0x144 */ int m_144;
    /* 0x148 */ bool m_148;
    /* 0x149 */ bool m_149;
    /* 0x14C */ int m_14C;
    /* 0x150 */ int m_150;
    /* 0x154 */ bool m_154;
    /* 0x155 */ bool m_155;
    /* 0x158 */ MoguraLight* mMoleLight;
    /* 0x15C */ int m_15C;
    /* 0x160 */ int m_160;
    /* 0x164 */ gfl::Vec3 m_164;
    /* 0x170 */ FriendEffect* mEffect;
    /* 0x174 */ int mFriendID;
};

#endif
