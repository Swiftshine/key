#include "graphics/FlfMdlDraw.h"

// nonmatching (std::string)
FlfMdlDraw::FlfMdlDraw(
    FullSortScene* pFullSortScene,
    const char* pResourceName,
    const char* pFilepath,
    bool arg4
)
    : mResourcePath(pResourceName)
    , mFullSortScene(pFullSortScene)
    , m_20(-1)
    , mUpdateRate(1.0f)
    , m_28(true)
    , m_2C(9.333333f)
    , m_30(0.0f, 0.0f, 0.0f)
    , mShouldUpdate(true)
    , m_40(1)
    , m_44(false)
    , m_48(1.0f)
    , m_4C(nullptr)
    , mNURBSAnimWrapper(nullptr)
    , mNURBSAnimWrapper2(nullptr)
    , mFlags(0)
    , mCurrentFrame(0.0f)
    , mCurrentFrameInt(10)
    , m_68(0)
    , mIsCubic(false)
    , mShadowOffsets()
    , m_C4(
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    )
    , m_F4(
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    )
    , m_124(arg4)
    , m_128(0.0f)
    , m_12C(0.0f)
    , m_130(0.0f)
    , m_134(0.0f)
    , m_138(0.89999998f)
    , m_13C(0)
    , m_140(0.0f)
    , m_144(0)
    , m_148(0)
    , m_14C(0.0f, 0.0f)
    , m_154(0.0f, 0.0f)
    , m_15C(0.0f, 0.0f)
    , m_164(3)
    , mCallbacks()
    , m_18C(0)
    , m_190(0)
    , m_194(0)
    , mAnimFileInfo(nullptr)
    , mFileInfo(nullptr)
    , m_1A0(new (gfl::HeapID::Work) FlfMdlVec)
    , m_1A4(new (gfl::HeapID::Work) FlfMdlVec)
    , m_1A8(0)
    , mNwBlendAnmWrappers(nullptr)
    , mNwBlendAnmWrapperCount(0)
    , mNURBSObjects()
    , mAnims(nullptr)
    , mDrawObj(nullptr)
{
    PSMTXIdentity(m_C4);
    PSMTXIdentity(m_F4);

    m_70 = 0;
    m_74 = 0;

    m_78.Init();
    mShadowOffsets.Init();

    size_t len = mResourcePath.size();
    const char* str = mResourcePath.c_str();

    if (str[len - 1] != '/') {
        mResourcePath += "/";
    }

    if (pFilepath != nullptr) {
        mRawFilepath = pFilepath;
        LoadWoolTextures();
    }

    mShadowOffsets.m_8 = 1.0f;
    mShadowOffsets.m_22 = true;
    m_15C.x = 0.0f;
    m_15C.y = 0.5f;
}

FlfMdlDraw::Callback::Callback() {

}

FlfMdlDraw::Callback::~Callback() {
    
}