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
    , mCurrentKeyFrames(0.0f, 0.0f, 0.0f)
    , m_11C(0.0f, 0.0f, 0.0f)
    , m_128(0.0f, 0.0f, 0.0f)
    , mParticleEffectMultiplier(0.0f, 0.0f, 0.0f)
{
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

    if (pSpringBase->mKeyFrameX.mInnerKeyFrames.size() != 0) {
        x = pSpringBase->mKeyFrameX.GetFrame(nullptr);
    }

    if (pSpringBase->mKeyFrameY.mInnerKeyFrames.size() != 0) {
        y = pSpringBase->mKeyFrameY.GetFrame(nullptr);
    }

    if (pSpringBase->mKeyFrameZ.mInnerKeyFrames.size() != 0) {
        z = pSpringBase->mKeyFrameZ.GetFrame(nullptr);
    }

    rDst.x = x;
    rDst.y = y;
    rDst.z = z;
}


inline float FloatAbs(float f) {
    return f < 0.0f ? -f : f;
} 

inline bool SomeInline(const nw4r::math::VEC3& rVec) {
    if (FloatAbs(rVec.x) < NW4R_MATH_FLT_EPSILON &&
        FloatAbs(rVec.y) < NW4R_MATH_FLT_EPSILON && 
        FloatAbs(rVec.z) < NW4R_MATH_FLT_EPSILON)
    {
        return true;
    }

    return false;
}


inline float VecAngle(nw4r::math::VEC3 &vec1, nw4r::math::VEC3 &vec2){
    float y =  VEC3Dot(&vec1, &vec2) / (PSVECMag(vec1) * PSVECMag(vec2));

    if (y > 1.0f) {
        y = 1.0f;
    }

    if (y < -1.0f) {
        y = -1.0f;
    }

    return acos(y);
}

void SpringBase::fn_80008BB0(nw4r::math::MTX34& rMtx) {
    nw4r::math::VEC3 offs0;
    nw4r::math::VEC3 offs;
    nw4r::math::VEC3 vec1;
    nw4r::math::VEC3 vec2;
    nw4r::math::VEC3 offs1;
    
    PSMTXIdentity(rMtx);
    GetParticleEffectOffsetByIndex(offs0, this, 0);
    GetParticleEffectOffsetByIndex(offs1, this, 1);

    const nw4r::math::VEC3* offsptr1 = &offs1;
    nw4r::math::VEC3* offsptr = &offs;
    const nw4r::math::VEC3* offsptr0 = &offs0;

    offs.x = 0.0f;
    offs.y = 0.0f;
    offs.z = 0.0f;
    
    VEC3Sub(offsptr, offsptr0, offsptr1);
    
    float y = 0.0f;

    vec1.x = 0.0f;
    vec1.y = -1.0f;
    vec1.z = 0.0f;

    
    if (!SomeInline(offs)) {
        y = VecAngle(offs,vec1);
    }

    vec2.x = 0.0f;
    vec2.y = 0.0f;
    vec2.z = 0.0f;

    PSVECCrossProduct(vec1, offs, vec2);

    y *= vec2.z >= 0.0f ? 1.0f : -1.0f;

    MTX34RotXYZRad(&rMtx, 0.0f, 0.0f, y);
    rMtx[0][3] = offs0.x;
    rMtx[1][3] = offs0.y;
    rMtx[2][3] = offs0.z;
}

void SpringBase::fn_80008DC0(nw4r::math::MTX34& rMtx) {
    nw4r::math::VEC3 offs0;
    nw4r::math::VEC3 offs;
    nw4r::math::VEC3 vec1;
    nw4r::math::VEC3 vec2;
    nw4r::math::VEC3 offs1;
    
    PSMTXIdentity(rMtx);
    GetParticleEffectOffsetByIndex(offs0, this, m_10C->mCount - 1);
    GetParticleEffectOffsetByIndex(offs1, this, m_10C->mCount - 2);

    const nw4r::math::VEC3* offsptr1 = &offs1;
    nw4r::math::VEC3* offsptr = &offs;
    const nw4r::math::VEC3* offsptr0 = &offs0;

    offs.x = 0.0f;
    offs.y = 0.0f;
    offs.z = 0.0f;
    
    VEC3Sub(offsptr, offsptr0, offsptr1);
    offs.z = 0.0f;

    float y = 0.0f;

    vec1.x = 0.0f;
    vec1.y = -1.0f;
    vec1.z = 0.0f;

    
    if (!SomeInline(offs)) {
        y = VecAngle(offs,vec1);
    }

    vec2.x = 0.0f;
    vec2.y = 0.0f;
    vec2.z = 0.0f;

    PSVECCrossProduct(vec1, offs, vec2);

    y *= vec2.z >= 0.0f ? 1.0f : -1.0f;

    MTX34RotXYZRad(&rMtx, 0.0f, 0.0f, y);
    rMtx[0][3] = offs0.x;
    rMtx[1][3] = offs0.y;
    rMtx[2][3] = offs0.z;
    
}

