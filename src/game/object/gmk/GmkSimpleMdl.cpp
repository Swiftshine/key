#include <game/object/Gimmick.h>
#include <gfl/file/resfileinfo.h>
#include <game/object/GimmickList.h>
#include <game/object/gmk/GmkSimpleMdlRotZ.h>
#include <gfl/render/scnmdlwrapper.h>

class NwAnm;

// size: 0x158
class GmkSimpleMdl : public Gimmick {
public:
    GmkSimpleMdl();
    void fn_80052E44(s16);
    void fn_80052E48(s16);
    GmkSimpleMdl(GimmickBuildInfo*);

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

ASSERT_SIZE(GmkSimpleMdl, 0x158)

// function declarations
void fn_8003D93C(void*, s16);
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
    int second = buildInfo->intVals[1];
}

asm void GmkSimpleMdl::fn_80052E44(s16 arg1) {
    nofralloc
    b fn_8003D93C
}

asm void GmkSimpleMdl::fn_80052E48(s16 arg1) {
    nofralloc
    b fn_8003D93C
}
