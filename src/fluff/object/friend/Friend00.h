#ifndef FLUFF_FRIEND00_H
#define FLUFF_FRIEND00_H

#include "object/FlfFriend.h"
#include "object/collision/CollisionEntry.h"

#include <vector>

class Friend00 : public FlfFriend {
private:
    static const char* ResourceName;
public:
    Friend00(gfl::Task* pParentTask, FullSortScene* pScene, const char* pTaskName);

    /* Virtual Methods */
    /* 0x0AC */ virtual void vfAC() override;
    /* 0x0D0 */ virtual void StartMission(PlayerBase*, bool) override;
    /* 0x0DC */ virtual int vfDC() override;
    /* 0x0E8 */ virtual int vfE8() override;
    /* 0x0EC */ virtual int vfEC() override;
    /* 0x14C */ virtual void StartMission() override;
    /* 0x15C */ virtual void vf15C() override;
    /* 0x164 */ virtual void Update() const override;
    /* 0x1BC */ virtual void vf1BC() override;
    /* 0x204 */ virtual void vf204() override;
    /* 0x208 */ virtual void vf208() override;
    /* 0x20C */ virtual void vf20C() override;
    /* 0x210 */ virtual void vf210(int) override;
    /* 0x214 */ virtual void vf214() override;
    /* 0x218 */ virtual int vf218() override;

    /* Class Methods */

    /* Static Methods */

    static const char* GetResourceName() DONT_INLINE_CLASS;
    static Friend00* Build(gfl::Task* pParentTask, FullSortScene* pScene, const char* pTaskName);
    static void AddResourceName();

    /* Class Members */

    /* 0x178 */ int m_178;
    /* 0x17C */ std::vector<placeholder_t> m_17C;
    /* 0x188 */ bool m_188;
    /* 0x18C */ float m_18C;
    /* 0x190 */ float m_190;
    /* 0x194 */ float m_194;
    /* 0x198 */ float m_198;
    /* 0x19C */ float m_19C;
    /* 0x1A0 */ float m_1A0;
    /* 0x1A4 */ int m_1A4;
    /* 0x1A8 */ int m_1A8;
    /* 0x1AC */ CollisionEntry* mCollisionEntry1;
    /* 0x1B0 */ CollisionEntry* mCollisionEntry2;
    /* 0x1B4 */ CollisionEntry* mCollisionEntry3;
};

#endif
