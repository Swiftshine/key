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
    , mIsPlaying(false)
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
    mIsPlaying = false;
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

    mIsPlaying = false;
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

void LayoutAnimeElement::UpdateTransformFrameMultiplied(f32 mult) {
    if (!mIsReversed) {
        mFrame = mult * mRate + mFrame;
        UpdateTransformFrameForward();
    } else {
        mFrame = -(mult * mRate - mFrame);
        UpdateTransformFrameReversed();
    }
}

void LayoutAnimeElement::UpdateTransformFrameForward() {
    if (mAnimTransform == nullptr) {
        return;
    }

    bool done = false;
    mIsPlaying = false;

    if (mAnimTransform->IsLoopData()) {
        while (static_cast<f32>(mAnimTransform->GetFrameSize()) <= mFrame) {
            mIsPlaying = true;
            mFrame -= static_cast<f32>(mAnimTransform->GetFrameSize());
        }
    } else {
        if (static_cast<f32>(mAnimTransform->GetFrameSize()) <= mFrame) {
            mFrame = static_cast<f32>(mAnimTransform->GetFrameSize());
            mIsPlaying = true;
            done = true;
        }
    }

    if (done) {
        mAnimTransform->SetFrame(static_cast<f32>(mAnimTransform->GetFrameSize()));
    } else {
        mAnimTransform->SetFrame(mFrame);
    }
}

void LayoutAnimeElement::UpdateTransformFrameReversed() {
    if (mAnimTransform == nullptr) {
        return;
    }

    bool done = false;
    mIsPlaying = false;

    if (mAnimTransform->IsLoopData()) {
        while (mFrame <= 0.0f) {
            mIsPlaying = true;
            mFrame += static_cast<f32>(mAnimTransform->GetFrameSize());
        }
    } else if (mFrame <= 0.0f) {
        mFrame = 0.0f;
        mIsPlaying = true;
        done = true;
    }

    if (done) {
        mAnimTransform->SetFrame(0.0f);
    } else {
        mAnimTransform->SetFrame(mFrame);
    }
}

void LayoutAnimeElement::UpdateTransformFrameDirectly(f32 frame) {
    mFrame = frame;

    if (!mIsReversed) {
        UpdateTransformFrameForward();
    } else {
        UpdateTransformFrameReversed();
    }
}

f32 LayoutAnimeElement::GetFrame() const {
    return mFrame;
}

f32 LayoutAnimeElement::GetAnimTransformFrameSize() {
    nw4r::lyt::AnimTransform* transform = mAnimTransform;
    if (transform == nullptr) {
        return -1.0f;
    }

    return static_cast<f32>(transform->GetFrameSize());
}

f32 LayoutAnimeElement::GetAnimationCompletion() const {
    f32 frame = GetFrame(); // code merging
    f32 rate = static_cast<f32>(mAnimTransform->GetFrameSize());

    if (rate <= 0.0f) {
        return 0.0f;
    }

    f32 percentage = 0.0f;
    frame /= rate;

    if (frame < 0.0f) {
        frame = 0.0f;
    }

    percentage = frame;

    if (1.0f < percentage) {
        percentage = 1.0f;
    }

    return percentage;
}

bool LayoutAnimeElement::ResetForward() {
    bool ret = mIsReversed != false;
    mIsReversed = false;
    mIsPlaying = false;
    return ret;
}

bool LayoutAnimeElement::ResetReversed() {
    bool ret = mIsReversed != true;
    mIsReversed = true;
    mIsPlaying = false;
    return ret;
}

bool LayoutAnimeElement::IsPlaying() const {
    return mIsPlaying;
}
