#ifndef FLUFF_SPRINGBASE_H
#define FLUFF_SPRINGBASE_H

#include "object/FlfGameObj.h"
#include "gfl/gflTask.h"
#include "graphics/KeyFrame.h"
#include "gfl/gflArray.h"
#include "gfl/gflResArchivedFileInfo.h"
#include "gfl/gflPointer.h"
#include <nw4r/g3d/g3d_obj.h>

/// @note Size: `0x150`
class SpringBase : public FlfGameObj {
public:

    /* Structures  */
    /// @note Size: `0x18`
    class Spring {
    public:
        /* Class Members */

        /* 0x00 */ int m_0;
        /* 0x04 */ int m_4;
        /* 0x08 */ float m_8;
        /* 0x0C */ int m_C;
        /* 0x10 */ float m_10;

        /* Constructor */

        Spring();

        /* Virtual Methods */

        /* 0x8 */ DECL_WEAK virtual ~Spring();
    };

    /// @note Size: `0x74`
    class Particle {
    public:
        /* Class Members */

        /* 0x00 */ float m_0;
        /* 0x04 */ float m_4;
        /* 0x08 */ float m_8;
        /* 0x0C */ float m_C;
        /* 0x10 */ Vec3f mEffectPosition;
        /* 0x1C */ Vec3f mPosition;
        /* 0x28 */ float m_28;
        /* 0x2C */ float m_2C;
        /* 0x30 */ float m_30;
        /* 0x34 */ float m_34;
        /* 0x38 */ float m_38;
        /* 0x3C */ float m_3C;
        /* 0x40 */ bool m_40;
        /* 0x44 */ nw4r::g3d::G3dObj* m_44;
        /* 0x48 */ float m_48;
        /* 0x4C */ float m_4C;
        /* 0x50 */ float m_50;
        /* 0x54 */ Vec3f m_54;
        /* 0x60 */ float m_60;
        /* 0x64 */ float m_64;
        /* 0x68 */ float m_68;
        /* 0x6C */ float m_6C;

        /* Constructor */

        Particle();
        
        /* Virtual Methods */

        /* 0x8 */ virtual ~Particle();

        /* Class Methods */
        void CopyVec(Vec3f& rSrc);
    };

    /// @note Size: `0x38`
    struct UnkStruct1 {
        /* 0x00 */ STRUCT_FILL(0x34);
        /* 0x34 */ int mCount;
    };

    /// @note Size: `0x10`
    struct UnkStruct2 {
        UnkStruct2();

        /* 0x0 */ Vec3f m_0;
        /* 0xC */ void* m_C;
    };


    /* Constructor */

    SpringBase(u32, const char* pTaskName);

    /* Virtual Methods */

    /* 0x08 */ virtual ~SpringBase();

    /* SpringBase */

    /* 0x68 */ virtual void vf68();
    /* 0x6C */ virtual float GetZPos();
    /* 0x70 */ virtual void vf70();
    /* 0x74 */ virtual void vf74();
    /* 0x78 */ virtual void vf78();
    /* 0x7C */ virtual void vf7C();

    /* Class Methods */

    int fn_800086B0();
    void fn_800086BC(uint index, bool value) DONT_INLINE_CLASS;
    void fn_800086D0(bool value);
    bool fn_80008738(uint index);
    void SetParticleEffectPositionByIndex(uint index, Vec3f& rPos, bool syncPosition);
    Vec3f GetParticleEffectPositionByIndex(uint index) DONT_INLINE_CLASS;
    void OffsetParticleEffectPositionByIndex(uint index, Vec3f& rOffset, bool syncPosition);
    void OffsetParticleEffectPositionByIndex(uint index, Vec2f& rOffset, bool syncPosition);
    Vec3f GetParticleEffectOffsetByIndex(uint index);
    Vec3f fn_80008908(uint index);
    Vec3f fn_80008930(uint index);
    void fn_800089A0();
    void fn_80008A34(uint index, Vec3f& rVec, void* pArg3);
    void fn_80008A68(Vec3f& rVec, void* pArg2);
    Vec3f fn_80008AE0();
    void fn_80008BB0(MTX34& mtx);
    void fn_80008DC0(MTX34& mtx);
    void fn_800090A4(void* pArg1, void* pArg2, void* pArg3);
    float fn_80009248(uint index);
    float fn_8000925C(uint index);
    int fn_80009270(uint index);
    void fn_80009284(Vec3f& rVec);
    void fn_800092A4();
    void fn_800092AC(float& rArg1);
    void fn_80009568(UnkStruct1& rArg1);
    void fn_80009678();
    void fn_80009E28(float& rArg1);
    void fn_80009F64(float& rArg1);
    void fn_8000A148();
    void fn_8000a748();
    void fn_8000AC6C();
    void fn_8000B15C(void* pSrc, void* pDest, UnkStruct1& rArg3);
    void fn_8000B270();
    void fn_8000B6BC();
    void fn_8000B74C();
    static bool fn_8000B888(float&, Vec3f&, Vec3f&);
    void fn_8000BA30();
    void fn_8000BB50();
    void fn_8000BBD4();

    /* Class Members */

    /* 0x80 */ gfl::Task mTask;
    /* 0x98 */ gfl::Pointer<gfl::ResArchivedFileInfo> mResArchivedFileInfo;
    /* 0x9C */ int m_9C;
    /* 0xA0 */ gfl::Array<Particle> mMainParticleArray;
    /* 0xA4 */ gfl::Array<Particle> mSubParticleArrays[4];
    /* 0xA8 */ gfl::Array<Spring> mSprings;
    /* 0xB8 */ KeyFrame<float> mKeyFrame1;
    /* 0xD0 */ bool m_D0;
    /* 0xD4 */ KeyFrame<float> mKeyFrame2;
    /* 0xEC */ bool m_EC;
    /* 0xF0 */ KeyFrame<float> mKeyFrame3;
    /* 0x108 */ bool m_108;
    /* 0x10C */ UnkStruct1* m_10C;
    /* 0x110 */ float m_110;
    /* 0x114 */ float m_114;
    /* 0x118 */ float m_118;
    /* 0x11C */ float m_11C;
    /* 0x120 */ float m_120;
    /* 0x124 */ float m_124;
    /* 0x128 */ float m_128;
    /* 0x12C */ float m_12C;
    /* 0x130 */ float m_130;
    /* 0x134 */ float m_134;
    /* 0x138 */ float m_138;
    /* 0x13C */ float m_13C;
    /* 0x140 */ float m_140;
    /* 0x144 */ int m_144;
    /* 0x148 */ int m_148;
    /* 0x14C */ gfl::Array<UnkStruct2> m_14C;
};

#endif
