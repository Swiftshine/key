#include "manager/EnemyMdlManager.h"

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