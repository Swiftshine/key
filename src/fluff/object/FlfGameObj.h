#ifndef FLUFF_FLFGAMEOBJ_H
#define FLUFF_FLFGAMEOBJ_H

#include "types.h"
#include "object/FlfHandleObj.h"
#include "util/ScreenPosition.h"
#include "util/Orientation.h"
#include "gfl/gflMtx34.h"
#include "gfl/gflVec2.h"
#include "gfl/gflVec3.h"
#include <nw4r/math.h>

#include <PowerPC_EABI_Support/MSL/MSL_C++/string>

class ColObj;
class CamMng;

/// @brief The base class for many entites.
/// @note Size: `0x80`
class FlfGameObj : public FlfHandleObj {
public:
    /* Structures */

    enum ObjectCategory {
        eObjectCategory_Player          = 0,
        eObjectCategory_Gimmick         = 1,
        eObjectCategory_Cat2            = 2,
        eObjectCategory_Cat3            = 3,
        eObjectCategory_Cat4            = 4,
        eObjectCategory_Cat5            = 5,
        eObjectCategory_Cat6            = 6,
        eObjectCategory_Spring          = 7,
        eObjectCategory_Cat8            = 8,
        eObjectCategory_Cat9            = 9,
        eObjectCategory_Friend          = 10,
        eObjectCategory_Cat11           = 11,
        eObjectCategory_PlayerBullet    = 12,
        eObjectCategory_Misc            = 13, // for anything that doesn't fit in the prior categories
    };

    FlfGameObj(u32);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfGameObj();
    /* 0x0C */ virtual void SetPosition(const gfl::Vec3& rPosition) DONT_INLINE_CLASS {
        mPosition = rPosition;
    }
    /* 0x10 */ virtual void vf10(bool val);
    /* 0x14 */ DECL_WEAK virtual bool vf14();
    /* 0x18 */ virtual void vf18();
    /* 0x1C */ virtual gfl::Vec3 GetPosition() const {
        return mPosition;
    }
    /* 0x20 */ virtual void SetSecondaryPosition(const gfl::Vec3& rPosition) {
        FlfGameObj::SetPosition(rPosition);
    }
    /* 0x24 */ virtual void Interact(FlfGameObj* pOther) { }
    /* 0x28 */ virtual void Interact() { }
    /* 0x2C */ virtual void MoveByOffset(
        gfl::Vec3& rArg1,
        const gfl::Vec3& rOffset,
        gfl::Vec3* pDst
    ) {
        if (m_6F) {
            return;
        }

        gfl::Vec3 pos;
        pos = mPosition;
        pos += rOffset;
        SetPosition(pos);

        if (pDst != nullptr) {
            *pDst = rOffset;
        }
    }
    /* 0x30 */ virtual void vf30() { }
    /* 0x34 */ virtual bool ShouldCull(CamMng* pCamMgr);
    /* 0x38 */ virtual ScreenPosition GetScreenPosition() const { // nonmatching
        ScreenPosition pos;
        pos.mX = mPosition.x;
        pos.mY = mPosition.y;
        pos.mCullThreshold = mCullThreshold;
        return pos;
    }
    /* 0x3C */ virtual ColObj* GetColObj() const {
        return nullptr;
    }
    /* 0x40 */ virtual void vf40(FlfGameObj*) { }
    /* 0x44 */ DECL_WEAK virtual s32  vf44() {
        return 1;
    }

    // looks for gimmicks or enemies with a specific tag and sets their
    // state to the specified one if found. the tag list consists of
    // four-character tags, delimited by a semicolon.
    // i.e. tag1;tag2;tag3;

    /// @brief Looks for gimmicks or enemies with any tag within the tag list
    /// and sets their state to the one provided.
    /// @param pState The target state.
    /// @param pTagList A string of four-character tags, delimited by a semicolon.
    /// e.g. "tag1;tag2;tag3;"
    /* 0x48 */ virtual void SetStateForTaggedObjects(const char* pState, const char* pTagList);
    /// @brief Sets the object state.
    /// @param pSetter A pointer to the object that induced the call.
    /// @param rState The target state.
    /* 0x4C */ virtual void SetState(FlfGameObj* pSetter, const std::string& rState) { }
    /* 0x50 */ virtual void SetIsInMission(bool inMission) {
        mIsInMission = inMission;
    }
    /* 0x54 */ virtual bool IsInMission() const {
        return mIsInMission;
    }
    /* 0x58 */ virtual void vf58() { }
    /* 0x5C */ virtual void SetCullThreshold(f32 threshold) {
        mCullThreshold = threshold;
    }
    /* 0x60 */ virtual f32 GetCullThreshold() const {
        return mCullThreshold;
    }
    /* 0x64 */ virtual void UpdateWater(bool) { }

    /* Class Methods */

    void UpdateMatrix();
    void SetCulled(bool culled);

    /* Static Methods */

    static void Destroy(FlfGameObj* pTarget);

    /* Class Members */

    /* 0x0C */ gfl::Vec3 mPosition;
    /* 0x18 */ gfl::Vec3 mRotation;
    /* 0x24 */ gfl::Vec3 mScale;
    /* 0x30 */ gfl::Mtx34 mMatrix;
    /* 0x60 */ u32 mFlags;
    /* 0x64 */ u32 m_64;
    /* 0x68 */ s32 mCategory;
    /* 0x6C */ bool m_6C;
    /* 0x6D */ bool mIsCulled;
    /* 0x6E */ bool mShouldUpdateWater;
    /* 0x6F */ bool m_6F;
    /* 0x70 */ f32 mCullThreshold;
    /* 0x74 */ s32 mDirection;
    /* 0x78 */ u32 m_78;
    /* 0x7C */ bool m_7C;
    /* 0x7D */ bool mIsInMission;
    /* 0x7E */ u16  m_7E;
};

ASSERT_SIZE(FlfGameObj, 0x80);

#endif
