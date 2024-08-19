#ifndef FLUFF_NW_ANM_H
#define FLUFF_NW_ANM_H

#include <flf_types.h>
// #include <gfl/render/ScnMdlWrapper.h>
#include <gfl/file/ResFileInfo.h>

namespace gfl { class ScnMdlWrapper; }
namespace nw4r { namespace g3d { class AnmObj; class ResMdl; }}
class NwAnm {
public:
    SCOPED_ENUM(Flags,
        UseTexPat = 1,
        UseChr = 2,

        UseVis = 64,
        // UseShp = 28672,
    );
public:
    NwAnm();
    virtual ~NwAnm();

    // void Play(gfl::ResArchivedFileInfo**, )
    void SetModelWrapper(gfl::ScnMdlWrapper*, bool);
    f32 GetCurrentFrame();
    void SetCurrentFrame(f32);
    void SetUpdateRate(f32);
    f32 GetUpdateRate();
    bool IsAnimationDone();
    bool HasAnim();
public:
    u32 mFlags;
    f32 mAnimationEndFrame;
    u32 m_C;


    class nw4r::g3d::AnmObj* mpTexPatAnim; // TexPatRes
    class nw4r::g3d::AnmObj* mpMatClrAnim; // MatClrRes
    class nw4r::g3d::AnmObj* mpTexSrtAnim; // TexSrtRes
    class nw4r::g3d::AnmObj* mpChrAnim; // ChrRes
    class nw4r::g3d::AnmObj* mpVisAnim; // VisRes
    class nw4r::g3d::AnmObj* mpShpAnim; // ShpRes
};

ASSERT_SIZE(NwAnm, 0x28);


#endif