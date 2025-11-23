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
    : m_28(0.0f)
    , m_60(0.0f)
{
    m_0 = 0.0f;
    m_4 = gfl::Vec3(0.0f);
    mEffectPosition = gfl::Vec3(0.0f);
    mPosition = gfl::Vec3(0.0f);
    m_34 = gfl::Vec3(0.0f);
    mInvalid = false;
    m_44 = nullptr;
    m_48 = gfl::Vec3(0.0f);
    m_54 = gfl::Vec3(0.0f);
}

SpringBase::Particle::~Particle() {
    if (m_44 != nullptr) {
        m_44->Destroy();
    }
}

void SpringBase::Particle::CopyVec(const gfl::Vec3& rSrc) {
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
    , mCurrentKeyFrames(0.0f)
    , m_11C(0.0f)
    , m_128(0.0f)
    , mParticleEffectMultiplier(0.0f)
{
    m_14C = nullptr;
    m_9C = arg1;
    mParticleArray1 = nullptr;
    mParticleArray2 = nullptr;
    mParticleArray3 = nullptr;
    mParticleArray4 = nullptr;
    mParticleArray5 = nullptr;
    mSpringArray = nullptr;
    mPosition = gfl::Vec3(0.0f);
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

void SpringBase::SetParticleEffectPositionByIndex(uint index, gfl::Vec3& rVec, bool syncPos) {
    mParticleArray1[index].mEffectPosition = rVec;
    if (syncPos) {
        mParticleArray1[index].mPosition = rVec;
    }
}

gfl::Vec3 SpringBase::GetParticleEffectPositionByIndex(uint index) {
    gfl::Vec3 vec = mParticleArray1[index].mEffectPosition;
    return vec;
}

void SpringBase::OffsetParticleEffectPositionByIndex(uint index, gfl::Vec3& rOffset, bool syncPos) {
    Particle* particle = &mParticleArray1[index];

    particle->mEffectPosition = rOffset - mPosition;
    
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

gfl::Vec3 SpringBase::GetParticleEffectOffsetByIndex(uint index) {
    return GetParticleEffectPositionByIndex(index) + mPosition;
}

gfl::Vec3 SpringBase::fn_80008908(uint index) {
    gfl::Vec3 vec = mParticleArray1[index].m_54;
    return vec;
}

gfl::Vec3 SpringBase::fn_80008930(uint index) {
    gfl::Vec3 offs = fn_80008908(index);
    return offs + mPosition;
}

void SpringBase::fn_800089A0() {
    if (m_14C == nullptr) {
        m_14C = new (gfl::HeapID::Work) UnkStruct2[mSpringTemplate->mParticleCount];
        fn_8000BB50();
    }
}

SpringBase::UnkStruct2::UnkStruct2()
    : m_0(0.0f)
    , m_C(0)
{ }

void SpringBase::fn_80008A34(uint index, const gfl::Vec3& rVec, int arg3) {
    m_14C[index].m_0 = rVec;
    m_14C[index].m_C = arg3;
}

void SpringBase::fn_80008A68(gfl::Vec3& rVec, int arg2) {
    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        fn_80008A34(i, rVec, arg2);
    }
}

gfl::Vec3 SpringBase::GetKeyFrames() {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    if (mKeyFrameX.mInnerKeyFrames.size() != 0) {
        x = mKeyFrameX.GetFrame(nullptr);
    }

    if (mKeyFrameY.mInnerKeyFrames.size() != 0) {
        y = mKeyFrameY.GetFrame(nullptr);
    }

    if (mKeyFrameZ.mInnerKeyFrames.size() != 0) {
        z = mKeyFrameZ.GetFrame(nullptr);
    }

    gfl::Vec3 ret;
    ret.x = x;
    ret.y = y;
    ret.z = z;
    return ret;
}


void SpringBase::fn_80008BB0(nw4r::math::MTX34& rMtx) {
    PSMTXIdentity(rMtx);
    
    gfl::Vec3 offs0 = GetParticleEffectOffsetByIndex(0);
    gfl::Vec3 offs = offs0 - GetParticleEffectOffsetByIndex(1);


    gfl::Vec3 unk;
    unk.x = 0.0f;
    unk.y = -1.0f;
    unk.z = 0.0f;

    float angle = 0.0f;
    if (!offs.IsInvalid()) {
        angle = gfl::Vec3::AngleRad(offs, unk);
    }

    gfl::Vec3 cross = gfl::Vec3::Cross(unk, offs);

    angle *= cross.z >= 0.0f ? 1.0f : -1.0f;
    
    MTX34RotXYZRad(&rMtx, 0.0f, 0.0f, angle);
    
    rMtx[0][3] = offs0.x;
    rMtx[1][3] = offs0.y;
    rMtx[2][3] = offs0.z;
}

void SpringBase::fn_80008DC0(nw4r::math::MTX34& rMtx) {
    PSMTXIdentity(rMtx);
    
    gfl::Vec3 offs0 = GetParticleEffectOffsetByIndex(mSpringTemplate->mParticleCount - 1);
    gfl::Vec3 offs = offs0 - GetParticleEffectOffsetByIndex(mSpringTemplate->mParticleCount - 2);
    offs.z = 0.0f;
    
    gfl::Vec3 unk;
    unk.x = 0.0f;
    unk.y = -1.0f;
    unk.z = 0.0f;

    float angle = 0.0f;
    if (!offs.IsInvalid()) {
        angle = gfl::Vec3::AngleRad(offs, unk);
    }

    gfl::Vec3 cross = gfl::Vec3::Cross(unk, offs);

    angle *= cross.z >= 0.0f ? 1.0f : -1.0f;
    
    MTX34RotXYZRad(&rMtx, 0.0f, 0.0f, angle);
    
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

void SpringBase::fn_80009284(gfl::Vec3& rVec) {
    mSpringTemplate->m_18 = rVec;
}

void SpringBase::fn_800092A4() {
    fn_80009568(mSpringTemplate);
}

void SpringBase::fn_800092AC(float scale) {
    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        mParticleArray1[i].m_28 = mParticleArray1[i].mEffectPosition;
    }

    if (mSpringTemplate->m_41) {
        for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
            Particle* particle = &mParticleArray1[i];
            float dot = gfl::Vec3::Dot2(particle->mEffectPosition, mParticleEffectMultiplier);

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

void SpringBase::vf78(float, Particle*, gfl::Vec3&) { }

void SpringBase::fn_80009568(SpringTemplate* pSpringTemplate) {
    for (uint i = 0; i < pSpringTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray1[i];
        particle->m_34 = gfl::Vec3(0.0f);
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

// https://decomp.me/scratch/mPqdv
void SpringBase::fn_80009678(float scale) {
    SpringTemplate* st = mSpringTemplate;

    CopyParticles(mParticleArray1, mParticleArray2, st);

    fn_8000A748(mParticleArray2);

    for (uint i = 0; i < st->mParticleCount; i++) {
        Particle* particle = &mParticleArray2[i];
        float rate = 1.0f / particle->m_0;
        particle->m_48 = particle->m_34 * rate * scale;
    }

    CopyParticles(mParticleArray2, mParticleArray3, st);

    for (uint i = 0; i < st->mParticleCount; i++) {
        Particle* pa = &mParticleArray2[i];
        Particle* pb = &mParticleArray3[i];

        pb->m_4 += pa->m_48 * scale * 0.5f;
        pb->mEffectPosition += pb->m_4 * scale * 0.5f;
    }

    
    fn_8000A748(mParticleArray3);

    for (uint i = 0; i < st->mParticleCount; i++) {
        Particle* particle = &mParticleArray3[i];
        float rate = 1.0f / particle->m_0;
        particle->m_48 = particle->m_34 * rate * scale;
    }

    CopyParticles(mParticleArray2, mParticleArray4, st);


    for (uint i = 0; i < st->mParticleCount; i++) {
        Particle* pa = &mParticleArray3[i];
        Particle* pb = &mParticleArray4[i];
        
        pb->m_4 += pa->m_48 * scale * 0.5f;
        pb->mEffectPosition += pb->m_4 * scale * 0.5f;
    }

    fn_8000A748(mParticleArray4);
    
    for (uint i = 0; i < mSpringTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray4[i];
        float rate = 1.0f / particle->m_0;
        particle->m_48 = particle->m_34 * rate * scale;
    }

    CopyParticles(mParticleArray2, mParticleArray5, st);

    for (uint i = 0; i < st->mParticleCount; i++) {
        Particle* pa = &mParticleArray4[i];
        Particle* pb = &mParticleArray5[i];
        
        pb->m_4 += pa->m_48 * scale;
        pb->mEffectPosition += pb->m_4 * scale;
    }
    
    fn_8000A748(mParticleArray5);


    for (uint i = 0; i < st->mParticleCount; i++) {
        Particle* particle = &mParticleArray5[i];
        float rate = 1.0f / particle->m_0;
        particle->m_48 = particle->m_34 * rate * scale;
    }

    for (uint i = 0; i < st->mParticleCount; i++) {
        float one = 1.0f;
        Particle* p1 = &mParticleArray1[i];

        if (p1->mInvalid) {
            continue;
        }

        Particle* p2 = &mParticleArray2[i];
        Particle* p3 = &mParticleArray3[i];
        Particle* p4 = &mParticleArray4[i];
        Particle* p5 = &mParticleArray5[i];

        float rate = one / 6.0f; // this has to be calculated dynamically
        p1->m_4 += (p2->m_48 + p3->m_48 * 2.0f + p4->m_48 * 2.0f + p5->m_48) * rate;
        p1->m_60 = p1->m_4 * scale;
    }
}

void SpringBase::fn_80009E28(float scale) {
    SpringTemplate* springTemplate = mSpringTemplate;
    
    fn_8000A748(mParticleArray1);

    
    for (uint i = 0; i < springTemplate->mParticleCount; i++) {
        Particle* particle = &mParticleArray1[i];

        if (particle->mInvalid) {
            continue;
        }

        float rate = 1.0f / particle->m_0;

        gfl::Vec3 temp = particle->m_34 * rate * scale;
        particle->m_4 += temp;
        particle->m_60 = particle->m_4 * scale;
    }
}

// https://decomp.me/scratch/m730M
void SpringBase::fn_80009F64(float scale) {
    SpringTemplate* st = mSpringTemplate;
    
    fn_8000A748(mParticleArray1);

    for (uint i = 0; i < st->mParticleCount; i++) {
        Particle* particle = &mParticleArray1[i];

        if (particle->mInvalid) {
            continue;
        }
        
        float rate = 1.0f / particle->m_0;
        
        gfl::Vec3 temp1 = particle->m_34 * rate * scale;
        particle->m_4 += temp1;

        rate = 1.0f / particle->m_0;

        gfl::Vec3 v3 = particle->mEffectPosition - particle->mPosition;
        gfl::Vec3 v7 = v3 + particle->m_34 * rate * scale * scale;
        particle->m_60 = v7;
    }
}


// https://decomp.me/scratch/rYtUO
void SpringBase::fn_8000A148(float scale) {
    SpringTemplate* st = mSpringTemplate;
    
    fn_8000AC6C(mParticleArray1);
    
    float unk1 = (100.0f - st->mPercentage) * 0.01f;
    
    for (uint i = 0; i < st->mParticleCount; i++) {
        Particle* particle = &mParticleArray1[i];

        if (particle->mInvalid) {
            continue;
        }
    
        float rate = 1.0f / particle->m_0;
        particle->m_60 = (particle->mEffectPosition - particle->mPosition) * unk1 + particle->m_34 * rate * scale * scale;
    }

    for (uint i = 0; i < st->mParticleCount; i++) {
        mParticleArray1[i].m_6D = false;
    }

    for (uint i = 0; i < mSpringTemplate->mSpringCount; i++) {
        Spring* spring = &mSpringArray[i];

        if (spring->m_10 < 1.0f) {
            continue;
        }

        Particle* p1 = &mParticleArray1[spring->mParticleIndex1];
        Particle* p2 = &mParticleArray1[spring->mParticleIndex2];

        if (!p1->mInvalid || !p2->mInvalid) {
            gfl::Vec3 temp = (p2->mEffectPosition + p2->m_60) - (p1->mEffectPosition + p1->m_60);

            float unk2;

                
            if (temp.IsInvalid()) {
                gfl::Vec3(0.0f); // not used?
                temp.x = unk1;
                temp.y = -1.0f;
                temp.z = unk1;

                unk2 = 0.0f;
            } else {
                unk2 = temp.Length();
                temp *= 1.0f / unk2;
            }
            

            float unk3 = -(spring->m_8 * spring->m_10 - unk2);

            if (0.0f > unk3) {

                gfl::Vec3(0.0f);
                gfl::Vec3 temp2 = temp * unk3 * 0.5f;
                
                if (p1->mInvalid || p2->mInvalid) {
                    temp2 *= 2.0f;
                }
                
    
                if (!p1->mInvalid) {
                    gfl::Vec3 a = p1->mEffectPosition + p1->m_60 + temp2;
                    p1->m_60 = a - p1->mEffectPosition;
                }
                
                if (!p2->mInvalid) {
                    p2->m_60 = (p2->mEffectPosition + p2->m_60 + temp2) - p2->mEffectPosition;
                }
            }
        }
    }
}

// https://decomp.me/scratch/jpA3V
void SpringBase::fn_8000A748(Particle* pParticles) {
    SpringTemplate* st = mSpringTemplate;

    for (uint i = 0; i < st->mParticleCount; i++) {
        Particle* particle = &pParticles[i];

        if (particle->mInvalid) {
            continue;
        }

        particle->m_34 -= st->m_18 * particle->m_0;
        particle->m_34 -= particle->m_4 * st->m_14;

        if (particle->m_6C) {
            particle->m_34 += mCurrentKeyFrames;
        }
    }


    if (st->m_44 > 0.0f) {
        for (uint i = 0; i < st->mParticleCount; i++) {
            Particle* particle = &pParticles[i];

            gfl::Vec3 temp = particle->m_54 - particle->mEffectPosition;

            if (st->m_48 > 0.0f) {
                float mag = temp.Length();
                float unk = 1.0f / st->m_48;

                temp = temp * mag * unk;
            }

            if (temp.IsInvalid()) {
                temp.Normalize();
                particle->m_34 += temp * st->m_44;
            }
        }
    }

    vf7C(pParticles);

    for (uint i = 0; i < st->mSpringCount; i++) {
        Spring* spring = &mSpringArray[i];

        Particle* p1 = &pParticles[spring->mParticleIndex1];
        Particle* p2 = &pParticles[spring->mParticleIndex2];

        gfl::Vec3 diff = p1->mEffectPosition - p2->mEffectPosition;

        float mag = diff.Length();

        if (mag <= 0.0f) {
            gfl::Vec3 temp1(0.0f);
            gfl::Vec3::Normalize(diff, temp1);
            float rate = 1.0f / mag;

            gfl::Vec3 temp2 = p1->m_4 - p2->m_4;
            
            float dot = gfl::Vec3::Dot1(temp2, diff);

            float unk = -(
                st->m_4[spring->mActiveParticleIndex] *
                mag - spring->m_8 *
                st->mPercentage *
                dot / mag
            );

            gfl::Vec3 temp3 = diff * unk * rate;
            
            if (!p1->mInvalid) {
                p1->m_34 += temp3;
            }

            if (!p2->mInvalid) {
                p2->m_34 += -temp3;
            }
        }
    }
}

// https://decomp.me/scratch/oMrll
void SpringBase::fn_8000AC6C(Particle* pParticles) {
    SpringTemplate* st = mSpringTemplate;
    
    for (uint i = 0; i < st->mParticleCount; i++) {
        Particle* particle = &pParticles[i];

        if (particle->mInvalid) {
            continue;
        }
 
        particle->m_34 -= st->m_18 * particle->m_0;
        gfl::Vec3 t2 = particle->mEffectPosition - particle->mPosition;
        particle->m_34 -= t2 * st->m_14;

        if (particle->m_6C) {
            particle->m_34 += mCurrentKeyFrames;
        }
    }

    if (st->m_44 > 0.0f) {
        for (uint i = 0; i < st->mParticleCount; i++) {
            Particle* particle = &pParticles[i];

            gfl::Vec3 temp = particle->m_54 - particle->mEffectPosition;

            if (st->m_48 > 0.0f) {
                float mag = temp.Length();
                float unk = 1.0f / st->m_48;
                
                temp = temp * mag * unk;
            }

            if (!temp.IsInvalid()) {
                temp.Normalize();
                particle->m_34 += temp * st->m_44;
            }
        }
    }

    vf7C(pParticles);

    for (uint i = 0; i < st->mSpringCount; i++) {
        Spring* spring = &mSpringArray[i];

        Particle* p1 = &pParticles[spring->mParticleIndex1];
        Particle* p2 = &pParticles[spring->mParticleIndex2];

        if (!p1->mInvalid || !p2->mInvalid) {
            gfl::Vec3 diff = p1->mEffectPosition - p2->mEffectPosition;
            
            gfl::Vec3(0.0f); // not used?
            float mag = diff.Length();
                
            if (mag <= 0.0f) {
                continue;
            }
            
            gfl::Vec3 zero(0.0f);
            gfl::Vec3::Normalize(diff, zero);

            float rate = 1.0f / mag;
            
            float unk = -(
                st->m_4[spring->mActiveParticleIndex] *
                (mag - spring->m_8)
            );

            gfl::Vec3 temp = diff * unk * rate;

            if (!p1->mInvalid) {
                p1->m_34 += temp;
            }

            if (!p2->mInvalid) {
                p2->m_34 += -temp;
            }
        }
    }
}

void SpringBase::CopyParticles(Particle* pSrc, Particle* pDst, SpringTemplate* pSpringTemplate) {
    for (uint i = 0; i < pSpringTemplate->mParticleCount; i++) {
        pDst[i] = pSrc[i];
        pDst[i].m_44 = nullptr;
    }
}

void SpringBase::fn_8000B270() {
    gfl::Vec3 keyFrames = GetKeyFrames();

    if (mKeyFrameX.Count() != 0) {
        mKeyFrameX.IncrementCurrentFrame();
    }

    if (mKeyFrameY.Count() != 0) {
        mKeyFrameY.IncrementCurrentFrame();
    }

    if (mKeyFrameZ.Count() != 0) {
        mKeyFrameZ.IncrementCurrentFrame();
    }

    mCurrentKeyFrames = GetKeyFrames();

    if (!mSpringTemplate->m_41) {
        return;
    }
    
    if (VEC3LenSq(&mCurrentKeyFrames) > 0.0f) {
        bool unk = false;

        if (VEC3LenSq(&keyFrames) == 0.0f) {
            unk = true;
        } else {
            float rad = gfl::Vec3::AngleRad(keyFrames, mCurrentKeyFrames);
            float degrees = 180.0f * (rad / NW4R_MATH_PI);
            if (degrees > 10.0f) {
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
    gfl::Vec3&,
    gfl::Vec3&,
    gfl::Vec3&,
    gfl::Vec3&,
    float*
);

using gfl::Vec3;

// https://decomp.me/scratch/94H5I
void SpringBase::vf74(float scale, Particle* pParticle, gfl::Vec3& rVec) {
    gfl::Vec3 v1(0.0f);
    v1.y = 1.0f;

    gfl::Vec3 v2 = mPosition + pParticle->mEffectPosition;
    gfl::Vec3 v3(0.0f);

    if (!fn_80012914(0.0f, rVec, v2, v1, v3, nullptr)) {
        return;
    }

    float dot = VEC3Dot(&pParticle->m_4, &v1);

    gfl::Vec3 temp1 = -(v1 * dot) * 0.5f;
    gfl::Vec3 temp2 = (pParticle->m_4 - v1 * dot) * 0.8f;
    // temp1 *= 0.8f;
    // temp2 *= 0.5f;
    
    pParticle->m_4 = temp1 + temp2;

    rVec = pParticle->m_4 * scale;
}

void SpringBase::fn_8000B6BC() {
    for (uint i = 0; i < GetParticleCount(); i++) {
        Particle* particle = &mParticleArray1[i];
        particle->m_4 = gfl::Vec3(0.0f);
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

bool SpringBase::fn_8000B888(float mag, gfl::Vec3& rArg2, const gfl::Vec3& rArg3) {
    gfl::Vec3 v1 = rArg3 - rArg2;

    if (v1.Length() <= mag) {
        rArg2 = rArg3;
        return true;
    } else {
        v1.Normalize();
        v1 *= mag;

        rArg2 = rArg2 + v1;

        gfl::Vec3 v3 = rArg3 - rArg2;

        if (gfl::Vec3::Dot1(v3, v1) < 0.0f || v3.Length() < mag) {
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

/*  all of the below should be defined in headers as they're weak functions that
    got emitted in this TU
*/

/* FlfGameObj */

// void FlfGameObj::vf64(bool) { }

// float FlfGameObj::GetCullThreshold() {
//     return mCullThreshold;
// }

// void FlfGameObj::SetCullThreshold(float thresh) {
//     mCullThreshold = thresh;
// }

// void FlfGameObj::vf58() { }

// bool FlfGameObj::vf54() {
//     return m_7D;
// }

// void FlfGameObj::vf50(bool arg1) {
//     m_7D = arg1;
// }

// void FlfGameObj::SetState(FlfGameObj* pSetter, std::string& rState) { }

// int FlfGameObj::vf44() {
//     return 1;
// }

// void FlfGameObj::vf40(FlfGameObj*) { }

// int FlfGameObj::vf3C() {
//     return 0;
// }

// ScreenPosition FlfGameObj::GetScreenPosition() {
//     ScreenPosition pos;
//     pos.mPosition.x = 0.0f;
//     pos.mPosition.y = 0.0f;
//     pos.mPosition = &mPosition.x;
//     pos.mCullThreshold = mCullThreshold;
//     return pos;
// }

// void FlfGameObj::vf30() { }

// void FlfGameObj::vf2C(
//     gfl::Vec3& rArg1,
//     const gfl::Vec3& rOffset,
//     gfl::Vec3* pDst
// ) {
//     if (m_6F) {
//         return;
//     }

//     gfl::Vec3 pos;
//     pos = mPosition;
//     pos += rOffset;
//     SetPosition(pos);

//     if (pDst != nullptr) {
//         *pDst = rOffset;
//     }
// }

// void FlfGameObj::SetPosition(const gfl::Vec3& rPosition) {
//     mPosition = rPosition;
// }

// void FlfGameObj::vf28() { }

// void FlfGameObj::Interact(FlfGameObj* pOther) { }

// void FlfGameObj::SetSecondaryPosition(const gfl::Vec3& rPosition) {
//     FlfGameObj::SetPosition(rPosition);
// }

// gfl::Vec3 FlfGameObj::GetPosition() {
//     gfl::Vec3 pos;
//     pos = mPosition;
//     return pos;
// }

// float SpringBase::GetZPos() {
//     return mPosition.z;
// }

// todo: move these to the header

/* KeyFrame */

// template <>
// void KeyFrame<float>::Add(float start, float end, const char* pName) {
//     size_t count = Count();
//     if (count != 0) {
//         AddNew(start, end + mInnerKeyFrames[count - 1].mEnd, pName);
//     } else {
//         AddNew(start, end, pName);
//     }
// }

// template <>
// float KeyFrame<float>::GetFrame(std::string* pName) {
//     return CalculateFrame(mCurrentFrame, pName);
// }

// // not complete
// template <>
// float KeyFrame<float>::CalculateFrame(float frame, std::string* pName) {
//     float newFrame;

//     if (mHasFrames && GetPreviousEndFrame() < frame) {
//         float prev = GetPreviousEndFrame();
//         uint unk = static_cast<unsigned int>(frame / prev);
//         newFrame = static_cast<float>(unk);
//     }

//     size_t count = Count();
//     size_t i = count;
//     while (true) {
//         if (i == 0) {
//             if (pName != nullptr) {
//                 *pName = mInnerKeyFrames[count - 1].mName;
//             }

//             return mInnerKeyFrames[Count() - 1].mStart;
//         }
//     }
// }

// template <>
// void KeyFrame<float>::IncrementCurrentFrame(float amt) {
//     float prevEnd;
//     float total = mCurrentFrame + amt;
//     mCurrentFrame = total;

//     if (!mHasFrames) {
//         return;
//     }

//     prevEnd = mInnerKeyFrames[Count() - 1].mEnd;

//     if (total > prevEnd) {
//         mCurrentFrame = total - prevEnd;
//     }
// }


// template <>
// float KeyFrame<float>::GetPreviousEndFrame() {
//     return mInnerKeyFrames[Count() - 1].mEnd;
// }

// template <>
// void KeyFrame<float>::GetNextStartFrame(float mult, uint index, InnerKeyFrame* pDst) {
//     InnerKeyFrame* frames = mInnerKeyFrames.data();
//     float cur = frames[index].mStart;
//     float delta = frames[index + 1].mStart - frames[index].mStart;
//     pDst->mStart = frames[index].mStart + delta * mult;
// }

// // https://decomp.me/scratch/aNK5Z
// template <>
// void KeyFrame<float>::AddNew(float start, float end, const char* pName) {
//     std::string name;

//     if (pName != nullptr) {
//         name = pName;
//     }

//     InnerKeyFrame inner;
//     inner.mStart = start;
//     inner.mEnd = end;
//     inner.mName = std::string(name);
    
//     mInnerKeyFrames.push_back_(inner);
// }
