#include "object/SpringBase.h"
#include "gfl/gflVec3.h"

typedef gfl::FunctorClassMethod0<void, SpringBase*, void (SpringBase::*)() const> FunctorType;

const KeyFrame<float>::FrameTemplate SpringBase_FrameTemplateX = {
    /* mCount */ 5,
    /* mStartFrames */ {
        /* 0 */ 0.0f,
        /* 1 */ -5.0f,
        /* 2 */ 0.0f,
        /* 3 */ 5.0f,
        /* 4 */ 0.0f,
        /* 5 */ 0.0f,
        /* 6 */ 0.0f,
        /* 7 */ 0.0f,
    },
    /* mEndFrames */ {
        /* 0 */ 0.0f,
        /* 1 */ 2.0f,
        /* 2 */ 2.0f,
        /* 3 */ 2.0f,
        /* 4 */ 2.0f,
        /* 5 */ 0.0f,
        /* 6 */ 0.0f,
        /* 7 */ 0.0f
    },
    /* mDefaultFrame */ 0.0f
};

const KeyFrame<float>::FrameTemplate SpringBase_FrameTemplateY = {
    /* mCount */ 5,
    /* mStartFrames */ {
        /* 0 */ 0.0f,
        /* 1 */ 1.0f,
        /* 2 */ 0.0f,
        /* 3 */ 1.0f,
        /* 4 */ 0.0f,
        /* 5 */ 0.0f,
        /* 6 */ 0.0f,
        /* 7 */ 0.0f,
    },
    /* mEndFrames */ {
        /* 0 */ 0.0f,
        /* 1 */ 1.0f,
        /* 2 */ 1.0f,
        /* 3 */ 1.0f,
        /* 4 */ 1.0f,
        /* 5 */ 0.0f,
        /* 6 */ 0.0f,
        /* 7 */ 0.0f
    },
    /* mDefaultFrame */ 0.0f
};


const KeyFrame<float>::FrameTemplate SpringBase_FrameTemplateZ = {
    /* mCount */ 5,
    /* mStartFrames */ {
        /* 0 */ 0.0f,
        /* 1 */ -5.0f,
        /* 2 */ 0.0f,
        /* 3 */ 5.0f,
        /* 4 */ 0.0f,
        /* 5 */ 0.0f,
        /* 6 */ 0.0f,
        /* 7 */ 0.0f,
    },
    /* mEndFrames */ {
        /* 0 */ 0.0f,
        /* 1 */ 1.0f,
        /* 2 */ 1.0f,
        /* 3 */ 1.0f,
        /* 4 */ 1.0f,
        /* 5 */ 0.0f,
        /* 6 */ 0.0f,
        /* 7 */ 0.0f
    },
    /* mDefaultFrame */ 0.0f
};

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
    mInvalid = false;
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
    mParticleIndex1 = 0;
    mParticleIndex2 = 0;
    m_8 = 0.0f;
    mActiveParticleIndex = 0;
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
    mSpringTemplate = nullptr;
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

uint SpringBase::GetParticleCount() {
    return mSpringTemplate->mParticleCount;
}

void SpringBase::SetParticleInvalid(uint index, bool val) {
    mParticleArray1[index].mInvalid = val;
}

void SpringBase::SetParticlesInvalid(bool val) {
    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        SetParticleInvalid(i, val);
    }
}

bool SpringBase::IsParticleInvalid(uint index) {
    return mParticleArray1[index].mInvalid;
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
        m_14C = new (gfl::HeapID::Work) UnkStruct2[mSpringTemplate->mParticleCount];
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
    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        fn_80008A34(i, rVec, arg2);
    }
}

