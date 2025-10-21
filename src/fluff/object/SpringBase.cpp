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

int SpringBase::fn_800086B0() {
    return m_10C->mCount;
}

void SpringBase::fn_800086BC(uint index, bool val) {
    mMainParticleArray[index].m_40 = val;
}

void SpringBase::fn_800086D0(bool val) {
    for (uint i = 0; i < m_10C->mCount; i++) {
        fn_800086BC(i, val);
    }
}

bool SpringBase::fn_80008738(uint index) {
    return mMainParticleArray[index].m_40;
}

void SpringBase::SetParticleEffectPositionByIndex(uint index, nw4r::math::VEC3& vec, bool syncPos) {
    Particle* particle = &mMainParticleArray[index];

    particle->mEffectPosition.x = vec.x;
    particle->mEffectPosition.y = vec.y;
    particle->mEffectPosition.z = vec.z;

    if (syncPos) {
        particle = &mMainParticleArray[index];

        particle->mPosition.x = vec.x;
        particle->mPosition.y = vec.y;
        particle->mPosition.z = vec.z;
    }
}

nw4r::math::VEC3 SpringBase::GetParticleEffectPositionByIndex(uint index) {
    return mMainParticleArray[index].mEffectPosition;
}

// void SpringBase::OffsetParticleEffectPositionByIndex(uint index, nw4r::math::VEC3& offset, bool syncPos) {

// }

void SpringBase::OffsetParticleEffectPositionByIndex(uint index, Vec2f& offset, bool syncPos ) {
    Particle* particle = &mMainParticleArray[index];

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
    return mMainParticleArray[index].m_54;
}