float SpringBase::vf68() {
    float ret = 0.0f;
    
    for (uint i = 0; i < m_10C->m_38; i++) {
        ret += mSpringArray[i].m_8;
    }

    return ret;
}

void SpringBase::ResetKeyFrames(
    KeyFrame<float>::FrameTemplate* pFTX,
    KeyFrame<float>::FrameTemplate* pFTY,
    KeyFrame<float>::FrameTemplate* pFTZ
) {
    mKeyFrameX.Reset();
    if (pFTX != nullptr) {
        mKeyFrameX.mIncrementAmount = 1.0f / 60.0f;

        for (uint i = 0; i < pFTX->mCount; i++) {
            mKeyFrameX.Add(pFTX->mStartFrames[i], pFTX->mEndFrames[i]);
        }

        mKeyFrameX.mCurrentFrame = pFTX->mDefaultFrame;
        mKeyFrameX.mHasFrames = true;
    }
    
    mKeyFrameY.Reset();
    if (pFTY != nullptr) {
        mKeyFrameY.mIncrementAmount = 1.0f / 60.0f;

        for (uint i = 0; i < pFTY->mCount; i++) {
            mKeyFrameY.Add(pFTY->mStartFrames[i], pFTY->mEndFrames[i]);
        }

        mKeyFrameY.mCurrentFrame = pFTY->mDefaultFrame;
        mKeyFrameY.mHasFrames = true;
    }
    
    mKeyFrameZ.Reset();
    if (pFTZ != nullptr) {
        mKeyFrameZ.mIncrementAmount = 1.0f / 60.0f;

        for (uint i = 0; i < pFTZ->mCount; i++) {
            mKeyFrameZ.Add(pFTZ->mStartFrames[i], pFTZ->mEndFrames[i]);
        }

        mKeyFrameZ.mCurrentFrame = pFTZ->mDefaultFrame;
        mKeyFrameZ.mHasFrames = true;
    }
}

float SpringBase::fn_80009248(uint index) {
    return mSpringArray[index].m_8;
}

float SpringBase::fn_8000925C(uint index) {
    return mSpringArray[index].m_10;
}

int SpringBase::fn_80009270(uint index) {
    return mSpringArray[index].m_C;
}

void SpringBase::fn_80009284(nw4r::math::VEC3& rVec) {
    m_10C->m_18 = rVec;
}

void SpringBase::fn_800092A4() {
    fn_80009568(m_10C);
}

// https://decomp.me/scratch/R1T4Y
void SpringBase::fn_800092AC(float scale) {
    for (uint i = 0; i < m_10C->mCount; i++) {
        mParticleArray1[i].m_28 = mParticleArray1[i].mEffectPosition;
    }

    if (m_10C->m_41) {
        for (uint i = 0; i < m_10C->mCount; i++) {
            Particle* particle = &mParticleArray1[i];
            float dot = VEC3Dot(
                &particle->mEffectPosition,
                &mParticleEffectMultiplier
            );
            if (m_144 + dot < 0.0f) {                    
                particle->m_6C = true;
            } else {
                particle->m_6C = false;
            }
        }

        m_144 -= m_148;
    } else {
        for (uint i = 0; i < m_10C->mCount; i++) {
            mParticleArray1[i].m_6C = true;
        }
    }

    switch (m_10C->m_24) {
        case 0:
            fn_80009E28(scale);
            break;
        case 2:
            fn_80009F64(scale);
            break;
        case 3:
            fn_8000A148(scale);
            break;
        case 1:
            fn_80009678(scale);
            break;
    }

    for (uint i = 0; i < m_10C->mCount; i++) {
        mParticleArray1[i].mPosition = mParticleArray1[i].m_28;
    }

    for (uint i = 0; i < m_10C->mCount; i++) {
        Particle* particle = &mParticleArray1[i];
        
        if (!particle->m_40) {
            vf78(scale, particle, particle->m_60);

            if (m_10C->m_28) {
                vf74(scale, particle, particle->m_60);
            }

            particle->mEffectPosition += particle->m_60;
        }
    }
}

void SpringBase::vf78(float, Particle*, const nw4r::math::VEC3&) { }

