#include "object/SpringBase.h"


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

void SpringBase::SetParticleEffectPositionByIndex(uint index, Vec3f& vec, bool syncPos) {
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

Vec3f SpringBase::GetParticleEffectPositionByIndex(uint index) {
    return mMainParticleArray[index].mEffectPosition;
}

// void SpringBase::OffsetParticleEffectPositionByIndex(uint index, Vec3f& offset, bool syncPos) {

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

// Vec3f SpringBase::GetParticleEffectOffsetByIndex(uint index) {

// }

Vec3f SpringBase::fn_80008908(uint index) {
    return mMainParticleArray[index].m_54;
}
