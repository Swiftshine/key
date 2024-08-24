#ifndef FLUFF_GMKSIMPLEMDL_H
#define FLUFF_GMKSIMPLEMDL_H

#include <string>

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
public:

    double RandomDouble(uint arg1);
    GmkSimpleMdl();
    virtual ~GmkSimpleMdl();
    void SetModelWrapperBySceneIndex(int index);
    void SetModel(const char* brres, const char* modelName, bool playAnim);
    void UpdateModel();

    void fn_80052E44(s16);
    void fn_80052E48(s16);
    GmkSimpleMdl(GimmickBuildInfo*);



    void vf4C(uint arg1, std::string& arg2) override;
public:
    gfl::ScnMdlWrapper* mPrimaryModelWrapper;
    NwAnm* mPrimaryAnim;
    gfl::ScnMdlWrapper* mSecondaryModelWrapper;
    NwAnm* mSecondaryAnim;
    gfl::Vec3 m_140;
    GmkSimpleMdlRotZ* mZRotationGmk;
    gfl::ResArchivedFileInfo* mFileInfo;
    uint m_154;
};


#endif