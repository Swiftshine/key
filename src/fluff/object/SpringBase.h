#ifndef FLUFF_SPRINGBASE_H
#define FLUFF_SPRINGBASE_H

#include "object/FlfGameObj.h"
#include "gfl/gflTask.h"
#include "graphics/KeyFrame.h"
#include "gfl/gflArray.h"
#include "gfl/gflPointer.h"
#include "gfl/gflResFileInfo.h"
#include "gfl/gflVec3.h"
#include <nw4r/g3d/g3d_obj.h>

/// @note Size: `0x150`
class SpringBase : public FlfGameObj {
public:

    /* Structures  */
    /// @note Size: `0x74`
    class Particle {
    public:
        /* Class Members */

        /* 0x00 */ float mScaleFactor;
        /* 0x04 */ gfl::Vec3 m_4;
        /* 0x10 */ gfl::Vec3 mEffectPosition;
        /* 0x1C */ gfl::Vec3 mPosition;
        /* 0x28 */ gfl::Vec3 m_28;
        /* 0x34 */ gfl::Vec3 m_34;
        /* 0x40 */ bool mInvalid;
        /* 0x44 */ nw4r::g3d::G3dObj* m_44;
        /* 0x48 */ gfl::Vec3 m_48;
        /* 0x54 */ gfl::Vec3 m_54;
        /* 0x60 */ gfl::Vec3 m_60;
        /* 0x6C */ bool m_6C;
        /* 0x6D */ bool m_6D;

        /* Constructor */

        Particle();
        
        /* Virtual Methods */

        /* 0x8 */ virtual ~Particle();

        /* Class Methods */
        void CopyVec(const gfl::Vec3& rSrc) DONT_INLINE_CLASS;
    };

    /// @note Size: `0x18`
    class Spring {
    public:
        /* Class Members */

        /* 0x00 */ uint mParticleIndex1;
        /* 0x04 */ uint mParticleIndex2;
        /* 0x08 */ float m_8;
        /* 0x0C */ int mActiveParticleIndex; // 0 for neither, 1 for the first, 2 for the second
        /* 0x10 */ float m_10;

        /* Constructor */

        Spring();

        /* Virtual Methods */

        /* 0x8 */ DECL_WEAK virtual ~Spring();
    };


    /// @note size unk (`0x4C`?)
    struct SpringTemplate {
        /* 0x00 */ float m_0;
        /* 0x04 */ float m_4[3];
        /* 0x10 */ float mPercentage;
        /* 0x14 */ float m_14;
        /* 0x18 */ gfl::Vec3 m_18;
        /* 0x24 */ int m_24;
        /* 0x28 */ bool m_28;
        /* 0x2C */ float m_2C;
        /* 0x30 */ int m_30;
        /* 0x34 */ uint mParticleCount;
        /* 0x38 */ uint mSpringCount;
        /* 0x3C */ uint m_3C;
        /* 0x40 */ bool m_40;
        /* 0x41 */ bool m_41;
        /* 0x44 */ float m_44;
        /* 0x48 */ float m_48;
    };

    /// @note Size: `0x10`
    struct UnkStruct2 {
        UnkStruct2();

        /* 0x0 */ gfl::Vec3 m_0;
        /* 0xC */ int m_C;
    };


    /* Constructor */

    SpringBase(int arg1, const char* pTaskName);

    /* Virtual Methods */

    /* 0x08 */ virtual ~SpringBase();

    /* SpringBase */

    /* 0x68 */ virtual float vf68();
    /* 0x6C */ virtual float GetZPos();
    /* 0x70 */ virtual void Update() const;
    /* 0x74 */ virtual void vf74(float scale, Particle* pParticle, gfl::Vec3& rDst);
    /* 0x78 */ virtual void vf78(float, Particle*, gfl::Vec3&);
    /* 0x7C */ virtual void vf7C(Particle*);

    /* Class Methods */

