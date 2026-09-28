#include <layout/Layout.h>
#include <layout/LayoutAnimeElement.h>

using namespace layout;

LayoutAnimeElement::LayoutAnimeElement(nw4r::lyt::Layout* pLayout, nw4r::lyt::Pane* pPane)
    : mLayout(pLayout)
    , mPane(pPane)
    , mHash(-1u)
    , mAnimTransform(nullptr)
    , mFrame(0.0f)
    , mIsTransformInited(false)
    , mIsReversed(false)
    , mRate(1.0f)
    , mIsRecursive(true)
    , mAdditionalTransforms()
{
    Init();
    mAdditionalTransforms.clear();
}

LayoutAnimeElement::~LayoutAnimeElement() {
    UnbindAnimation();
    mAdditionalTransforms.clear();
}

void LayoutAnimeElement::Init() {
    mHash = -1u;
    mAnimTransform = nullptr;
    mFrame = 0.0f;
    mIsTransformInited = false;
    mIsReversed = false;
    mRate = 1.0f;
    mIsRecursive = true;
}

void LayoutAnimeElement::BindForward(const char* pAnimationName, bool recursive, s32 arg3) {
    u32 hash = CalcHash(pAnimationName);
    if (
        (arg3 == 0 || mHash != hash) &&
        SetAnimTransform(hash, pAnimationName, recursive) &&
        InitForward() &&
        BindAnimation()
    ) {
        mHash = hash;
    }
}

void LayoutAnimeElement::BindReversed(const char* pAnimationName, bool recursive, s32 arg3) {
    u32 hash = CalcHash(pAnimationName);
    if (
        (arg3 == 0 || mHash != hash) &&
        SetAnimTransform(hash, pAnimationName, recursive) &&
        InitReversed() &&
        BindAnimation()
    ) {
        mHash = hash;
    }
}

bool LayoutAnimeElement::SetAnimTransform(u32 hash, const char* pAnimationName, bool recursive) {
    if (mPane == nullptr) {
        return false;
    }

    if (mAnimTransform != nullptr) {
        UnbindAnimation();
    }

    mAnimTransform = GetAnimTransform(hash);

    if (mAnimTransform == nullptr) {
        mAnimTransform = CreateAnimTransform(pAnimationName);
    }

    mIsTransformInited = false;
    mRate = 1.0f;
    mIsRecursive = recursive;

    return true;
}

bool LayoutAnimeElement::InitForward() {
    if (mAnimTransform == nullptr) {
        return false;
    }

    mFrame = 0.0f;
    mIsReversed = false;

    return true;
}

bool LayoutAnimeElement::InitReversed() {
    if (mAnimTransform == nullptr) {
        return false;
    }

    mFrame = static_cast<f32>(mAnimTransform->GetFrameSize()) - 1.0f;
    mIsReversed = true;

    return true;
}

bool LayoutAnimeElement::BindAnimation() {
    if (mAnimTransform == nullptr) {
        return false;
    }

    mPane->BindAnimation(mAnimTransform, mIsRecursive, false);
    mPane->SetAnimationEnable(mAnimTransform, true, mIsRecursive);
    mAnimTransform->SetFrame(mFrame);

    return true;
}
