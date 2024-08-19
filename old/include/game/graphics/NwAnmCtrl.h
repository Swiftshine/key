#ifndef FLUFF_NW_ANM_CTRL_H
#define FLUFF_NW_ANM_CTRL_H

#include <flf_types.h>
#include <game/graphics/NwAnm.h>
#include <gfl/render/ScnMdlWrapper.h>
#include <gfl/string/BasicString.h>
#include <gfl/mem/ScopedPointer.h>
#include <gfl/container/SimpleArray.h>
// #include <game/stage/FullSortScene.h>
// #include <game/manager/StageManager.h>
// #include <nw4r/g3d/g3d_resmdl.h>



class NwAnmCtrl {
public:
    NwAnmCtrl(u32 animCount, gfl::ScopedPointer<gfl::ResArchivedFileInfo>& fileInfo, const char* animName);
    virtual ~NwAnmCtrl();
    void PlayAnimationByNameAndIndex(u32 animIndex, const char* animName);
    class gfl::ScnMdlWrapper* SetupModelWrapper(u32 arg1);
    void SetFullSortSceneModelWrapper(class FullSortScene* scene, u32 arg2);
    void SetStageFullSortSceneModelWrapper(u32 arg1);
    u32 fn_800EA1F4();
    NwAnm* GetAnimationByIndex(u32 index) DONT_INLINE;
    void SetCurrentAnimationIndex(u32 index);
    f32 GetEndFrame();
    f32 GetCurrentFrame();
    void SetCurrentFrame(f32);
    void SetUpdateRate(f32);
    f32 GetUpdateRate();
    bool IsAnimationDone();
    bool HasAnim(u32 index);
    Vec3f& fn_800EA480(nw4r::g3d::ResMdl* resmdl);

    inline NwAnm* GetCurrentAnimation() {
        return GetAnimationByIndex(mCurrentAnimIndex);
    }

    inline void SomeInline(NwAnm** a) {
        delete[] *a;
    }

public:
    gfl::ScopedPointer<gfl::ResArchivedFileInfo> mpFileInfo;
    gfl::ScopedPointer<gfl::ScnMdlWrapper> mpModelWrapper;
    gfl::BasicString mAnimName;
    u32 mCurrentAnimIndex;
    gfl::SimpleArray<NwAnm> mpAnimations;
    u32 mNumAnims;
};

ASSERT_SIZE(NwAnmCtrl, 0x24)

#endif
