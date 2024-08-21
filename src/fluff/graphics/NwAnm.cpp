#include "graphics/NwAnm.h"
#include <nw4r/g3d/g3d_anmobj.h>

float NwAnm::GetCurrentFrame() {
    if (mTexPatAnim) return mTexPatAnim->GetFrame();
    if (mMatClrAnim) return mMatClrAnim->GetFrame();
    if (mTexSrtAnim) return mTexSrtAnim->GetFrame();
    if (mChrAnim) return mChrAnim->GetFrame();
    if (mVisAnim) return mVisAnim->GetFrame();
    if (mShpAnim) return mShpAnim->GetFrame();
    return 0.0f;
}

void NwAnm::SetCurrentFrame(float frame) {
    if (mTexPatAnim) mTexPatAnim->SetFrame(frame);
    if (mMatClrAnim) mMatClrAnim->SetFrame(frame);
    if (mTexSrtAnim) mTexSrtAnim->SetFrame(frame);
    if (mChrAnim) mChrAnim->SetFrame(frame);
    if (mVisAnim) mVisAnim->SetFrame(frame);
    if (mShpAnim) mShpAnim->SetFrame(frame);
}

void NwAnm::SetUpdateRate(float rate) {
    if (mTexPatAnim) mTexPatAnim->SetUpdateRate(rate);
    if (mMatClrAnim) mMatClrAnim->SetUpdateRate(rate);
    if (mTexSrtAnim) mTexSrtAnim->SetUpdateRate(rate);
    if (mChrAnim) mChrAnim->SetUpdateRate(rate);
    if (mVisAnim) mVisAnim->SetUpdateRate(rate);
    if (mShpAnim) mShpAnim->SetUpdateRate(rate);
}

float NwAnm::GetUpdateRate() {
    if (mTexPatAnim) return mTexPatAnim->GetUpdateRate();
    if (mMatClrAnim) return mMatClrAnim->GetUpdateRate();
    if (mTexSrtAnim) return mTexSrtAnim->GetUpdateRate();
    if (mChrAnim) return mChrAnim->GetUpdateRate();
    if (mVisAnim) return mVisAnim->GetUpdateRate();
    if (mShpAnim) return mShpAnim->GetUpdateRate();
}

bool NwAnm::IsAnimationDone() {
    return mAnimationEndFrame <= GetCurrentFrame();
}

bool NwAnm::HasAnim() {
    if (!mTexPatAnim && !mMatClrAnim && !mTexSrtAnim && !mChrAnim && !mVisAnim && !mShpAnim) {
        return false;
    }

    return true;
}
