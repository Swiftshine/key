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
    , mKeyFrame1()
    , mKeyFrame2()
    , mKeyFrame3()
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
    Particle* particle = &mParticleArray1[index];

    particle->mEffectPosition = rVec;

    if (syncPos) {
        particle = &mParticleArray1[index];

        particle->mPosition = rVec;
    }
}

nw4r::math::VEC3 SpringBase::GetParticleEffectPositionByIndex(uint index) {
    return mParticleArray1[index].mEffectPosition;
}

// void SpringBase::OffsetParticleEffectPositionByIndex(uint index, nw4r::math::VEC3& offset, bool syncPos) {

// }

void SpringBase::OffsetParticleEffectPositionByIndex(uint index, Vec2f& offset, bool syncPos ) {
    Particle* particle = &mParticleArray1[index];

    particle->mEffectPosition.x = offset.x - mPosition.x;
    particle->mEffectPosition.y = offset.y - mPosition.y;

    if (syncPos) {
        particle->mPosition.x = particle->mEffectPosition.x;
        particle->mPosition.y = particle->mEffectPosition.y;
        particle->mPosition.z = particle->mEffectPosition.z;
    }
}

// nw4r::math::VEC3 SpringBase::GetParticleEffectOffsetByIndex(uint index) {

// }

nw4r::math::VEC3 SpringBase::fn_80008908(uint index) {
    return mParticleArray1[index].m_54;
}
