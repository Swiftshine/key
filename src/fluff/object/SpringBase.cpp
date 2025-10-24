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

// https://decomp.me/scratch/Y9XVP
void SpringBase::OffsetParticleEffectPositionByIndex(uint index, nw4r::math::VEC3& rOffset, bool syncPos) {
    Particle* particle = &mParticleArray1[index];

    particle->mEffectPosition.x = rOffset.x - mPosition.x;
    particle->mEffectPosition.y = rOffset.y - mPosition.y;
    particle->mEffectPosition.z = rOffset.z - mPosition.z;

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

// https://decomp.me/scratch/cAPvg
void SpringBase::GetParticleEffectOffsetByIndex(nw4r::math::VEC3& rDst, uint index) {
    nw4r::math::VEC3 offs = GetParticleEffectPositionByIndex(index);
    rDst = offs + mPosition;
}

nw4r::math::VEC3 SpringBase::fn_80008908(uint index) {
    return mParticleArray1[index].m_54;
}

nw4r::math::VEC3 SpringBase::fn_80008930(uint index) {
    nw4r::math::VEC3 offs = fn_80008908(index);
    nw4r::math::VEC3 vec = nw4r::math::VEC3(0, 0, 0);

    vec = offs - mPosition;
    
    return vec;
}

void SpringBase::fn_800089A0() {
    if (m_14C == nullptr) {
        m_14C = new (gfl::HeapID::Work) UnkStruct2[m_10C->mCount];
        fn_8000BB50();
    }
}