#ifndef FLUFF_LAYOUT_LAYOUTANIMEELEMENT_H
#define FLUFF_LAYOUT_LAYOUTANIMEELEMENT_H

#include <types.h>

#include <tree>

#include <nw4r/lyt.h>

namespace layout {

class LayoutAnimeElement {
public:
    LayoutAnimeElement(nw4r::lyt::Layout* pLayout, nw4r::lyt::Pane* pPane);
    virtual ~LayoutAnimeElement();

    void Init();
    void BindForward(const char* pAnimationName, bool recursive, s32 arg3 = 0);
    void BindReversed(const char* pAnimationName, bool recursive, s32 arg3 = 0);
    bool SetAnimTransform(u32 hash, const char* pAnimationName, bool recursive);
    bool InitForward();
    bool InitReversed();
    bool BindAnimation();
    void UnbindAnimation();
    nw4r::lyt::AnimTransform* CreateAnimTransform(const char* pAnimationName);
    nw4r::lyt::AnimTransform* GetAnimTransform(u32 hash) const;
    void SetAnimTransformFrameForward();
    void SetAnimTransformFrameReversed();
    void UpdateTransformFrameMultiplied(f32 mult);
    void UpdateTransformFrameForward();
    void UpdateTransformFrameReversed();
    void UpdateTransformFrameDirectly(f32 frame);
    f32 GetAnimTransformFrameSize();
    f32 GetAnimationCompletion() const;
    bool ResetForward();
    bool ResetReversed();
    bool IsPlaying() const;
    DECL_WEAK f32 GetFrame() const DONT_INLINE_CLASS ;
private:
    /* 0x04 */ nw4r::lyt::Layout* mLayout;
    /* 0x08 */ nw4r::lyt::Pane* mPane;
    /* 0x0C */ u32 mHash;
    /* 0x10 */ nw4r::lyt::AnimTransform* mAnimTransform;
    /* 0x14 */ f32 mFrame;
    /* 0x18 */ bool mIsPlaying;
    /* 0x19 */ bool mIsReversed;
    /* 0x1C */ f32 mRate;
    /* 0x20 */ bool mIsRecursive;
    /* 0x24 */ std::tree<nw4r::lyt::AnimTransform*> mAdditionalTransforms; // probably an std::map<u32, nw4r::lyt::AnimTransform*>?
};

}

#endif
