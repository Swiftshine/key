#ifndef FLUFF_NWANMCTRL_H
#define FLUFF_NWANMCTRL_H


#include "types.h"
#include "graphics/NwAnm.h"
#include "gfl/gflScnMdlWrapper.h"
#include "gfl/gflPointer.h"
#include "gfl/gflArray.h"

#include "gfl/gflResFileInfo.h"
#include "gfl/gflResArchivedFileInfo.h"
#include "gfl/gflMemoryManagement.h"
#include "graphics/FullSortScene.h"

#include <string>
#include <memory>


class ResArchivedFileInfo;


class NwAnmCtrl {
public:
    NwAnmCtrl(uint animCount, gfl::ResFileObject& fileInfo, const char* animName);
    virtual ~NwAnmCtrl();
    void PlayAnimationByNameAndIndex(uint animIndex, const char* animName, int dummy = 1);
    gfl::ScnMdlWrapper* SetupModelWrapper(uint flags) DONT_INLINE_CLASS;
    void SetFullSortSceneModelWrapper(FullSortScene* scene, uint flags) DONT_INLINE_CLASS;
    void SetStageFullSortSceneModelWrapper(uint flags) DONT_INLINE_CLASS;
    uint CalculateFlags();
    NwAnm* GetAnimationByIndex(uint index) DONT_INLINE_CLASS;
    void SetCurrentAnimationIndex(uint index);
    f32 GetEndFrame();
    f32 GetCurrentFrame();
    void SetCurrentFrame(f32);
    void SetUpdateRate(f32);
    f32 GetUpdateRate();
    bool IsAnimationDone();
    bool HasAnim(uint index);
    nw4r::math::VEC3 GetCurrentAnimationPosition(nw4r::g3d::ResMdl& resmdl);
    
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

private:
    gfl::ResFileObject mResFileInfo;
    gfl::Pointer<gfl::ScnMdlWrapper> mModelWrapper;
    std::string mResMdlName;
    uint mCurrentAnimIndex;
    gfl::Array<NwAnm> mAnimations;
    uint mNumAnims;
};

// ASSERT_SIZE(NwAnmCtrl, 0x24);

#endif
