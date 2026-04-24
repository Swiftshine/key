#ifndef FLUFF_FRIEND00_H
#define FLUFF_FRIEND00_H

#include "object/FlfFriend.h"
#include "object/collision/CollisionEntry.h"
#include "types.h"

#include <vector>

class GmkBead;

class GatherBeadFriend00 {
public:
    virtual ~GatherBeadFriend00();
};

class Friend00 : public FlfFriend {
private:
    static const char* ResourceName;
public:
    Friend00(gfl::Task* pParentTask, FullSortScene* pScene, const char* pTaskName);

    /* Virtual Methods */
    /* 0x008 */ virtual ~Friend00();
    /* 0x0AC */ virtual void vfAC() override;
    /* 0x0D0 */ virtual void StartMission(PlayerBase*, bool) override;
    /* 0x0DC */ virtual bool vfDC() const override;
    /* 0x0E8 */ virtual bool vfE8() const override;
    /* 0x0EC */ virtual bool vfEC() const override;
    /* 0x14C */ virtual void StartMission() override;
    /* 0x15C */ virtual void vf15C(/* args unk */) override;
    /* 0x164 */ virtual void Update() const override;
    /* 0x1BC */ virtual void vf1BC() override;
    /* 0x204 */ virtual void vf204() override;
    /* 0x208 */ virtual void vf208() override;
    /* 0x20C */ virtual void vf20C(bool isReset) override;
    /* 0x210 */ virtual void vf210(bool isReset) override;
    /* 0x214 */ virtual void vf214(bool isReset) override;
    /* 0x218 */ virtual bool vf218() override;

    /* Class Methods */

    void InitCollision();
    void IncrementBeadCount(uint amt);
    void fn_80342888() DONT_INLINE_CLASS;
    void fn_80342DE4(PlayerBase* pPlayer, bool isReset);
    void fn_803431E4();
    /// @note The result of this function is never used.
    int GetBeadGimmickID(GmkBead* pBead) const;
    void fn_80343534();
    void fn_803436C8();

    /* Static Methods */

    static const char* GetResourceName() DONT_INLINE_CLASS;
    static Friend00* Build(gfl::Task* pParentTask, FullSortScene* pScene, const char* pTaskName);
    static void AddResourceName();

    /* Class Members */

    /* 0x178 */ int mBeadCount;
    /* 0x17C */ std::vector<GatherBeadFriend00*> mGathers;
    /* 0x188 */ bool m_188;
    /* 0x18C */ gfl::Vec3 m_18C;
    /* 0x198 */ gfl::Vec3 m_198;
    /* 0x1A4 */ int mBeadsCollected[2];
    /* 0x1AC */ gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry1;
    /* 0x1B0 */ gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry2;
    /* 0x1B4 */ gfl::ReleasedPointer<CollisionEntry, CollisionEntry::Remove> mCollisionEntry3;
};

#endif