void SpringBase::GetKeyFrames(nw4r::math::VEC3& rDst, SpringBase* pSpringBase) {
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
    float y =  VEC3Dot(&vec1, &vec2) / (VEC3Len(&vec1) * VEC3Len(&vec2));

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
    GetParticleEffectOffsetByIndex(offs0, this, mSpringTemplate->mParticleCount - 1);
    GetParticleEffectOffsetByIndex(offs1, this, mSpringTemplate->mParticleCount - 2);

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
    
    for (uint i = 0; i < mSpringTemplate->mSpringCount; i++) {
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
    return mSpringArray[index].mActiveParticleIndex;
}

void SpringBase::fn_80009284(nw4r::math::VEC3& rVec) {
    mSpringTemplate->m_18 = rVec;
}

void SpringBase::fn_800092A4() {
    fn_80009568(mSpringTemplate);
}

// https://decomp.me/scratch/R1T4Y
void SpringBase::fn_800092AC(float scale) {
    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        mParticleArray1[i].m_28 = mParticleArray1[i].mEffectPosition;
    }

    if (mSpringTemplate->m_41) {
        for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
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
        for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
            mParticleArray1[i].m_6C = true;
        }
    }

    switch (mSpringTemplate->m_24) {
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

    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        mParticleArray1[i].mPosition = mParticleArray1[i].m_28;
    }

    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray1[i];
        
        if (!particle->mInvalid) {
            vf78(scale, particle, particle->m_60);

            if (mSpringTemplate->m_28) {
                vf74(scale, particle, particle->m_60);
            }

            particle->mEffectPosition += particle->m_60;
        }
    }
}

void SpringBase::vf78(float, Particle*, nw4r::math::VEC3&) { }

void SpringBase::fn_80009568(SpringTemplate* pSpringTemplate) {
    for (uint i = 0; i < pSpringTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray1[i];
        particle->m_34 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    }

    fn_8000BB50();
}

void SpringBase::Update() const {
    const_cast<SpringBase*>(this)->fn_8000B270();
    
    for (uint i = 0; i < mSpringTemplate->m_3C; i++) {
        const_cast<SpringBase*>(this)->fn_800092AC(1.0f / 60.0f / mSpringTemplate->m_3C);
        const_cast<SpringBase*>(this)->fn_80009568(mSpringTemplate);
    }
}

// not complete -- https://decomp.me/scratch/lM0lL
void SpringBase::fn_80009678(float scale) {
    CopyParticles(mParticleArray1, mParticleArray2, mSpringTemplate);
    
    fn_8000A748(mParticleArray2);

    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray2[i];
        particle->m_48 = particle->m_34 * ((1.0f / particle->m_0) * scale);
    }

    CopyParticles(mParticleArray2, mParticleArray3, mSpringTemplate);

    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        Particle* pa = &mParticleArray2[i];
        Particle* pb = &mParticleArray3[i];
        
        pb->m_4 += pa->m_48 * (0.5 * scale);
        pb->mEffectPosition += pb->m_4 * (0.5 * scale);
    }
    
    fn_8000A748(mParticleArray3);
    
    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray3[i];
        particle->m_48 = particle->m_34 * ((1.0f / particle->m_0) * scale);
    }

    CopyParticles(mParticleArray2, mParticleArray4, mSpringTemplate);
    
    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        Particle* pa = &mParticleArray3[i];
        Particle* pb = &mParticleArray4[i];
        
        pb->m_4 += pa->m_48 * (0.5 * scale);
        pb->mEffectPosition += pb->m_4 * (0.5 * scale);
    }

    fn_8000A748(mParticleArray4);

    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray4[i];
        particle->m_48 = particle->m_34 * ((1.0f / particle->m_0) * scale);
    }
    
    CopyParticles(mParticleArray2, mParticleArray5, mSpringTemplate);

    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        Particle* pa = &mParticleArray4[i];
        Particle* pb = &mParticleArray5[i];
        
        pb->m_4 += pa->m_48 * scale;
        pb->mEffectPosition += pb->m_4 * scale;
    }

    fn_8000A748(mParticleArray5);

    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray5[i];
        particle->m_48 = particle->m_34 * ((1.0f / particle->m_0) * scale);
    }


    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        Particle* p1 = &mParticleArray1[i];

        if (!p1->mInvalid) {
            continue;
        }

        // not complete
    }
}

inline void ClearVec(nw4r::math::VEC3& v) {
    v.x = 0.0f;
    v.y = 0.0f;
    v.z = 0.0f;
}

