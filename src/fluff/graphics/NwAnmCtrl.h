#ifndef FLUFF_NWANMCTRL_H
#define FLUFF_NWANMCTRL_H


#include "types.h"
#include "graphics/NwAnm.h"
#include "gfl/gflScnMdlWrapper.h"
#include "gfl/gflScopedPointer.h"
#include "gfl/gflArray.h"
#include "gfl/gflVec3.h"
#include "gfl/gflResFileInfo.h"

#include <string>
#include <memory>


class ResArchivedFileInfo;

class NwAnmCtrl {
public:
    NwAnmCtrl(uint animCount, gfl::ScopedPointer<gfl::ResArchivedFileInfo>& fileInfo, const char* animName);
    virtual ~NwAnmCtrl();
    void PlayAnimationByNameAndIndex(uint animIndex, const char* animName);
    class gfl::ScnMdlWrapper* SetupModelWrapper(uint arg1);
    void SetFullSortSceneModelWrapper(class FullSortScene* scene, uint arg2);
    void SetStageFullSortSceneModelWrapper(uint arg1);
    uint fn_800EA1F4();
    NwAnm* GetAnimationByIndex(uint index) DONT_INLINE;
    void SetCurrentAnimationIndex(uint index);
    f32 GetEndFrame();
    f32 GetCurrentFrame();
    void SetCurrentFrame(f32);
    void SetUpdateRate(f32);
    f32 GetUpdateRate();
    bool IsAnimationDone();
    bool HasAnim(uint index);
    gfl::Vec3& fn_800EA480(nw4r::g3d::ResMdl* resmdl);

    inline NwAnm* GetCurrentAnimation() {
        return GetAnimationByIndex(mCurrentAnimIndex);
    }

    inline void SomeInline(NwAnm** a) {
        delete[] *a;
    }

public:
    gfl::ScopedPointer<gfl::ResArchivedFileInfo> mpFileInfo;
    gfl::ScopedPointer<gfl::ScnMdlWrapper> mpModelWrapper;
    std::string mAnimName;
    uint mCurrentAnimIndex;
    gfl::Array<NwAnm> mpAnimations;
    uint mNumAnims;
};

// ASSERT_SIZE(NwAnmCtrl, 0x24);

#endif