void SpringBase::fn_80009568(UnkStruct1* pArg1) {
    for (uint i = 0; i < pArg1->mCount; i++) {
        Particle* particle = &mParticleArray1[i];
        particle->m_34 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    }

    fn_8000BB50();
}

void SpringBase::Update() const {
    const_cast<SpringBase*>(this)->fn_8000B270();
    
    for (uint i = 0; i < m_10C->m_3C; i++) {
        const_cast<SpringBase*>(this)->fn_800092AC(1.0f / 60.0f / m_10C->m_3C);
        const_cast<SpringBase*>(this)->fn_80009568(m_10C);
    }
}

// not complete -- https://decomp.me/scratch/lM0lL
void SpringBase::fn_80009678(float scale) {
    CopyParticles(mParticleArray1, mParticleArray2, m_10C);
    
    fn_8000A748(mParticleArray2);

    for (uint i = 0; i < m_10C->mCount; i++) {
        Particle* particle = &mParticleArray2[i];
        particle->m_48 = particle->m_34 * ((1.0f / particle->m_0) * scale);
    }

    CopyParticles(mParticleArray2, mParticleArray3, m_10C);

    for (uint i = 0; i < m_10C->mCount; i++) {
        Particle* pa = &mParticleArray2[i];
        Particle* pb = &mParticleArray3[i];
        
        pb->m_4 += pa->m_48 * (0.5 * scale);
        pb->mEffectPosition += pb->m_4 * (0.5 * scale);
    }
    
    fn_8000A748(mParticleArray3);
    
    for (uint i = 0; i < m_10C->mCount; i++) {
        Particle* particle = &mParticleArray3[i];
        particle->m_48 = particle->m_34 * ((1.0f / particle->m_0) * scale);
    }

    CopyParticles(mParticleArray2, mParticleArray4, m_10C);
    
    for (uint i = 0; i < m_10C->mCount; i++) {
        Particle* pa = &mParticleArray3[i];
        Particle* pb = &mParticleArray4[i];
        
        pb->m_4 += pa->m_48 * (0.5 * scale);
        pb->mEffectPosition += pb->m_4 * (0.5 * scale);
    }

    fn_8000A748(mParticleArray4);

    for (uint i = 0; i < m_10C->mCount; i++) {
        Particle* particle = &mParticleArray4[i];
        particle->m_48 = particle->m_34 * ((1.0f / particle->m_0) * scale);
    }
    
    CopyParticles(mParticleArray2, mParticleArray5, m_10C);

    for (uint i = 0; i < m_10C->mCount; i++) {
        Particle* pa = &mParticleArray4[i];
        Particle* pb = &mParticleArray5[i];
        
        pb->m_4 += pa->m_48 * scale;
        pb->mEffectPosition += pb->m_4 * scale;
    }

    fn_8000A748(mParticleArray5);

    for (uint i = 0; i < m_10C->mCount; i++) {
        Particle* particle = &mParticleArray5[i];
        particle->m_48 = particle->m_34 * ((1.0f / particle->m_0) * scale);
    }


    for (uint i = 0; i < m_10C->mCount; i++) {
        Particle* p1 = &mParticleArray1[i];

        if (!p1->m_40) {
            continue;
        }

        // not complete
    }
}

void SpringBase::fn_80009E28(float scale) {
    UnkStruct1* s = m_10C;
    
    fn_8000A748(mParticleArray1);

    nw4r::math::VEC3 vec2;
    nw4r::math::VEC3 vec1;
    nw4r::math::VEC3 vec3;
    
    for (uint i = 0; i < s->mCount; i++) {
        Particle* particle = &mParticleArray1[i];

        if (particle->m_40) {
            continue;
        }
        
        float rate = 1.0f / particle->m_0;
        
        vec1.x = 0.0f;
        vec1.y = 0.0f;
        vec1.z = 0.0f;

        VEC3Scale(&vec1, &particle->m_34, rate);
        
        vec2.x = 0.0f;
        vec2.y = 0.0f;
        vec2.z = 0.0f;
        
        VEC3Scale(&vec2, &vec1, scale);
        
        particle->m_4 += vec2;
        
        vec3.x = 0.0f;
        vec3.y = 0.0f;
        vec3.z = 0.0f;

        VEC3Scale(&vec3, &particle->m_4, scale);

        particle->m_60 = vec3;
    }
}


// https://decomp.me/scratch/vwO7T
void SpringBase::fn_80009F64(float scale) {
    // not complete
}

void SpringBase::CopyParticles(Particle* pSrc, Particle* pDst, UnkStruct1* pArg3) {
    for (uint i = 0; i < pArg3->mCount; i++) {
        pDst[i] = pSrc[i];
        pDst[i].m_44 = nullptr;
    }
}