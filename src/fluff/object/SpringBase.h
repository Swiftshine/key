#ifndef FLUFF_SPRINGBASE_H
#define FLUFF_SPRINGBASE_H

#include "object/FlfGameObj.h"
#include "gfl/gflTask.h"
#include "graphics/KeyFrame.h"
#include "gfl/gflArray.h"
#include "gfl/gflResArchivedFileInfo.h"
#include "gfl/gflScopedPointer.h"
#include <nw4r/g3d/g3d_obj.h>

// size: 0x150
class SpringBase : public FlfGameObj {
public:
    // size: 0x18
    class Spring {
    public:
        int m_0;
        int m_4;
        float m_8;
        int m_C;
        float m_10;
    public:
        Spring();
        DECL_WEAK virtual ~Spring();
    };

    // size: 0x74
    class Particle {
    public:
        float m_0;
        float m_4;
        float m_8;
        float m_C;
        Vec3f mEffectPosition;
        Vec3f mPosition;
        float m_28;
        float m_2C;
        float m_30;
        float m_34;
        float m_38;
        float m_3C;
        bool m_40;
        nw4r::g3d::G3dObj* m_44;
        float m_48;
        float m_4C;
        float m_50;
        Vec3f m_54;
        float m_60;
        float m_64;
        float m_68;
        float m_6C;
    public:
        Particle();
        virtual ~Particle();

        void CopyVec(Vec3f& src);
    };

    struct UnkStruct1 {
        STRUCT_FILL(0x34);
        int mCount;
    };

    struct UnkStruct2 {
        UnkStruct2();

        Vec3f m_0;
        void* m_C;
    };
public:
    SpringBase(u32, const char* taskName);
    virtual ~SpringBase();

    /* SpringBase */

    virtual void vf68();
    virtual float GetZPos();
    virtual void vf70();
    virtual void vf74();
    virtual void vf78();
    virtual void vf7C();


    int fn_800086B0();
    void fn_800086BC(uint index, bool value) DONT_INLINE_CLASS;
    void fn_800086D0(bool value);
    bool fn_80008738(uint index);
    void SetParticleEffectPositionByIndex(uint index, Vec3f& pos, bool syncPosition);
    Vec3f GetParticleEffectPositionByIndex(uint index) DONT_INLINE_CLASS;
    void OffsetParticleEffectPositionByIndex(uint index, Vec3f& offset, bool syncPosition);
    void OffsetParticleEffectPositionByIndex(uint index, Vec2f& offset, bool syncPosition);
    Vec3f GetParticleEffectOffsetByIndex(uint index);
    Vec3f fn_80008908(uint index);
    Vec3f fn_80008930(uint index);
    void fn_800089A0();
    void fn_80008A34(uint index, Vec3f& vec, void* arg3);
    void fn_80008A68(Vec3f& vec, void* arg2);
    Vec3f fn_80008AE0();
    void fn_80008BB0(MTX34& mtx);
    void fn_80008DC0(MTX34& mtx);
    void fn_800090A4(void* arg1, void* arg2, void* arg3);
    float fn_80009248(uint index);
    float fn_8000925C(uint index);
    int fn_80009270(uint index);
    void fn_80009284(Vec3f& vec);
    void fn_800092A4();
    void fn_800092AC(float& arg1);
    void fn_80009568(UnkStruct1& unkStruct);
    void fn_80009678();
    void fn_80009E28(float& arg1);
    void fn_80009F64(float& arg1);
    void fn_8000A148();
    void fn_8000a748();
    void fn_8000AC6C();
    void fn_8000B15C(void* src, void* dst, UnkStruct1& unkStruct);
    void fn_8000B270();
    void fn_8000B6BC();
    void fn_8000B74C();
    static bool fn_8000B888(float&, Vec3f&, Vec3f&);
    void fn_8000BA30();
    void fn_8000BB50();
    void fn_8000BBD4();
private:
    gfl::Task mTask;
    gfl::ScopedPointer<gfl::ResArchivedFileInfo> mResArchivedFileInfo;
    int m_9C;
    gfl::Array<Particle> mMainParticleArray;
    gfl::Array<Particle> mSubParticleArrays[4];
    gfl::Array<Spring> mSprings;
    KeyFrame<float> mKeyFrame1;
    bool m_D0;
    KeyFrame<float> mKeyFrame2;
    bool m_EC;
    KeyFrame<float> mKeyFrame3;
    bool m_108;
    UnkStruct1* m_10C;
    float m_110;
    float m_114;
    float m_118;
    float m_11C;
    float m_120;
    float m_124;
    float m_128;
    float m_12C;
    float m_130;
    float m_134;
    float m_138;
    float m_13C;
    float m_140;
    int m_144;
    int m_148;
    gfl::Array<UnkStruct2> m_14C;
};

ASSERT_SIZE(SpringBase, 0x150);

#endif
