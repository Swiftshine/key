#ifndef FLUFF_FBMOKOMOKO_H
#define FLUFF_FBMOKOMOKO_H

#include <string>

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

    const gfl::Vec3 getTranslation() const {
        return mTranslation;
    }

    bool isAnimPlaying() const {
        return mIsAnimPlaying;
    }

    void setAnimPlaying(bool playing) {
        mIsAnimPlaying = playing;
    }

private:
    /* 0x104 */ u16 mWidescreenHeight;
    /* 0x106 */ u16 mWidth;
    /* 0x108 */ u16 mHeight;
    /* 0x10C */ GXTexFmt mTexFormat;
    /* 0x110 */ void* mImageBuffer;
    /* 0x114 */ gfl::Vec3 mTranslation;
    /* 0x120 */ gfl::Vec2 mPosition;
    /* 0x12C */ std::string mStartAnimName;
    /* 0x138 */ std::string mEndAnimName;
    /* 0x144 */ gfl::Pointer<placeholder_t> m_144;
    /* 0x148 */ MokoMokoMdl* mMokoMokoMdl;
    /* 0x14C */ gfl::ScnMdlWrapper* mScnMdlWrapper;
    /* 0x150 */ bool mIsAnimPlaying;
};

#endif
