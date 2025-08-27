#include "graphics/NwAnm.h"
#include <nw4r/g3d/g3d_anmobj.h>

float NwAnm::GetCurrentFrame() {
    if (mTexPatAnim != nullptr) {
        return mTexPatAnim->GetFrame();
    }

    if (mMatClrAnim != nullptr) {
        return mMatClrAnim->GetFrame();
    }

    if (mTexSrtAnim != nullptr) {
        return mTexSrtAnim->GetFrame();
    }

    if (mChrAnim != nullptr) {
        return mChrAnim->GetFrame();
    }

    if (mVisAnim != nullptr) {
        return mVisAnim->GetFrame();
    }

    if (mShpAnim != nullptr) {
        return mShpAnim->GetFrame();
    }

    return 0.0f;
}

void NwAnm::SetCurrentFrame(float frame) {
    if (mTexPatAnim != nullptr) {
        mTexPatAnim->SetFrame(frame);
    }

    if (mMatClrAnim != nullptr) {
        mMatClrAnim->SetFrame(frame);
    }

    if (mTexSrtAnim != nullptr) {
        mTexSrtAnim->SetFrame(frame);
    }

    if (mChrAnim != nullptr) {
        mChrAnim->SetFrame(frame);
    }

    if (mVisAnim != nullptr) {
        mVisAnim->SetFrame(frame);
    }

    if (mShpAnim != nullptr) {
        mShpAnim->SetFrame(frame);
    }
}

void NwAnm::SetUpdateRate(float rate) {
    if (mTexPatAnim != nullptr) {
        mTexPatAnim->SetUpdateRate(rate);
    }

    if (mMatClrAnim != nullptr) {
        mMatClrAnim->SetUpdateRate(rate);
    }

    if (mTexSrtAnim != nullptr) {
        mTexSrtAnim->SetUpdateRate(rate);
    }

    if (mChrAnim != nullptr) {
        mChrAnim->SetUpdateRate(rate);
    }

    if (mVisAnim != nullptr) {
        mVisAnim->SetUpdateRate(rate);
    }

    if (mShpAnim != nullptr) {
        mShpAnim->SetUpdateRate(rate);
    }
}

float NwAnm::GetUpdateRate() {
    if (mTexPatAnim != nullptr) {
        return mTexPatAnim->GetUpdateRate();
    }

    if (mMatClrAnim != nullptr) {
        return mMatClrAnim->GetUpdateRate();
    }

    if (mTexSrtAnim != nullptr) {
        return mTexSrtAnim->GetUpdateRate();
    }

    if (mChrAnim != nullptr) {
        return mChrAnim->GetUpdateRate();
    }

    if (mVisAnim != nullptr) {
        return mVisAnim->GetUpdateRate();
    }

    if (mShpAnim != nullptr) {
        return mShpAnim->GetUpdateRate();
    }

    return 0.0f;
}

bool NwAnm::IsAnimationDone() {
    return mAnimationEndFrame <= GetCurrentFrame();
}

bool NwAnm::HasAnim() {
    if ((mTexPatAnim == nullptr) &&
        (mMatClrAnim == nullptr) &&
        (mTexSrtAnim == nullptr) &&
        (mChrAnim    == nullptr) &&
        (mVisAnim    == nullptr) &&
        (mShpAnim    == nullptr)) {
        return false;
    }

    return true;
}
