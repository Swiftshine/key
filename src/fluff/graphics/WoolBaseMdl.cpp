#include "graphics/WoolBaseMdl.h"

WoolBaseMdl::WoolBaseMdl(
    FullSortScene* pScene,
    WoolBaseTask* pTask,
    int arg3,
    gfl::ResFileObject& rResFileObject,
    const char* pWoolName1,
    const char* pWoolName2,
    int arg6,
    const char* pName
)
    : CustomRenderObj(false, true, pName)
    , mHermiteCurve()
    , m_128(1.0f)
    , m_134(0.0f)
    , mBackupBuffs()
    , m_150(0)
    , m_154(0)
    , m_158(false)
    , m_15C(0)
{
    mWoolBaseTask = pTask;
    m_108 = true;
    m_10C = arg3;
    mFlfWoolDraw = nullptr;

    pScene->AddRenderObj(static_cast<gfl::RenderObj*>(this));
    
    mHermiteCurve.fn_806602EC(mWoolBaseTask->mSpringTemplate->mParticleCount);

    mFlfWoolDraw = new (gfl::HeapID::Work) FlfWoolDraw;

    int index = mFlfWoolDraw->Register(&rResFileObject, pWoolName1, pWoolName2);

    uint count = mWoolBaseTask->mSpringTemplate->mParticleCount;
    mFlfWoolDraw->fn_800267B0(index, count + m_10C * (count - 1));
    mFlfWoolDraw->m_18 = 1.0f;
    fn_8001AA00(1.0f);
    fn_8001AB58();
}

const char wool_string_template[] = "wool_%02d";

WoolBaseMdl::WoolBaseMdl(
    FullSortScene* pScene,
    WoolBaseTask* pTask,
    int arg3,
    gfl::ResFileObject& rResFileObject,
    const char* pName
)
    : CustomRenderObj(false, true, pName)
    , mHermiteCurve()
    , m_128(1.0f)
    , m_134(0.0f)
    , mBackupBuffs()
    , m_150(0)
    , m_154(0)
    , m_158(false)
{
    mWoolBaseTask = pTask;
    m_108 = true;
    m_10C = arg3;
    mFlfWoolDraw = nullptr;

    pScene->AddRenderObj(static_cast<gfl::RenderObj*>(this));
    
    mHermiteCurve.fn_806602EC(mWoolBaseTask->mSpringTemplate->mParticleCount);

    mFlfWoolDraw = new (gfl::HeapID::Work) FlfWoolDraw;
    
    int index = -1;
    int idx = 0;

    for (uint i = 0; i < 0x40; i++) {
        char name[0x20];
        sprintf(name, "C8_wool_%02d", i);
        idx = mFlfWoolDraw->Register(&rResFileObject, name, name);

        if (i == 0) {
            index = idx;
        }

        if (idx < 0) {
            break;
        }
    }

    if (index < 0) {
        for (uint i = 0; i < 0x40; i++) {
            char name[0x20];
            sprintf(name, wool_string_template, i);
            idx = mFlfWoolDraw->Register(&rResFileObject, name, name);

            if (i == 0) {
                index = idx;
            }

            if (idx < 0) {
                break;
            }
        }
    }

    uint count = mWoolBaseTask->mSpringTemplate->mParticleCount;
    mFlfWoolDraw->fn_800267B0(index, count + m_10C * (count - 1));
    mFlfWoolDraw->m_18 = 1.0f;
    fn_8001AA00(1.0f);
    fn_8001AB58();
}

// https://decomp.me/scratch/2EoV3 std::vector being annoying again
WoolBaseMdl::~WoolBaseMdl() {
    if (mFlfWoolDraw != nullptr) {
        delete mFlfWoolDraw;
    }

    mFlfWoolDraw = nullptr;

    for (uint i = 0; i < mBackupBuffs.size(); i++) {
        delete mBackupBuffs[i];
    }
}

WoolBaseMdl::BackupBuff::~BackupBuff() {
    if (mPoints != nullptr) {
        delete[] mPoints;
    }
}

void WoolBaseMdl::fn_8001AA00(float arg1) {
    m_140 = arg1;
    mFlfWoolDraw->fn_80026DFC(arg1);
}

void WoolBaseMdl::fn_8001AA0C(float arg1) {
    mFlfWoolDraw->m_18 = arg1;
}

void WoolBaseMdl::fn_8001AA18(float arg1) {
    mFlfWoolDraw->m_1C = arg1;
}

void WoolBaseMdl::fn_8001AA24(bool arg1) {
    m_108 = arg1;
    SetUpdate(m_108 || m_158);
}

void WoolBaseMdl::fn_8001AA5C(bool arg1) {
    if (arg1 && !m_158) {
        m_150 = 0;
    }

    m_158 = arg1;
    SetUpdate(m_108 || m_158);
}

int WoolBaseMdl::ResetScene(FullSortScene* pScene) {
    GetScene()->RemoveRenderObj(this);
    pScene->AddRenderObj(this);
    return 1;
}

void WoolBaseMdl::fn_8001AB34(int arg1) {
    mFlfWoolDraw->fn_80026A54(arg1);
}

gfl::Vec3 WoolBaseMdl::vfA0() {
    return m_134;
}