void SpringBase::fn_80009E28(float scale) {
    SpringTemplate* springTemplate = mSpringTemplate;
    
    fn_8000A748(mParticleArray1);

    nw4r::math::VEC3 vec2;
    nw4r::math::VEC3 vec1;
    nw4r::math::VEC3 vec3;
    
    for (uint i = 0; i < springTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray1[i];

        if (particle->mInvalid) {
            continue;
        }
        
        float rate = 1.0f / particle->m_0;

        ClearVec(vec1);
    
        VEC3Scale(&vec1, &particle->m_34, rate);
        
        ClearVec(vec2);

        VEC3Scale(&vec2, &vec1, scale);
        
        particle->m_4 += vec2;

        ClearVec(vec3);

        VEC3Scale(&vec3, &particle->m_4, scale);
        
        particle->m_60 = vec3;
    }
}

// https://decomp.me/scratch/vwO7T
void SpringBase::fn_80009F64(float scale) {
    SpringTemplate* springTemplate = mSpringTemplate;

    fn_8000A748(mParticleArray1);

    nw4r::math::VEC3 vec2;
    nw4r::math::VEC3 vec1;
    nw4r::math::VEC3 vec7;
    nw4r::math::VEC3 vec3;
    nw4r::math::VEC3 vec6;
    nw4r::math::VEC3 vec5;
    nw4r::math::VEC3 vec4;

    
    for (uint i = 0; i < springTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray1[i];

        if (particle->mInvalid) {
            continue;
        }
    
        float rate = 1.0f / particle->m_0;

        ClearVec(vec1);
        
        ClearVec(vec2);

        VEC3Scale(&vec1, &particle->m_34, rate);

        VEC3Scale(&vec2, &vec1, scale);

        particle->m_4 += vec2;

        ClearVec(vec4); 

        ClearVec(vec3); 

        ClearVec(vec5);
  
        ClearVec(vec6);
        
        ClearVec(vec7);

        VEC3Sub(&vec3, &particle->mEffectPosition, &particle->mPosition);

        VEC3Scale(&vec4, &particle->m_34, 1.0f / particle->m_0);

        VEC3Scale(&vec5, &vec4, scale);

        VEC3Scale(&vec6, &vec5, scale);
  
        VEC3Add(&vec7, &vec3, &vec6);

        particle->m_60 = vec7;
    }
}

// https://decomp.me/scratch/zb3kQ
void SpringBase::fn_8000A148(float scale) {
    SpringTemplate* springTemplate = mSpringTemplate;
    fn_8000AC6C(mParticleArray1);

    float unk1 = 0.01f * (100.0f - springTemplate->mPercentage);

    for (uint i = 0; i < springTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray1[i];

        if (particle->mInvalid) {
            continue;
        }

        float rate = 1.0f / particle->m_0;
        particle->m_60 = (particle->mEffectPosition - particle->mPosition) * unk1 + particle->m_34 * rate * scale * scale;
    }

    for (uint i = 0; i < springTemplate->mParticleCount; i++) {
        mParticleArray1[i].m_6D = false;
    }


    for (uint i = 0; i < mSpringTemplate->mSpringCount; i++) {
        Spring* spring = &mSpringArray[i];

        if (1.0f > spring->m_10) {
            continue;
        }

        uint index1 = spring->mParticleIndex1;
        uint index2 = spring->mParticleIndex2;

        Particle* p1 = &mParticleArray1[index1];
        Particle* p2 = &mParticleArray1[index2];

        if (!p1->mInvalid || !p2->mInvalid) {
            nw4r::math::VEC3 vecA = (p2->mEffectPosition + p2->m_60) - (p1->mEffectPosition - p1->m_60);

            float unk2;
            if (SomeInline(vecA)) {
                vecA.x = unk1;
                vecA.y = -1.0f;
                vecA.z = unk1;

                unk2 = 0.0f;
            } else {
                unk2 = VEC3Len(&vecA);
                vecA *= 1.0f / unk2;
            }

            float unk3 = -(spring->m_8 * spring->m_10 - unk2);

            if (unk3 >= 0.0f) {
                continue;
            }

            nw4r::math::VEC3 vecB = vecA * unk3 * 0.5f;

            if (p1->mInvalid || p1->mInvalid) {
                vecB *= 2.0f;
            }

            if (!p1->mInvalid) {
                p1->m_60 = (p1->mEffectPosition + p1->m_60 + vecB) - p1->mEffectPosition;
            }

            if (!p2->mInvalid) {
                p2->m_60 = (p2->mEffectPosition + p2->m_60 + vecB) - p2->mEffectPosition;
            }
        }
    }
}

