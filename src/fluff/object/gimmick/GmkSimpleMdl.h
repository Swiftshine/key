#ifndef FLUFF_GMKSIMPLEMDL_H
#define FLUFF_GMKSIMPLEMDL_H

#include <string>
#include "types.h"

#include "object/Gimmick.h"
#include "gfl/gflResFileInfo.h"
#include "gfl/gflResArchivedFileInfo.h"
#include "gfl/gflScnMdlWrapper.h"
#include "gfl/gflPointer.h"
#include "object/gimmick/GmkSimpleMdlRotZ.h"
#include "graphics/NwAnm.h"

class GmkSimpleMdl : public Gimmick {
public:
    static const char BRRES_path_template[];
    static const char MDL0_name_template[];

    enum Parameter {
        eParameter_SortSceneIndex = 0, // s32 0
        eParameter_ZRotation = 0,     // f32 0
        eParameter_ResourceName = 0,   // string 0

        eParameter_PlayAnim = 1,       // s32 1

        eParameter_InitialFrameIndex = 2, // s32 2
        eParameter_AnimationSpeed = 2, // f32 2
    };
public:
    GmkSimpleMdl();
    GmkSimpleMdl(GimmickBuildInfo* buildInfo);
    virtual ~GmkSimpleMdl();
    void SetModelWrapperByFullSortSceneIndex(s32 index) DONT_INLINE_CLASS;
    void SetModel(const char* brres, const char* modelName, bool playAnim) DONT_INLINE_CLASS;
    void UpdateModel() DONT_INLINE_CLASS;
    virtual void SetState(FlfGameObj* pSetter, const std::string& rState) override;
    gfl::ScnMdlWrapper* CreateModelWrapper(nw4r::g3d::ResFile& resFile, const char* filepath, u32 flag) DONT_INLINE_CLASS;
    NwAnm* CreateAnim(nw4r::g3d::ResFile& resFile, const char* resMdlName, const char* animName) DONT_INLINE_CLASS;
    void SetShadow(nw4r::g3d::ResFile& resFile, const char* name, bool createAnim) DONT_INLINE_CLASS;

public:
    gfl::Pointer<gfl::ScnMdlWrapper> mModelWrapper;
    gfl::Pointer<NwAnm> mAnim;
    gfl::Pointer<gfl::ScnMdlWrapper> mShadowModelWrapper;
    gfl::Pointer<NwAnm> mShadowAnim;
    nw4r::math::VEC3 mModelScale;
    gfl::Pointer<GmkSimpleMdlRotZ> mZRotationGmk;
    gfl::ResFileObject mResFileObject;
    // gfl::ResFileInfo* mResFileInfo;
    u32 m_154;
};


#endif
