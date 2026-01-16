#include "manager/EnemyMdlManager.h"
#include "object/EnemyBase.h"

// https://decomp.me/scratch/2vAP6
EnemyMdlManager::EnemyMdlManager(
    gfl::Task* pParentTask,
    FullSortScene* pScene,
    EnemyBase* pOwner,
    const char* pResourcePath,
    uint drawFlags,
    int count,
    int* pIndices
)
    : mTask(nullptr)
    , m_8(0)
    , mScene(pScene)
    , mOwner(pOwner)
    , mFlfMdlDraw(nullptr)
    , m_34(0)
    , mKeyFrames()
    , m_55(false)
    , m_56(false)
    , m_74(0.7f)
    , mMatrix()
    , m_A8(nw4r::math::VEC3(0.0f, 0.0f, 0.0f))
    , m_B4(nw4r::math::VEC3(1.0f, 1.0f, 1.0f))
    , m_C0(nw4r::math::VEC3(1.0f, 1.0f, 1.0f))
    , m_CC(999999)
    , m_D0(-1.0f)
    , mMdlParts()
{

    mTask = new (gfl::HeapID::Work) gfl::Task(this, Update, "EnemyMdlManger::Update");
    mTask->SetFlags(0);
    pParentTask->MakeChild(mTask);

    SetupGraphics(mScene, pResourcePath, drawFlags, count, pIndices);
    m_20 = 1.0f;
    m_1C = -1;
    m_18 = -1;

    mCurrentState = 0;
    mPreviousState = 0;

    m_2C = 0x244;
    mResetFrames = true;

    fn_8011222C(0);
    fn_80112234(0.0f);

    m_60 = 0;
    m_64 = 0.0f;
    m_68 = 0;
    m_6C = 0xF;
    m_70 = 1;
}

EnemyMdlManager::~EnemyMdlManager() {
    if (mFlfMdlDraw != nullptr) {
        delete mFlfMdlDraw;
    }
    
    mFlfMdlDraw = nullptr;

    if (m_8 != nullptr) {
        delete m_8;
    }
    
    m_8 = nullptr;

    if (mTask != nullptr) {
        delete mTask;
    }

    mTask = nullptr;
}

void EnemyMdlManager::Update() const {
    GET_UNCONST(EnemyMdlManager);

    self->fn_80112334();
    self->fn_8011224C();
}

void EnemyMdlManager::fn_801121E4(float arg1) {
    if (arg1 < 0.0f) {
        arg1 *= -1.0f;
    }

    m_58 = 1;
    m_5C = arg1;
}

void EnemyMdlManager::fn_80112208(float arg1) {
    if (arg1 > 0.0f) {
        arg1 *= -1.0f;
    }

    m_58 = 2;
    m_5C = arg1;
}

void EnemyMdlManager::fn_8011222C(uint arg1) {
    m_58 = arg1;
}

void EnemyMdlManager::fn_80112234(float arg1) {
    m_5C = arg1;
}

int EnemyMdlManager::fn_8011223C() {
    return m_58;
}

void EnemyMdlManager::fn_80112244() {
    fn_8011222C(0);
}

inline float clamp(float f, float min, float max) {
    float ret = f;
    
    if (f <= min) {
        ret = min;
    } else if (f >= max) {
        ret = max;
    }

    return ret;
}

void EnemyMdlManager::fn_8011224C() {
    FlfMdlDraw* draw = mFlfMdlDraw;

    float unk = draw->fn_800252AC();

    if (m_58 - 1 > 1) {
        return;
    }

    unk += m_5C;

    float f = clamp(unk, 0, 1.0f);

    draw->fn_80025204(f);
}

void EnemyMdlManager::fn_801122D4(bool arg1, int arg2, int arg3) {
    if (arg1) {
        m_60 = 1;
        m_64 = 0.0f;
        m_68 = 0;
        m_6C = arg3;
        m_70 = arg2;
    } else {
        m_60 = 0;
    }

    if (mFlfMdlDraw != nullptr) {
        mFlfMdlDraw->fn_80147C28(0.0f, 0);
    }
}

int EnemyMdlManager::fn_80112324() {
    return m_60;
}

void EnemyMdlManager::fn_8011232C(int arg1) {
    m_6C = arg1;
}

void EnemyMdlManager::fn_80112334() {
    
    if (m_60 == 0) {
        return;
    }

    if (mFlfMdlDraw == nullptr) {
        return;
    }

    FlfMdlDraw* draw = mFlfMdlDraw;
    
    float unk = 1.0f / static_cast<float>(m_6C);

    switch (m_60) {
        case 1: {
            m_64 += unk;
    
            if (m_64 >= 1.0f) {
                m_64 = 1.0f;
                m_60 = 2;
            }

            break;
        }

        case 2: {
            m_64 -= unk;
    
            if (m_64 <= 0.0f) {            
                m_64 = 0.0f;
                m_60 = 1;
            }

            break;
        }
    }

    m_68++;
    if (m_68 >= m_6C) {
        m_68 = 0;
    }

    draw->fn_80147C28(m_70, m_64);
}

