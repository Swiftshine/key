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
    

    NwAnmCtrl(uint animCount, gfl::ResFileObject& rResFileObject, const char* pAnimName);

    /* Virtual Methods */

    /* 0x08 */ virtual ~NwAnmCtrl();

    /* Class Methods */
    
    void PlayAnimationByNameAndIndex(uint animIndex, const char* pAnimName, int dummy = 1);
    gfl::ScnMdlWrapper* SetupModelWrapper(uint flags) DONT_INLINE_CLASS;
    gfl::ScnMdlWrapper* SetFullSortSceneModelWrapper(FullSortScene* pScene, uint flags) DONT_INLINE_CLASS;
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

    /* 0x04 */ gfl::ResFileObject mResFileObject;
    /* 0x08 */ gfl::Pointer<gfl::ScnMdlWrapper> mScnMdlWrapper;
    /* 0x0C */ std::string mResMdlName;
    /* 0x18 */ uint mCurrentAnimIndex;
    /* 0x1C */ gfl::Array<NwAnm> mAnimations;
    /* 0x20 */ uint mNumAnims;
};

// ASSERT_SIZE(NwAnmCtrl, 0x24);

#endif
