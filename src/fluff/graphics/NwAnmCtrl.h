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

class NwAnmCtrl {
public:
    /* Constructor */

    NwAnmCtrl(uint animCount, gfl::ResFileObject& fileInfo, const char* animName);

    /* Virtual Methods */

    /* 0x08 */ virtual ~NwAnmCtrl();

    /* Class Methods */
    
    void PlayAnimationByNameAndIndex(uint animIndex, const char* pAnimName, int dummy = 1);
    gfl::ScnMdlWrapper* SetupModelWrapper(uint flags) DONT_INLINE_CLASS;
    void SetFullSortSceneModelWrapper(FullSortScene* pScene, uint flags) DONT_INLINE_CLASS;
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
    nw4r::math::VEC3 GetCurrentAnimationPosition(nw4r::g3d::ResMdl& rResMdl);
    
    inline NwAnm* GetCurrentAnimation() {
        return GetAnimationByIndex(mCurrentAnimIndex);
    }

    /* Class Members */

    /* 0x */ gfl::ResFileObject mResFileInfo;
    /* 0x */ gfl::Pointer<gfl::ScnMdlWrapper> mScnMdlWrapper;
    /* 0x */ std::string mResMdlName;
    /* 0x */ uint mCurrentAnimIndex;
    /* 0x */ gfl::Array<NwAnm> mAnimations;
    /* 0x */ uint mNumAnims;
};

// ASSERT_SIZE(NwAnmCtrl, 0x24);

#endif
