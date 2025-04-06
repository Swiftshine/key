#ifndef FLUFF_ENEMYBASE_H
#define FLUFF_ENEMYBASE_H

#include "types.h"
#include "object/FlfGameObj.h"
#include "demo/EventDemoAttachment.h"
#include "object/collision/IObjHitCB.h"
#include "object/MoveTarget.h"
#include "gfl/gflTask.h"

class EnemyBase : public FlfGameObj, public IObjHitCB, public demo::EventDemoAttachment {
public:
    EnemyBase(gfl::Task* parentTask, uint arg2, uint arg3, const char* arg4);
    virtual ~EnemyBase();

    /* FlfGameObj */
    virtual void SetPosition(nw4r::math::VEC3& pos) override;
    virtual void vf10_FlfGameObj(bool arg1) override;
    virtual nw4r::math::VEC3 GetPosition() override;
    virtual void SetSecondaryPosition(nw4r::math::VEC3& pos) override;
    virtual void vf28_FlfGameObj() override;
    virtual void vf2C_FlfGameObj(nw4r::math::VEC3& arg1, nw4r::math::VEC3& arg2, nw4r::math::VEC3& arg3) override;
    virtual bool ShouldCull(CameraManager* camMgr) override;
    virtual int vf3C_FlfGameObj() override;
    virtual void SetState(FlfGameObj* setter, std::string& state) override;
    virtual void vf64_FlfGameObj(bool) override;

    /* IObjHitCB */
    virtual int vf8_IObjHitCB() override;

    /* demo::EventDemoAttachment */
    virtual void vfC_EventDemoAttachment() override;
    virtual void vf10_EventDemoAttachment() override;
    virtual void vf14_EventDemoAttachment() override;
    virtual void vf18_EventDemoAttachment() override;
    virtual void vf1C_EventDemoAttachment() override;

    /* EnemyBase */
    virtual void vf94();
    virtual void vf98();
    virtual void vf9C();
    virtual void vfA0();

    // ...
    virtual void vf5A4();
protected:
    int m_90;
    int m_94;
    int m_98;
    int m_9C;
    int m_A0;
    int m_A4;
    int m_A8;
    int m_AC;
    int m_B0;
    nw4r::math::VEC3 m_B4;
    int m_C0;
    int m_C4;
    int m_C8;
    int m_CC;
    int m_D0;
    int m_D4;
    int m_D8;
    int m_DC;
    int m_E0;
    int m_E4;
    int m_E8;
    int m_EC;
    MoveTarget mMoveTargets[2]; // @ 0xF0
    int m_180;
    int m_184;
    int m_18C;
    int m_190;
    nw4r::math::MTX44 m_194;
    nw4r::math::VEC2 m_1D4;
    nw4r::math::VEC2 m_1DC;
    STRUCT_FILL(0x1774 - 464);
};

// ASSERT_SIZE(EnemyBase, 0x1774);

#endif