// https://decomp.me/scratch/i6lcp
void WoolBaseMdl::fn_8001AB58() {
    gfl::Vec2 vec1(0.0f, 0.0f);
    gfl::Vec2 vec2(0.0f, 0.0f);

    for (uint i = 0; i < mWoolBaseTask->mSpringTemplate->mParticleCount; i++) {
        gfl::Vec3 offset = mWoolBaseTask->GetParticleEffectOffsetByIndex(i);

        if (i == 0 || offset.x < vec1.x) {
            vec1.x = offset.x;
        }

        if (i == 0 || offset.x < vec1.y) {
            vec1.y = offset.y;
        }

        if (i == 0 || vec2.x > offset.x) {
            vec2.x = offset.x;
        }

        if (i == 0 || vec2.y > offset.y) {
            vec2.y = offset.y;
        }
    }

    m_134 = (vec2 - vec1) * 0.5f + vec1;
    m_134.z = 0.0f;

    float f1 = (vec2.x - vec1.x) * (vec2.x - vec1.x) + (vec2.y - vec1.y) * (vec2.y - vec1.y);

    if (f1 < 0.0f) {
        NW4R_MATH_WARNING("arithmetic.h", 0x273, "FSqrt: Input is out of the domain.");
    }

    float f2 = 0.0f;
    if (f1 > 0.0f) {
        f2 = nw4r::math::FrSqrt(f1);
        f2 = f1 * f2;
    }

    SetUpdateRate(f2 * 0.5f * 1.5f);
}

gfl::Vec2::Vec2() {
    x = 0.0f;
    y = 0.0f;
}

void WoolBaseMdl::fn_8001AD5C(float arg1) {
    mFlfWoolDraw->fn_80026E74(arg1, 0);
}

void WoolBaseMdl::fn_8001AD68() {
    mFlfWoolDraw->fn_80026E88(0);
}

void WoolBaseMdl::fn_8001AD74(int arg1) {
    mFlfWoolDraw->m_58 = arg1;
}

void WoolBaseMdl::fn_8001AD80(float arg1) {
    mFlfWoolDraw->m_5C = arg1;
}

void WoolBaseMdl::fn_8001AD8C(int arg1, int arg2) {
    m_154 = arg1;

    int num = mFlfWoolDraw->fn_80026B54(0);

    for (uint i = 0; i < m_154; i++) {
        BackupBuff* buf = new (gfl::HeapID::Work) BackupBuff;
        buf->mPoints = new (gfl::HeapID::Work) gfl::Vec2[num];
        mBackupBuffs.push_back(buf);
    }

    m_15C = arg2;
}

void WoolBaseMdl::fn_8001AEE4() {
    uint count = mWoolBaseTask->GetParticleCount();
    gfl::Vec3 pos = mWoolBaseTask->GetParticleEffectOffsetByIndex(count - 1);

    nw4r::math::MTX34 mtx;
    PSMTXIdentity(mtx);
    mtx[0][0] = m_128.x;
    mtx[1][1] = m_128.y;
    mtx[2][2] = 1.0f;

    mtx[0][3] = pos.x + mWoolBaseTask->mPosition.x;
    mtx[1][3] = pos.y + mWoolBaseTask->mPosition.y;
    mtx[2][3] = mWoolBaseTask->GetZPos();

    nw4r::g3d::ScnObj::SetMtx(MTX_LOCAL, &mtx);
}

// https://decomp.me/scratch/jqMgw
void WoolBaseMdl::DrawXlu() {
    if (m_108 || m_158) {
        if (m_10C != 0) {
            for (uint i = 0; i < mWoolBaseTask->mSpringTemplate->mParticleCount; i++) {
                gfl::Vec3 pos1 = mWoolBaseTask->GetParticleEffectOffsetByIndex(i);

                gfl::Vec3 vec1(0.0f);
                gfl::Vec3 vec2;

                if (i == mWoolBaseTask->mSpringTemplate->mParticleCount - 1) {
                    gfl::Vec3 pos2 = mWoolBaseTask->GetParticleEffectPositionByIndex(i - 1);
                    vec2 = pos1 - pos2;
                } else if (i == 0) {
                    gfl::Vec3 pos2 = mWoolBaseTask->GetParticleEffectPositionByIndex(1);
                    vec2 = pos2 - pos1;
                } else {
                    gfl::Vec3 pos2 = mWoolBaseTask->GetParticleEffectPositionByIndex(i + 1);
                    vec2 = ((pos2 - pos1) + vec1) * 0.5f;
                }

                gfl::Vec3 vec3 = vec2 * 2.0f;
                mHermiteCurve.fn_806606A8(i, pos1, vec3);
            }
            mHermiteCurve.fn_80660FA8();
        }

        uint count = mWoolBaseTask->GetParticleCount();
        gfl::Vec3 pos1 = mWoolBaseTask->GetParticleEffectPositionByIndex(count - 1);

        gfl::Vec2 vec(0.0f, 0.0f);

        for (uint i = 0; i < mWoolBaseTask->mSpringTemplate->mParticleCount; i++) {
            gfl::Vec3 pos2 = mWoolBaseTask->GetParticleEffectPositionByIndex(i);

            // not done
        }
    }
}

void WoolBaseMdl::fn_8001B4DC() {
    // not decompiled
}

void WoolBaseMdl::fn_8001BCD0(nw4r::math::MTX34* pMtx) {
    if (mWoolBaseTask->mTask.mFlags & ~mWoolBaseTask->mTask.mSuspendFlags) {
        return;
    }

    BackupBuff* buf = mBackupBuffs[m_150];
    
    for (uint i = 0; i < mFlfWoolDraw->fn_80026B54(0); i++) {
        buf->mPoints[i] = *mFlfWoolDraw->fn_80026A60(0, i);
    }

    buf->mMtx = *pMtx;
}
