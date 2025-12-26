#ifndef FLUFF_ENEMYBASE_H
#define FLUFF_ENEMYBASE_H

#include "types.h"
#include "object/FlfGameObj.h"
#include "demo/EventDemoAttachment.h"
#include "object/collision/IObjHitCB.h"
#include "object/MoveTarget.h"
#include "gfl/gflTask.h"

/// @brief Base class for enemies and similar entities.
/// @note Size: `0x1774`
class EnemyBase : public FlfGameObj, public IObjHitCB, public demo::EventDemoAttachment {
public:

    /* Constructor */

    EnemyBase(gfl::Task* pParentTask, uint arg2, uint arg3, const char* pArg4);

    /* Virtual Methods */
    
    /* 0x08 */ virtual ~EnemyBase();

    /* -> FlfGameObj */
    /* 0x00C */ virtual void SetPosition(nw4r::math::VEC3& rPos) override;
    /* 0x010 */ virtual void vf10(bool arg1) override;
    /* 0x014 */ virtual nw4r::math::VEC3 GetPosition() override;
    /* 0x020 */ virtual void SetSecondaryPosition(nw4r::math::VEC3& rPos) override;
    /* 0x028 */ virtual void vf28() override;
    /* 0x02C */ virtual void vf2C(nw4r::math::VEC3& rArg1, nw4r::math::VEC3& rArg2, nw4r::math::VEC3& rArg3) override;
    /* 0x034 */ virtual bool ShouldCull(CameraManager* pCamMgr) override;
    /* 0x03C */ virtual int vf3C() override;
    /* 0x04C */ virtual void SetState(FlfGameObj* pSetter, std::string& rState) override;
    /* 0x064 */ virtual void vf64(bool) override;

    /* -> IObjHitCB */
    /* 0x70 */ virtual int vf8() override;

    /* -> demo::EventDemoAttachment */

    /* 0x080 */ virtual void vfC() override;
    /* 0x084 */ virtual void vf10() override;
    /* 0x088 */ virtual int  vf14_() override;
    /* 0x08C */ virtual void vf18() override;
    /* 0x090 */ virtual void vf1C() override;

    /* EnemyBase */

    /* 0x094 */ virtual void vf94();
    /* 0x098 */ virtual void vf98();
    /* 0x09C */ virtual void vf9C();
    /* 0x0A0 */ virtual void vfA0();

    // you get the idea

    /* 0x5A4 */ virtual void vf5A4();

    /* Class Members */
    
    /* 0x090 */ int m_90;
    /* 0x094 */ int m_94;
    /* 0x098 */ int m_98;
    /* 0x09C */ int m_9C;
    /* 0x0A0 */ int m_A0;
    /* 0x0A4 */ int m_A4;
    /* 0x0A8 */ int m_A8;
    /* 0x0AC */ int m_AC;
    /* 0x0B0 */ int m_B0;
    /* 0x0B4 */ nw4r::math::VEC3 m_B4;
    /* 0x0C0 */ int m_C0;
    /* 0x0C4 */ int m_C4;
    /* 0x0C8 */ int m_C8;
    /* 0x0CC */ int m_CC;
    /* 0x0D0 */ int m_D0;
    /* 0x0D4 */ int m_D4;
    /* 0x0D8 */ int m_D8;
    /* 0x0DC */ int m_DC;
    /* 0x0E0 */ int m_E0;
    /* 0x0E4 */ int m_E4;
    /* 0x0E8 */ int m_E8;
    /* 0x0EC */ int m_EC;
    /* 0x0F0 */ MoveTarget mMoveTargets[2]; // @ 0xF0
    /* 0x180 */ int m_180;
    /* 0x184 */ int m_184;
    /* 0x18C */ int m_18C;
    /* 0x190 */ int m_190;
    /* 0x194 */ nw4r::math::MTX44 m_194;
    /* 0x1D4 */ nw4r::math::VEC2 m_1D4;
    /* 0x1DC */ nw4r::math::VEC2 m_1DC;
    /* 0x1E4 */ STRUCT_FILL(0x1774 - 464);
};

// ASSERT_SIZE(EnemyBase, 0x1774);

#endif
