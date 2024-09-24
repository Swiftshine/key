#ifndef FLUFF_GMKSIMPLEMDL_H
#define FLUFF_GMKSIMPLEMDL_H

#include <string>
#include "types.h"

#include "object/Gimmick.h"
#include "gfl/gflResFileInfo.h"
#include "gfl/gflResArchivedFileInfo.h"
#include "gfl/gflScnMdlWrapper.h"
#include "gfl/gflScopedPointer.h"
#include "object/gmk/GmkSimpleMdlRotZ.h"
#include "graphics/NwAnm.h"

class GmkSimpleMdl : public Gimmick {
public:
    static const char BRRES_path_template[];
    static const char MDL0_name_template[];

    ENUM_CLASS(Parameter,
        SortSceneIndex = 0, // int 0
        Z_Rotation = 0,     // float 0
        ResourceName = 0,   // string 0


        InitialFrameIndex = 2, // int 2
    );
public:
    GmkSimpleMdl();
    GmkSimpleMdl(GimmickBuildInfo* buildInfo);
    virtual ~GmkSimpleMdl();
    void SetModelWrapperByFullSortSceneIndex(int index);
    void SetModel(const char* brres, const char* modelName, bool playAnim);
    void UpdateModel();
    virtual void SetState(uint arg1, std::string& strState) override;
    gfl::ScnMdlWrapper* CreateModelWrapper(nw4r::g3d::ResFile& resFile, const char* filepath, uint flag);
    NwAnm* CreateAnim(nw4r::g3d::ResFile& resFile, const char* resMdlName, const char* animName);
    void SetShadow(nw4r::g3d::ResFile& resFile, const char* name, bool createAnim);

public:
    gfl::ScopedPointer<gfl::ScnMdlWrapper> mModelWrapper;
    gfl::ScopedPointer<NwAnm> mAnim;
    gfl::ScopedPointer<gfl::ScnMdlWrapper> mShadowModelWrapper;
    gfl::ScopedPointer<NwAnm> mShadowAnim;
    gfl::Vec3 mModelScale;
    gfl::ScopedPointer<GmkSimpleMdlRotZ> mZRotationGmk;
    gfl::ResFileInfoPointer mResFileInfo;
    // gfl::ResFileInfo* mResFileInfo;
    uint m_154;
};


#endif
