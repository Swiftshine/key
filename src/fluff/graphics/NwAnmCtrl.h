#ifndef FLUFF_NWANMCTRL_H
#define FLUFF_NWANMCTRL_H


#include "types.h"
#include "graphics/NwAnm.h"
#include "gfl/gflScnMdlWrapper.h"
#include "gfl/gflScopedPointer.h"
#include "gfl/gflArray.h"
#include "gfl/gflVec3.h"
#include "gfl/gflResFileInfo.h"
#include "gfl/gflResArchivedFileInfo.h"
#include "gfl/gflMemoryManagement.h"
#include <string>
#include <memory>


class ResArchivedFileInfo;

class NwAnmCtrl {
public:
    NwAnmCtrl(uint animCount, gfl::ResFileInfoPointer& fileInfo, const char* animName);
    virtual ~NwAnmCtrl();
    void PlayAnimationByNameAndIndex(uint animIndex, const char* animName);
    class gfl::ScnMdlWrapper* SetupModelWrapper(uint arg1);
    void SetFullSortSceneModelWrapper(class FullSortScene* scene, uint arg2);
    void SetStageFullSortSceneModelWrapper(uint arg1);
    uint fn_800EA1F4();
    NwAnm* GetAnimationByIndex(uint index) DONT_INLINE_CLASS;
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

    inline uint GetCurrentAnimationIndex() {
        return mCurrentAnimIndex;
    }

    inline gfl::ScnMdlWrapper* GetScnMdlWrapper() {
        return mModelWrapper.Get();
    }

public:
    gfl::ResFileInfoPointer mFileInfo;
    gfl::ScopedPointer<gfl::ScnMdlWrapper> mModelWrapper;
    std::string mAnimName;
    uint mCurrentAnimIndex;
    gfl::Array<NwAnm> mAnimations;
    uint mNumAnims;
};

// ASSERT_SIZE(NwAnmCtrl, 0x24);

#endif
