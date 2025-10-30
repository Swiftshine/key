#include "object/SpringBase.h"

/* Particle */

SpringBase::Particle::Particle()
    : m_28(0.0f, 0.0f, 0.0f)
    , m_60(0.0f, 0.0f, 0.0f)
{
    m_0 = 0.0f;
    m_4 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    mEffectPosition = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    mPosition = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    m_34 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    m_40 = 0.0f;
    m_44 = nullptr;
    m_48 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    m_54 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
}

SpringBase::Particle::~Particle() {
    if (m_44 != nullptr) {
        m_44->Destroy();
    }
}

void SpringBase::Particle::CopyVec(const nw4r::math::VEC3& rSrc) {
    mPosition = rSrc;
    m_54 = rSrc;
    mEffectPosition = rSrc;
}

/* Spring */

SpringBase::Spring::Spring() {
    m_0 = 0;
    m_4 = 0;
    m_8 = 0.0f;
    m_C = 0;
    m_10 = -1.0f;
}

SpringBase::Spring::~Spring() { }

/* SpringBase */

SpringBase::SpringBase(int arg1, const char* pTaskName)
    : FlfGameObj(ObjectCategory::Spring)
    , mTask(this, SpringBase::Update, pTaskName)
    , mResFileObject(nullptr)
    , mKeyFrameX()
    , mKeyFrameY()
    , mKeyFrameZ()
{
    m_110 = 0.0f;
    m_114 = 0.0f;
    m_118 = 0.0f;
    m_11C = 0.0f;
    m_120 = 0.0f;
    m_124 = 0.0f;
    m_128 = 0.0f;
    m_12C = 0.0f;
    m_130 = 0.0f;
    m_138 = 0.0f;
    m_13C = 0.0f;
    m_140 = 0.0f;
    m_14C = nullptr;
    m_9C = arg1;
    mParticleArray1 = nullptr;
    mParticleArray2 = nullptr;
    mParticleArray3 = nullptr;
    mParticleArray4 = nullptr;
    mParticleArray5 = nullptr;
    mSpringArray = nullptr;
    mPosition = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    m_10C = nullptr;
}

SpringBase::~SpringBase() {
    if (mParticleArray1 != nullptr) {
        delete[] mParticleArray1;
    }

    for (uint i = 0; i < 4; i++) {
        Particle** p = &mParticleArray2 + i;

        if (*p != nullptr) {
            delete[] *p;
        }
    }

    if (mSpringArray != nullptr) {
        delete[] mSpringArray;
    }    

    // possibly inline?
    // i know it's not a gfl::Pointer
    UnkStruct2* unk2 = m_14C;
    if (unk2 != nullptr && unk2 != nullptr) {
        delete (unk2 - 1);
    }
}

int SpringBase::fn_800086B0() {
    return m_10C->mCount;
}

void SpringBase::fn_800086BC(uint index, bool val) {
    mParticleArray1[index].m_40 = val;
}

void SpringBase::fn_800086D0(bool val) {
    for (uint i = 0; i < m_10C->mCount; i++) {
        fn_800086BC(i, val);
    }
}

bool SpringBase::fn_80008738(uint index) {
    return mParticleArray1[index].m_40;
}

void SpringBase::SetParticleEffectPositionByIndex(uint index, nw4r::math::VEC3& rVec, bool syncPos) {
    mParticleArray1[index].mEffectPosition = rVec;
    if (syncPos) {
        mParticleArray1[index].mPosition = rVec;
    }
}

nw4r::math::VEC3 SpringBase::GetParticleEffectPositionByIndex(uint index) {
    nw4r::math::VEC3 vec;
    vec = mParticleArray1[index].mEffectPosition;
    return vec;
}

void SpringBase::OffsetParticleEffectPositionByIndex(uint index, nw4r::math::VEC3& rOffset, bool syncPos) {
    Particle* particle = &mParticleArray1[index];
    nw4r::math::VEC3 vec(0, 0, 0);
    VEC3Sub(&vec, &rOffset, &mPosition);
    
    particle->mEffectPosition = vec;
    
    if (syncPos) {
        particle->mPosition = particle->mEffectPosition;
    }
}

