#ifndef FLUFF_FLFGAMEOBJ_H
#define FLUFF_FLFGAMEOBJ_H

#include "types.h"
#include "object/FlfHandleObj.h"
#include "util/ScreenPosition.h"
#include "gfl/gflVec2.h"
#include "gfl/gflVec3.h"
#include <nw4r/math.h>

#include <PowerPC_EABI_Support/MSL/MSL_C++/string>

class ColObj;
class CameraManager;

/// @brief The base class for many entites.
/// @note Size: `0x80`
class FlfGameObj : public FlfHandleObj {
public:
    /* Structures */

    ENUM_CLASS(ObjectCategory,
        Player          = 0,
        Gimmick         = 1,
        Cat2            = 2,
        Cat3            = 3,
        Cat4            = 4,
        Cat5            = 5,
        Cat6            = 6,
        Spring          = 7,
        Cat8            = 8,
        Cat9            = 9,
        Friend          = 10,
        Cat11           = 11,
        PlayerBullet    = 12,
        Misc            = 13, // for anything that doesn't fit in the prior categories

    );

    

    FlfGameObj(uint);

    /* Virtual Methods */
    
    /* 0x08 */ virtual ~FlfGameObj();
    /* 0x0C */ virtual void SetPosition(const nw4r::math::VEC3& rPosition) DONT_INLINE_CLASS;
    /* 0x10 */ virtual void vf10(bool val);
    /* 0x14 */ DECL_WEAK virtual bool vf14();
    /* 0x18 */ virtual void vf18();
    /* 0x1C */ virtual nw4r::math::VEC3 GetPosition();
    /* 0x20 */ virtual void SetSecondaryPosition(const nw4r::math::VEC3& rPosition);
    /* 0x24 */ virtual void Interact(FlfGameObj* pOther);
    /* 0x28 */ virtual void vf28();
    /* 0x2C */ virtual void vf2C(
        nw4r::math::VEC3& rArg1,
        const nw4r::math::VEC3& rOffset,
        nw4r::math::VEC3* pDst
    );
    /* 0x30 */ virtual void vf30();
    /* 0x34 */ virtual bool ShouldCull(CameraManager* pCamMgr);
    /* 0x38 */ virtual ScreenPosition GetScreenPosition();
    /* 0x3C */ virtual ColObj* GetColObj();
    /* 0x40 */ virtual void vf40(FlfGameObj*);
    /* 0x44 */ virtual int  vf44();

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
    /* 0x4C */ virtual void SetState(FlfGameObj* pSetter, const std::string& rState); 
    /* 0x50 */ virtual void vf50(bool arg1);
    /* 0x54 */ virtual bool vf54();
    /* 0x58 */ virtual void vf58();
    /* 0x5C */ virtual void SetCullThreshold(float threshold);
    /* 0x60 */ virtual float GetCullThreshold();
    /* 0x64 */ virtual void UpdateWater(bool);

    /* Class Methods */

    void UpdateMatrix();
    void SetCulled(bool culled);

    /* Static Methods */

    static void Destroy(FlfGameObj* pTarget);

    /* Class Members */
    
    /* 0x0C */ gfl::Vec3 mPosition;     
    /* 0x18 */ gfl::Vec3 mRotation;     
    /* 0x24 */ gfl::Vec3 mScale;        
    /* 0x30 */ nw4r::math::MTX34 mMatrix;       
    /* 0x60 */ u32 mFlags;     
    /* 0x64 */ u32 m_64;        
    /* 0x68 */ int mCategory;           
    /* 0x6C */ bool m_6C;           
    /* 0x6D */ bool mIsCulled;           
    /* 0x6E */ bool m_6E;           
    /* 0x6F */ bool m_6F;           
    /* 0x70 */ float mCullThreshold;
    /* 0x74 */ u32 m_74;            
    /* 0x78 */ u32 m_78;            
    /* 0x7C */ bool m_7C;           
    /* 0x7D */ bool m_7D;           
    /* 0x7E */ u16  m_7E;           
};

ASSERT_SIZE(FlfGameObj, 0x80);

#endif
