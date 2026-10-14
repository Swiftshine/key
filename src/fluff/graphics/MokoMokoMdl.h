#ifndef FLUFF_GRAPHICS_MOKOMOKOMDL_H
#define FLUFF_GRAPHICS_MOKOMOKOMDL_H

#include <gfl/gflResFileInfo.h>

#include <graphics/FbMokoMoko.h>
#include <graphics/FullSortScene.h>
#include <graphics/NwAnmCtrl.h>
#include <misc/ScopedPointers.h>

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

    gfl::ScnMdlWrapper* GetScnMdlWrapper() const;
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

#endif
