#ifndef FLUFF_GMKSIMPLEMDL_H
#define FLUFF_GMKSIMPLEMDL_H

#include <string>
#include "types.h"

#include "object/Gimmick.h"
#include "gfl/gflResFileInfo.h"
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

    // it's likely this function doesn't strictly belong to GmkSimpleMdl,
    // since it's used by GmkSimpleNurbs and GmkColAnimMdl as well
    static float RandomFloat(int arg1);


    GmkSimpleMdl();
    GmkSimpleMdl(GimmickBuildInfo* buildInfo);
    virtual ~GmkSimpleMdl();
    void SetModelWrapperBySceneIndex(int index);
    void SetModel(const char* brres, const char* modelName, bool playAnim);
    void UpdateModel();

    void fn_80052E44(s16);
    void fn_80052E48(s16);



    void vf4C(uint arg1, std::string& arg2) override;
public:
    gfl::ScnMdlWrapper* mPrimaryModelWrapper;
    NwAnm* mPrimaryAnim;
    gfl::ScnMdlWrapper* mSecondaryModelWrapper;
    NwAnm* mSecondaryAnim;
    float m_140;
    float m_144;
    float m_148;
    GmkSimpleMdlRotZ* mZRotationGmk;
    gfl::ResArchivedFileInfo* mFileInfo;
    uint m_154;
};


#endif