    uint GetParticleCount() DONT_INLINE_CLASS;
    void SetParticleInvalid(uint index, bool value) DONT_INLINE_CLASS;
    void SetParticlesInvalid(bool value) DONT_INLINE_CLASS;
    bool IsParticleInvalid(uint index);
    void SetParticleEffectPositionByIndex(uint index, gfl::Vec3& rPos, bool syncPosition);
    gfl::Vec3 GetParticleEffectPositionByIndex(uint index) DONT_INLINE_CLASS;
    void OffsetParticleEffectPositionByIndex(uint index, gfl::Vec3& rOffset, bool syncPosition) DONT_INLINE_CLASS;
    void OffsetParticleEffectPositionByIndex(uint index, nw4r::math::VEC2& rOffset, bool syncPosition) DONT_INLINE_CLASS;
    gfl::Vec3 GetParticleEffectOffsetByIndex(uint index) DONT_INLINE_CLASS;
    gfl::Vec3 fn_80008908(uint index) DONT_INLINE_CLASS;
    gfl::Vec3 fn_80008930(uint index) DONT_INLINE_CLASS;
    void fn_800089A0();
    void fn_80008A34(uint index, const gfl::Vec3& rVec, int arg3) DONT_INLINE_CLASS;
    void fn_80008A68(gfl::Vec3& rVec, int arg2) DONT_INLINE_CLASS;
    gfl::Vec3 GetKeyFrames() DONT_INLINE_CLASS;
    void fn_80008BB0(nw4r::math::MTX34& rMtx);
    void fn_80008DC0(nw4r::math::MTX34& rMtx);
    void ResetKeyFrames(KeyFrame<float>::FrameTemplate* pFTX, KeyFrame<float>::FrameTemplate* pFTY, KeyFrame<float>::FrameTemplate* pFTZ);
    float fn_80009248(uint index);
    float fn_8000925C(uint index);
    int fn_80009270(uint index);
    void fn_80009284(gfl::Vec3& rVec);
    void fn_800092A4();
    void fn_800092AC(float scale);
    void fn_80009568(SpringTemplate* pSpringTemplate) DONT_INLINE_CLASS;
    void fn_80009678(float scale) DONT_INLINE_CLASS;
    void fn_80009E28(float scale);
    void fn_80009F64(float scale);
    void fn_8000A148(float scale);
    void fn_8000A748(Particle* pParticles) DONT_INLINE_CLASS;
    void fn_8000AC6C(Particle* pParticle) DONT_INLINE_CLASS;
    void CopyParticles(Particle* pSrc, Particle* pDst, SpringTemplate* pSpringTemplate) DONT_INLINE_CLASS;
    void fn_8000B270() DONT_INLINE_CLASS;
    void fn_8000B6BC();
    bool fn_8000B74C();
    static bool fn_8000B888(float, gfl::Vec3&, const gfl::Vec3&);
    void LoadDefaultKeyFrames();
    void fn_8000BB50() DONT_INLINE_CLASS;
    void CreateParticleArrays() DONT_INLINE_CLASS;
    
    /* Class Members */

    /* 0x080 */ gfl::Task mTask;
    /* 0x098 */ gfl::ResFileObject mResFileObject;
    /* 0x09C */ int m_9C;
    /* 0x0A0 */ Particle* mParticleArray1;
    /* 0x0A4 */ Particle* mParticleArray2;
    /* 0x0A8 */ Particle* mParticleArray3;
    /* 0x0AC */ Particle* mParticleArray4;
    /* 0x0B0 */ Particle* mParticleArray5;
    /* 0x0B4 */ Spring* mSpringArray;
    /* 0x0B8 */ KeyFrame<float> mKeyFrameX;
    /* 0x0D4 */ KeyFrame<float> mKeyFrameY;
    /* 0x0F0 */ KeyFrame<float> mKeyFrameZ;
    /* 0x10C */ SpringTemplate* mSpringTemplate;
    /* 0x110 */ gfl::Vec3 mCurrentKeyFrames;
    /* 0x11C */ gfl::Vec3 m_11C;
    /* 0x128 */ gfl::Vec3 m_128;
    /* 0x134 */ float m_134;
    /* 0x138 */ gfl::Vec3 mParticleEffectMultiplier;
    /* 0x144 */ float m_144;
    /* 0x148 */ float m_148;
    /* 0x14C */ UnkStruct2* m_14C;
};

#endif