void SpringBase::fn_8000A748(Particle* pParticles) {
    // not decompiled
}

void SpringBase::fn_8000AC6C(Particle* pParticles) {
    // not decompiled
}

void SpringBase::CopyParticles(Particle* pSrc, Particle* pDst, SpringTemplate* pSpringTemplate) {
    for (uint i = 0; i < pSpringTemplate->mParticleCount; i++) {
        pDst[i] = pSrc[i];
        pDst[i].m_44 = nullptr;
    }
}

void SpringBase::fn_8000B270() {
    nw4r::math::VEC3 keyFramesA;
    GetKeyFrames(keyFramesA, this);

    if (mKeyFrameX.Count() != 0) {
        mKeyFrameX.IncrementCurrentFrame();
    }

    if (mKeyFrameY.Count() != 0) {
        mKeyFrameY.IncrementCurrentFrame();
    }

    if (mKeyFrameZ.Count() != 0) {
        mKeyFrameZ.IncrementCurrentFrame();
    }

    nw4r::math::VEC3 keyFramesB;
    GetKeyFrames(keyFramesB, this);
    mCurrentKeyFrames = keyFramesB;
    
    if (!mSpringTemplate->m_41) {
        return;
    }
    
    if (VEC3LenSq(&mCurrentKeyFrames) > 0.0f) {
        bool unk = false;

        if (VEC3LenSq(&keyFramesA) == 0.0f) {
            unk = true;
        } else {
            float angle = VecAngle(keyFramesA, mCurrentKeyFrames);
            
            if (180.0f * (angle / NW4R_MATH_PI) > 10.0f) {
                unk = true;
            }
        }

        if (unk) {
            mParticleEffectMultiplier = mCurrentKeyFrames;
            VEC3Normalize(&mParticleEffectMultiplier, &mParticleEffectMultiplier);
            m_144 = m_134 + VEC3Len(&m_128);
        }
    }

    if (VEC3LenSq(&mCurrentKeyFrames) > 0.0f) {
        m_148 = 0.001f * VEC3Len(&mCurrentKeyFrames);
    }
}

// no idea what tu this belongs to
bool fn_80012914(
    float,
    nw4r::math::VEC3&,
    nw4r::math::VEC3&,
    nw4r::math::VEC3&,
    nw4r::math::VEC3&,
    float*
);

using nw4r::math::VEC3;

// https://decomp.me/scratch/XCrDu
void SpringBase::vf74(float scale, Particle* pParticle, nw4r::math::VEC3& rVec) {
    nw4r::math::VEC3 vec1;
    
    vec1.x = 0.0f;
    vec1.y = 1.0f;
    vec1.z = 0.0f;
    
    nw4r::math::VEC3 vec2;
    nw4r::math::VEC3 vec3;

    ClearVec(vec2);
    VEC3Add(&vec2, &mPosition, &pParticle->mEffectPosition);
    ClearVec(vec3);
    
    VEC3 vec4;
    VEC3 vec5;
    VEC3 vec6;
    VEC3 vec7;
    VEC3 vec8;
    VEC3 vec9;

    bool unk = fn_80012914(0.0f, rVec, vec2, vec1, vec3, nullptr);
    
    if (!unk) {
        return;
    }
    
    ClearVec(vec4);
    // ClearVec(vec5);
    // ClearVec(vec6);
        
    float dot = VEC3Dot(&pParticle->m_4, &vec1);

    VEC3Scale(&vec4, &vec1, dot);

    vec5.x = -vec4.x;
    vec5.y = -vec4.y;
    vec5.z = -vec4.z;

    VEC3Sub(&vec6, &pParticle->m_4, &vec4);
    VEC3Scale(&vec7, &vec5, 0.5f);
    VEC3Scale(&vec8, &vec7, 0.8f);
    VEC3Add(&vec9, &vec6, &vec8);
    
    pParticle->m_4 = vec9;

    
    // VEC
    // (pParticle->m_4).x = -(vec1.x * dot) * f0.5 + ((pParticle->m_4).x - vec1.x * dot) * f0.8;


    VEC3 t;
    VEC3Scale(&t, &pParticle->m_4, scale);
    rVec = t;
}