nw4r::g3d::G3dObj* EnemyMdlManager::SetupGraphics(
    FullSortScene* pScene,
    const char* pResourcePath,
    uint drawFlags,
    int count,
    int* pIndices
) {
    mFlfMdlDraw = new (gfl::HeapID::Work) FlfMdlDraw(pScene, pResourcePath, nullptr, true);

    mFlfMdlDraw->mFlags |= drawFlags;
    
    if (count == 0) {
        mFlfMdlDraw->LoadNURBSFromFileList();
    } else {
        mFlfMdlDraw->LoadNURBSFromFileList(pIndices, count);
    }
    
    mFlfMdlDraw->mShadowOffsets.m_14 = true;

    nw4r::g3d::G3dObj* anim = mFlfMdlDraw->GetBlendAnmMatCtrlAnim(0);
    mGraphicsSetup = true;
    return anim;
}

void EnemyMdlManager::fn_801124DC(float arg1, float arg2, int arg3) {
    mFlfMdlDraw->m_13C = arg3;
    mFlfMdlDraw->m_138 = arg1;
    mFlfMdlDraw->m_140 = arg2;
    m_74 = arg1;
}

void EnemyMdlManager::fn_801124FC() {
    mFlfMdlDraw->m_138 = 0.1f;
}

void EnemyMdlManager::fn_8011250C() {
    mFlfMdlDraw->m_138 = m_74;
}

void EnemyMdlManager::fn_8011251C(int arg1, bool resetFrames) {
    m_1C = mOwner->vf314();
    m_2C = arg1;
    mResetFrames = resetFrames;
}

void EnemyMdlManager::fn_8011257C(int arg1, bool resetFrames) {
    m_1C = mOwner->vf314();
    m_2C = arg1;
    mResetFrames = resetFrames;
    Reset();
}

void EnemyMdlManager::Reset() {
    mPreviousState = mCurrentState;

    if (m_1C < 0) {
        return;
    }
    
    int old = m_1C;

    m_18 = m_1C;
    m_1C = -1;
    mCurrentState = m_2C;
    m_2C = 0x244;
    
    mFlfMdlDraw->ResetNURBSAnimation(old, mResetFrames);
}

void EnemyMdlManager::Reset(int arg1, bool resetFrames) {
    mPreviousState = mCurrentState;
    mCurrentState = 0x243;
    m_1C = -1;
    m_18 = arg1;
    mFlfMdlDraw->ResetNURBSAnimation(arg1, resetFrames);
}

bool EnemyMdlManager::fn_80112648() {
    bool ret = false;

    if (mOwner->m_74 == 0 && mGraphicsSetup) {
        ret = true;
    }

    return ret;
}

void EnemyMdlManager::fn_80112674(const nw4r::math::MTX34& rMtx) {
    if (mOwner->m_74 == 0 && mGraphicsSetup) {
        nw4r::math::MTX34 mtx1 = rMtx;
        nw4r::math::MTX34 mtx2(
            -1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0, 1.0f, 0.0f
        );
        PSMTXConcat(mtx1, mtx2, mtx1);
        mFlfMdlDraw->SetWoolDrawMatrix(mtx1);
        mMatrix = rMtx;
    } else {
        mFlfMdlDraw->SetWoolDrawMatrix(rMtx);
        mMatrix = rMtx;
    }
}

void EnemyMdlManager::SetVisibility(bool visible) {
    mFlfMdlDraw->SetVisibility(visible);
}

bool EnemyMdlManager::fn_80112854() {
    return mFlfMdlDraw->fn_80023B1C();
}

void EnemyMdlManager::fn_8011285C(bool arg1) {
    m_55 = arg1;
    fn_8011286C();   
}

void EnemyMdlManager::fn_80112864(bool arg1) {
    m_56 = arg1;
    fn_8011286C();   
}

void EnemyMdlManager::fn_8011286C() {
    bool update = false;

    if (!m_55 && !m_56) {
        update = true;
    }

    mFlfMdlDraw->Update(update);

    if (mMdlParts.m_0 != nullptr) {
        mMdlParts.m_0->Update(update);
    }
}

float EnemyMdlManager::GetCurrentFrame() {
    return mFlfMdlDraw->GetCurrentFrame();
}

void EnemyMdlManager::SetCurrentFrame(float frame) {
    mFlfMdlDraw->SetCurrentNURBSFrame(frame);
}

bool EnemyMdlManager::IsAnimationDone() {
    return mFlfMdlDraw->IsAnimationDone();
}

void EnemyMdlManager::SetUpdateRate(float rate) {
    mFlfMdlDraw->SetUpdateRate(rate);
}

float EnemyMdlManager::GetUpdateRate() {
    return mFlfMdlDraw->mUpdateRate;
}

bool EnemyMdlManager::SetScene(FullSortScene* pScene) {
    if (mFlfMdlDraw == nullptr) {
        return false;
    }
    
    mFlfMdlDraw->SetScene(pScene);
    return true;
}