void SpringBase::OffsetParticleEffectPositionByIndex(uint index, nw4r::math::VEC2& rOffset, bool syncPos ) {
    Particle* particle = &mParticleArray1[index];

    particle->mEffectPosition.x = rOffset.x - mPosition.x;
    particle->mEffectPosition.y = rOffset.y - mPosition.y;

    if (syncPos) {
        particle->mPosition = particle->mEffectPosition;
    }
}

void SpringBase::GetParticleEffectOffsetByIndex(nw4r::math::VEC3& rDst, SpringBase* pSpringBase, uint index) {
    nw4r::math::VEC3 offs = pSpringBase->GetParticleEffectPositionByIndex(index);
    rDst.x = 0.0f;
    rDst.y = 0.0f;
    rDst.z = 0.0f;
    VEC3Add(&rDst, &offs, &pSpringBase->mPosition);
}

void SpringBase::fn_80008908(nw4r::math::VEC3& rDst, SpringBase* pSpringBase, uint index) {
    rDst = pSpringBase->mParticleArray1[index].m_54;
}

void SpringBase::fn_80008930(nw4r::math::VEC3& rDst, SpringBase* pSpringBase, uint index) {
    nw4r::math::VEC3 offs;
    fn_80008908(offs, pSpringBase, index);
    rDst.x = 0.0f;
    rDst.y = 0.0f;
    rDst.z = 0.0f;
    VEC3Add(&rDst, &offs, &pSpringBase->mPosition);
}

void SpringBase::fn_800089A0() {
    if (m_14C == nullptr) {
        m_14C = new (gfl::HeapID::Work) UnkStruct2[m_10C->mCount];
        fn_8000BB50();
    }
}

SpringBase::UnkStruct2::UnkStruct2()
    : m_0(0.0f, 0.0f, 0.0f)
    , m_C(0)
{ }

void SpringBase::fn_80008A34(uint index, const nw4r::math::VEC3& rVec, int arg3) {
    m_14C[index].m_0 = rVec;
    m_14C[index].m_C = arg3;
}

void SpringBase::fn_80008A68(nw4r::math::VEC3& rVec, int arg2) {
    for (uint i = 0; i < m_10C->mCount; i++) {
        fn_80008A34(i, rVec, arg2);
    }
}

void SpringBase::GetKeyframes(nw4r::math::VEC3& rDst, SpringBase* pSpringBase) {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    if (pSpringBase->mKeyFrameX.mFrameHolder.mCount != 0) {
        x = pSpringBase->mKeyFrameX.GetFrame(nullptr);
    }

    if (pSpringBase->mKeyFrameY.mFrameHolder.mCount != 0) {
        y = pSpringBase->mKeyFrameY.GetFrame(nullptr);
    }

    if (pSpringBase->mKeyFrameZ.mFrameHolder.mCount != 0) {
        z = pSpringBase->mKeyFrameZ.GetFrame(nullptr);
    }

    rDst.x = x;
    rDst.y = y;
    rDst.z = z;
}

inline bool SomeInline(const nw4r::math::VEC3& rVec) {
    float f = rVec.x;

    if (rVec.x < 0.0f) {
        f = -rVec.x;
    }

    if (f < NW4R_MATH_FLT_EPSILON) {
        f = rVec.y;
        if (rVec.y < 0.0f) {
            f = -rVec.y;
        }

        if (f < NW4R_MATH_FLT_EPSILON) {
            f = rVec.z;
            if (rVec.z < 0.0f) {
                f = -rVec.z;
            }

            if (f < NW4R_MATH_FLT_EPSILON) {
                return true;
            }
        }
    }

    return false;
}

// not complete
void SpringBase::fn_80008BB0(nw4r::math::MTX34& rMtx) {
    PSMTXIdentity(rMtx);
    nw4r::math::VEC3 offs0;
    nw4r::math::VEC3 offs1;
    GetParticleEffectOffsetByIndex(offs0, this, 0);
    GetParticleEffectOffsetByIndex(offs1, this, 1);
    
    nw4r::math::VEC3 offs;
    VEC3Sub(&offs, &offs0, &offs1);

    nw4r::math::VEC3 vec1(0.0f, -1.0f, 0.0f);

    if (SomeInline(offs)) {

    }


    rMtx[0][3] = offs.x;
    rMtx[1][3] = offs.y;
    rMtx[2][3] = offs.z;
}

