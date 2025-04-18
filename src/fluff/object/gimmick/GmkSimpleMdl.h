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

    ENUM_CLASS(Parameter,
        SortSceneIndex = 0, // int 0
        ZRotation = 0,     // float 0
        ResourceName = 0,   // string 0

        PlayAnim = 1,       // int 1

        InitialFrameIndex = 2, // int 2
    );
public:
    GmkSimpleMdl();
    GmkSimpleMdl(GimmickBuildInfo* buildInfo);
    virtual ~GmkSimpleMdl();
    void SetModelWrapperByFullSortSceneIndex(int index) DONT_INLINE_CLASS;
    void SetModel(const char* brres, const char* modelName, bool playAnim) DONT_INLINE_CLASS;
    void UpdateModel() DONT_INLINE_CLASS;
    virtual void SetState(FlfGameObj* setter, std::string& strState) override;
    gfl::ScnMdlWrapper* CreateModelWrapper(nw4r::g3d::ResFile& resFile, const char* filepath, uint flag) DONT_INLINE_CLASS;
    NwAnm* CreateAnim(nw4r::g3d::ResFile& resFile, const char* resMdlName, const char* animName) DONT_INLINE_CLASS;
    void SetShadow(nw4r::g3d::ResFile& resFile, const char* name, bool createAnim) DONT_INLINE_CLASS;

public:
    gfl::Pointer<gfl::ScnMdlWrapper> mModelWrapper;
    gfl::Pointer<NwAnm> mAnim;
    gfl::Pointer<gfl::ScnMdlWrapper> mShadowModelWrapper;
    gfl::Pointer<NwAnm> mShadowAnim;
    nw4r::math::VEC3 mModelScale;
    gfl::Pointer<GmkSimpleMdlRotZ> mZRotationGmk;
    gfl::ResFileObject mResFileInfo;
    // gfl::ResFileInfo* mResFileInfo;
    uint m_154;
};


#endif
