#include <layout/Layout.h>
#include <layout/LayoutAnimeElement.h>
#include <layout/LayoutManager.h>

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

void LayoutAnimeElement::UnbindAnimation() {
    if (mAnimTransform == nullptr) {
        return;
    }

    if (mPane != nullptr) {
        mPane->SetAnimationEnable(mAnimTransform, false, mIsRecursive);
        mPane->UnbindAnimation(mAnimTransform, mIsRecursive);
    }

    if (mLayout != nullptr) {
        mLayout->SetAnimationEnable(mAnimTransform, false);
        mLayout->UnbindAnimation(mAnimTransform);
    }

    mAnimTransform = nullptr;
}

// non-matching due to tree (?)::insert
nw4r::lyt::AnimTransform* LayoutAnimeElement::CreateAnimTransform(const char* pAnimationName) {
    if (mLayout == nullptr) {
        return nullptr;
    }

    nw4r::lyt::ArcResourceAccessor* accessor = LayoutManager::GetResourceAccessor();

    if (accessor == nullptr) {
        return nullptr;
    }

    u32 hash = CalcHash(pAnimationName);
    nw4r::lyt::AnimTransform* transform = GetAnimTransform(hash);

    if (transform != nullptr) {
        return transform;
    }

    void* resource = accessor->GetResource(nw4r::lyt::ArcResourceAccessor::RES_TYPE_ANIMATION, pAnimationName, nullptr);

    if (resource == nullptr) {
        return nullptr;
    }

    transform = mLayout->CreateAnimTransform(resource, accessor);
    mAdditionalTransforms.insert(transform);
    return transform;
}

// non-matching
nw4r::lyt::AnimTransform* LayoutAnimeElement::GetAnimTransform(u32 hash) const {
    // not decompiled
    return nullptr;
}

void LayoutAnimeElement::SetAnimTransformFrameForward() {
    if (!mIsReversed || mAnimTransform == nullptr) {
        mFrame = 0.0f;
    } else {
        mFrame = static_cast<f32>(mAnimTransform->GetFrameSize()) - 1.0f;
    }
}

void LayoutAnimeElement::SetAnimTransformFrameReversed() {
    if (!mIsReversed || mAnimTransform == nullptr) {
        mFrame = static_cast<f32>(mAnimTransform->GetFrameSize()) - 1.0f;
    } else {
        mFrame = 0.0f;
    }
}

void LayoutAnimeElement::UpdateTransformFrame(f32 mult) {
    if (!mIsReversed) {
        mFrame = mult * mRate + mFrame;
        UpdateTransformFrameForward();
    } else {
        mFrame = -(mult * mRate - mFrame);
        UpdateTransformFrameReversed();
    }
}
