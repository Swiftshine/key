#include <cstdio>
#include <gfl/file/ResFileInfo.h>
#include <gfl/render/ScnMdlWrapper.h>
#include <game/object/Gimmick.h>
#include <game/object/GimmickList.h>
#include <game/object/gmk/GmkSimpleMdlRotZ.h>
#include <game/stage/FullSortScene.h>
#include <game/graphics/NwAnm.h>



// size: 0x158
class GmkSimpleMdl : public Gimmick {
public:
    static const char BRRES_path_template[];
    static const char MDL0_name_template[];
public:
    GmkSimpleMdl();
    void fn_80052E44(s16);
    void fn_80052E48(s16);
    GmkSimpleMdl(GimmickBuildInfo*);

    void SetModel(const char* brres, const char* modelName, bool playAnim);
    void UpdateModel();


    // virtual functions
    virtual ~GmkSimpleMdl();
    void vf4C(u32 arg1, gfl::BasicString* arg2) override;    

public:
    gfl::ScnMdlWrapper* modelWrapper;
    NwAnm* anim1;
    NwAnm* curAnim;
    NwAnm* anim3;
    Vec3f _140;
    GmkSimpleMdlRotZ* subRotationGmk;
    gfl::ResArchivedFileInfo* fileInfo;
    u32 _154;
};

const char GmkSimpleMdl::BRRES_path_template[] = "bggimmick/%s/%s.brres";
const char GmkSimpleMdl::MDL0_name_template[] = "%s_00_000";

ASSERT_SIZE(GmkSimpleMdl, 0x158)

// function declarations
void fn_8003D93C(void*, s16);
float GetZOrder(int sceneIndex, int arg1);
// 

GmkSimpleMdl::GmkSimpleMdl()
    : Gimmick(GimmickIDs::GMK_TYPE_SIMPLE_MDL)

    , modelWrapper(NULL)
    , anim1(NULL)
    , curAnim(NULL)
    , anim3(NULL)
    , subRotationGmk(NULL)
    , fileInfo(NULL)
    , _140()
{ }

GmkSimpleMdl::GmkSimpleMdl(GimmickBuildInfo* buildInfo)
    : Gimmick(GimmickIDs::GMK_TYPE_SIMPLE_MDL, buildInfo)
    
    , modelWrapper(NULL)
    , anim1(NULL)
    , curAnim(NULL)
    , anim3(NULL)
    , subRotationGmk(NULL)
    , fileInfo(NULL)
    , _140()
{
    int useAnim = buildInfo->intVals[1];
    int id = this->GetGimmickID();
    const char* firstString;
    char brresPath[0x200];
    char resMdlName[0x200];

    if (id - 2 < GimmickIDs::SimpleMdlCommon) {
        gfl::BasicString* bs = &buildInfo->stringVals[0];
        if (GFL_BASIC_STRING_CHECK_USE_STRING(bs)) {
            firstString = bs->string;
        } else {
            firstString = (char*)(bs) + 0x1;
        }

        snprintf(brresPath, 0x200, BRRES_path_template, firstString, firstString);
        snprintf(resMdlName, 0x200, MDL0_name_template, firstString);
        SetModel(brresPath, resMdlName, useAnim != false);
        int sortScene = buildInfo->intVals[0] + 6;
        position.z = GetZOrder(sortScene, 4);
        UpdateModel();
    }
}

// asm void GmkSimpleMdl::fn_80052E44(s16 arg1) {
//     nofralloc
//     b fn_8003D93C
// }

// asm void GmkSimpleMdl::fn_80052E48(s16 arg1) {
//     nofralloc
//     b fn_8003D93C
// }

// asm GmkSimpleMdlRotZ::~GmkSimpleMdlRotZ(void) {
//     nofralloc
//     b common_dtor
// }
