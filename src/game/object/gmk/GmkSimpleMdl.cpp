#include <game/object/Gimmick.h>
#include <gfl/file/resfileinfo.h>
#include <game/object/GimmickList.h>


namespace gfl { class ScnMdlWrapper; }
class NwAnm;

// size: 0x158
class GmkSimpleMdl : public Gimmick {
public:
    GmkSimpleMdl();
    virtual ~GmkSimpleMdl();

    virtual void fn_8000BC7C() override; // (this, PlayerBase*)
    virtual void fn_8000BC74() override; // (this, undefined4, BasicString*)
public:
    gfl::ScnMdlWrapper* modelWrapper;
    NwAnm* anim1;
    NwAnm* anim2;
    NwAnm* anim3;
    Vec3f _140;
    u32 _14C;
    gfl::ResArchivedFileInfo* fileInfo;
    u32 _154;
};

ASSERT_SIZE(GmkSimpleMdl, 0x158)

GmkSimpleMdl::GmkSimpleMdl()
    : Gimmick(GimmickIDs::GMK_TYPE_SIMPLE_MDL)
{

}
