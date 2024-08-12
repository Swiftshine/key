#include <game/graphics/NwAnm.h>
#include <nw4r/g3d/g3d_anmobj.h>

f32 NwAnm::GetCurrentFrame() {
    if (mpTexPatAnim) return mpTexPatAnim->GetFrame();
    if (mpMatClrAnim) return mpMatClrAnim->GetFrame();
    if (mpTexSrtAnim) return mpTexSrtAnim->GetFrame();
    if (mpChrAnim) return mpChrAnim->GetFrame();
    if (mpVisAnim) return mpVisAnim->GetFrame();
    if (mpShpAnim) return mpShpAnim->GetFrame();
    return 0.0f;
}

void NwAnm::SetCurrentFrame(f32 frame) {
    if (mpTexPatAnim) mpTexPatAnim->SetFrame(frame);
    if (mpMatClrAnim) mpMatClrAnim->SetFrame(frame);
    if (mpTexSrtAnim) mpTexSrtAnim->SetFrame(frame);
    if (mpChrAnim) mpChrAnim->SetFrame(frame);
    if (mpVisAnim) mpVisAnim->SetFrame(frame);
    if (mpShpAnim) mpShpAnim->SetFrame(frame);
}

void NwAnm::SetUpdateRate(f32 rate) {
    if (mpTexPatAnim) mpTexPatAnim->SetUpdateRate(rate);
    if (mpMatClrAnim) mpMatClrAnim->SetUpdateRate(rate);
    if (mpTexSrtAnim) mpTexSrtAnim->SetUpdateRate(rate);
    if (mpChrAnim) mpChrAnim->SetUpdateRate(rate);
    if (mpVisAnim) mpVisAnim->SetUpdateRate(rate);
    if (mpShpAnim) mpShpAnim->SetUpdateRate(rate);
}

f32 NwAnm::GetUpdateRate() {
    if (mpTexPatAnim) return mpTexPatAnim->GetUpdateRate();
    if (mpMatClrAnim) return mpMatClrAnim->GetUpdateRate();
    if (mpTexSrtAnim) return mpTexSrtAnim->GetUpdateRate();
    if (mpChrAnim) return mpChrAnim->GetUpdateRate();
    if (mpVisAnim) return mpVisAnim->GetUpdateRate();
    if (mpShpAnim) return mpShpAnim->GetUpdateRate();
}

bool NwAnm::IsAnimationDone() {
    return mAnimationEndFrame <= GetCurrentFrame();
}

bool NwAnm::HasAnim() {
    if (!mpTexPatAnim && !mpMatClrAnim && !mpTexSrtAnim && !mpChrAnim && !mpVisAnim && !mpShpAnim) {
        return false;
    }

    return true;
}
