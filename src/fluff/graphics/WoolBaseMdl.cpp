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

    int index = mFlfWoolDraw->Register(rResFileObject, pWoolName1, pWoolName2);

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
        idx = mFlfWoolDraw->Register(rResFileObject, name, name);

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
            idx = mFlfWoolDraw->Register(rResFileObject, name, name);

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
    if (m_0 != nullptr) {
        delete[] m_0;
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