void SpringBase::fn_8000B6BC() {
    for (uint i = 0; i < GetParticleCount(); i++) {
        Particle* particle = &mParticleArray1[i];
        particle->m_4 = nw4r::math::VEC3(0.0f, 0.0f, 0.0f);
    }
}

bool SpringBase::fn_8000B74C() {
    mParticleArray1 = new (gfl::HeapID::Work) Particle[mSpringTemplate->mParticleCount];

    if (mParticleArray1 == nullptr) {
        return false;
    } else {
        
        if (mSpringTemplate->m_24 == 1) {
            CreateParticleArrays();
        }
        
        mSpringArray = new (gfl::HeapID::Work) Spring[mSpringTemplate->mSpringCount];
    
        // is an inline involved? it doesn't make sense to
        // check the spring template for nullptr after it was used

        if (mSpringArray == nullptr) {
            return false;
        }
        
        if (mSpringTemplate != nullptr) {
            for (uint i = 0; i < GetParticleCount(); i++) {
                Particle* particle = &mParticleArray1[i];
                particle->CopyVec(gfl::Vec3::Zero);
                particle->m_0 = mSpringTemplate->m_0;
            }
            
            SetParticlesInvalid(false);
        }
    }

    return true;
}

bool SpringBase::fn_8000B888(float mag, nw4r::math::VEC3& rArg2, const nw4r::math::VEC3& rArg3) {
    nw4r::math::VEC3 vec1;
    nw4r::math::VEC3 vec3;
    nw4r::math::VEC3 vec2;
    
    ClearVec(vec1);
    
    VEC3Sub(&vec1, &rArg3, &rArg2);
    
    if (PSVECMag(vec1) <= mag) {
        rArg2 = rArg3;
        return true;
    } else {
        VEC3Normalize(&vec1, &vec1);

        ClearVec(vec2);
        
        VEC3Scale(&vec1, &vec1, mag);
        
        VEC3Add(&vec2, &rArg2, &vec1);
        
        rArg2 = vec2;
        
        ClearVec(vec3);
        
        VEC3Sub(&vec3, &rArg3, &rArg2);

        float dot = VEC3Dot_(&vec3, &vec1);
        
        if (dot < 0.0f || PSVECMag(vec3) < mag) {
            rArg2 = rArg3;
            return true;
        }
    }

    return false;
}

// https://decomp.me/scratch/Hb6IE
void SpringBase::LoadDefaultKeyFrames() {
    KeyFrame<float>::FrameTemplate ftX, ftY, ftZ;

    ftX = SpringBase_FrameTemplateX;
    ftY = SpringBase_FrameTemplateY;
    ftZ = SpringBase_FrameTemplateZ;

    ResetKeyFrames(&ftX, &ftY, &ftZ);
}

void SpringBase::vf7C(Particle* pParticles) {
    if (m_14C == nullptr) {
        return;
    }

    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        UnkStruct2* s = &m_14C[i];
        Particle* particle = &pParticles[i];
        
        if (s->m_C == 0) {
            continue;
        }

        particle->m_34 += s->m_0;
    }
}

void SpringBase::fn_8000BB50() {
    if (m_14C == nullptr) {
        return;
    }

    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        if (m_14C[i].m_C != 0) {
            m_14C[i].m_C--;
        }

        UnkStruct2* s = &m_14C[i];
        
        if (s->m_C == 0) {
            s->m_0 = gfl::Vec3::Zero;
        }
    }
}

void SpringBase::CreateParticleArrays() {
    for (uint i = 0; i < 4; i++) {
        Particle** arr = &mParticleArray2;
        arr[i] = new (gfl::HeapID::Work) Particle[mSpringTemplate->mParticleCount];
    }
}


/* FlfGameObj */

void FlfGameObj::vf64(bool) { }

float FlfGameObj::GetCullThreshold() {
    return mCullThreshold;
}

void FlfGameObj::SetCullThreshold(float thresh) {
    mCullThreshold = thresh;
}

void FlfGameObj::vf58() { }

bool FlfGameObj::vf54() {
    return m_7D;
}

void FlfGameObj::vf50(bool arg1) {
    m_7D = arg1;
}

