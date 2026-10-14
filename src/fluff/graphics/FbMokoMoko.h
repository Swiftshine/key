#ifndef FLUFF_FBMOKOMOKO_H
#define FLUFF_FBMOKOMOKO_H

#include <gfl/gflCustomRenderObj.h>
#include <gfl/gflResFileInfo.h>
#include <gfl/gflVec2.h>

#include <graphics/FullSortScene.h>
#include <graphics/NwAnmCtrl.h>
#include <misc/ScopedPointers.h>

class FbMokoMoko;

/// @note Size: `0x20`
class MokoMokoMdl {
public:
    enum PlaybackState {
        ePlaybackState_NotPlaying = 0,
        ePlaybackState_Forward    = 1,
        ePlaybackState_Reverse    = 2
    };

    MokoMokoMdl(FullSortScene::SceneID sceneID, const char* pFilepath, f32 zPos);
    virtual ~MokoMokoMdl();

    gfl::ScnMdlWrapper* GetScnMdlWrapper() const DONT_INLINE_CLASS;
    void Reset(FullSortScene::SceneID sceneID, f32 zPos);
    void PlayAnimation(FbMokoMoko* pFramebuffer);
    void PlayAnimation();
    void SetMatrix(const gfl::Vec2& rTranslation);

private:
    /* 0x04 */ PlaybackState mPlaybackState;
    /* 0x08 */ f32 mZPos;
    /* 0x0C */ gfl::Pointer<NwAnmCtrl> mAnim;
    /* 0x10 */ gfl::ResFileObject mResFileObject;
    /* 0x14 */ gfl::Vec3 mTranslation;
};


// @note Size: `0x154`
class FbMokoMoko : public gfl::CustomRenderObj {
public:
    FbMokoMoko(f32, f32, f32, const char*, gfl::ScnMdlWrapper*, u32, const char*, const char*);
    virtual ~FbMokoMoko();

    /* Class Methods */

    void UpdateMatrix(nw4r::math::VEC2 const &);
    
    const gfl::Vec2 getTranslation() const {
        return mTranslation;
    }

    bool isAnimPlaying() const {
        return mIsAnimPlaying;
    }

    void setAnimPlaying(bool playing) {
        mIsAnimPlaying = playing;
    }

private:
    /* 0x104 */ STRUCT_FILL(0x10);
    /* 0x114 */ gfl::Vec2 mTranslation;
    /* 0x11C */ STRUCT_FILL(0x150 - 0x11C);
    /* 0x150 */ bool mIsAnimPlaying;
};

#endif