void FlfGameObj::SetState(FlfGameObj* pSetter, std::string& rState) { }

int FlfGameObj::vf44() {
    return 1;
}

void FlfGameObj::vf40(FlfGameObj*) { }

int FlfGameObj::vf3C() {
    return 0;
}

ScreenPosition FlfGameObj::GetScreenPosition() {
    ScreenPosition pos;
    pos.mPosition.x = 0.0f;
    pos.mPosition.y = 0.0f;
    pos.mPosition = &mPosition.x;
    pos.mCullThreshold = mCullThreshold;
    return pos;
}

void FlfGameObj::vf30() { }

void FlfGameObj::vf2C(
    nw4r::math::VEC3& rArg1,
    const nw4r::math::VEC3& rOffset,
    nw4r::math::VEC3* pDst
) {
    if (m_6F) {
        return;
    }

    nw4r::math::VEC3 pos;
    pos = mPosition;
    pos += rOffset;
    SetPosition(pos);

    if (pDst != nullptr) {
        *pDst = rOffset;
    }
}

void FlfGameObj::SetPosition(const nw4r::math::VEC3& rPosition) {
    mPosition = rPosition;
}

void FlfGameObj::vf28() { }

void FlfGameObj::Interact(FlfGameObj* pOther) { }

void FlfGameObj::SetSecondaryPosition(const nw4r::math::VEC3& rPosition) {
    FlfGameObj::SetPosition(rPosition);
}

nw4r::math::VEC3 FlfGameObj::GetPosition() {
    nw4r::math::VEC3 pos;
    pos = mPosition;
    return pos;
}

float SpringBase::GetZPos() {
    return mPosition.z;
}

/* KeyFrame */

template <>
void KeyFrame<float>::Add(float start, float end, const char* pName) {
    size_t count = Count();
    if (count != 0) {
        AddNew(start, end + mInnerKeyFrames[count - 1].mEnd, pName);
    } else {
        AddNew(start, end, pName);
    }
}

template <>
float KeyFrame<float>::GetFrame(std::string* pName) {
    return CalculateFrame(mCurrentFrame, pName);
}

// not complete
template <>
float KeyFrame<float>::CalculateFrame(float frame, std::string* pName) {
    float newFrame;

    if (mHasFrames && GetPreviousEndFrame() < frame) {
        float prev = GetPreviousEndFrame();
        uint unk = static_cast<unsigned int>(frame / prev);
        newFrame = static_cast<float>(unk);
    }

    size_t count = Count();
    size_t i = count;
    while (true) {
        if (i == 0) {
            if (pName != nullptr) {
                *pName = mInnerKeyFrames[count - 1].mName;
            }

            return mInnerKeyFrames[Count() - 1].mStart;
        }
    }
}

template <>
void KeyFrame<float>::IncrementCurrentFrame(float amt) {
    float prevEnd;
    float total = mCurrentFrame + amt;
    mCurrentFrame = total;

    if (!mHasFrames) {
        return;
    }

    prevEnd = mInnerKeyFrames[Count() - 1].mEnd;

    if (total > prevEnd) {
        mCurrentFrame = total - prevEnd;
    }
}

// todo: move these to the header

template <>
float KeyFrame<float>::GetPreviousEndFrame() {
    return mInnerKeyFrames[Count() - 1].mEnd;
}

template <>
void KeyFrame<float>::GetNextStartFrame(float mult, uint index, InnerKeyFrame* pDst) {
    InnerKeyFrame* frames = mInnerKeyFrames.data();
    float cur = frames[index].mStart;
    float delta = frames[index + 1].mStart - frames[index].mStart;
    pDst->mStart = frames[index].mStart + delta * mult;
}

// https://decomp.me/scratch/aNK5Z
template <>
void KeyFrame<float>::AddNew(float start, float end, const char* pName) {
    std::string name;

    if (pName != nullptr) {
        name = pName;
    }

    InnerKeyFrame inner(start, end, name);

    size_t count = Count();

    if (count < mInnerKeyFrames.capacity()) {
        InnerKeyFrame* last = &mInnerKeyFrames[count];

        if (last != nullptr) {
            *last = inner;
        }
    } else {
        mInnerKeyFrames.insert(inner);
    }
}