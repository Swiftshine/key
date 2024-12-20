#ifndef FLUFF_NWANM_H
#define FLUFF_NWANM_H

#include "types.h"
#include "gfl/gflResFileInfo.h"

#include <nw4r/g3d.h>

namespace gfl { class ScnMdlWrapper; }
namespace nw4r { namespace g3d { class AnmObj; class ResMdl; } }

class NwAnm {
public:
    ENUM_CLASS(Flags,
        UseTexPat = 1,
        UseChr = 2,
        
        UseVis = 64,
    );

public:
    NwAnm();
    virtual ~NwAnm();

    void SetModelWrapper(gfl::ScnMdlWrapper*, bool);
    float GetCurrentFrame();
    void SetCurrentFrame(float);
    void SetUpdateRate(float);
    float GetUpdateRate();
    bool IsAnimationDone();
    bool HasAnim();
    void Play(gfl::ResFileObject&, const char* resMdlName, const char* animName, void* resName /* ?*/ );
    bool Init(nw4r::g3d::ResFile& resFile, const char* resMdlName, const char* animName, nw4r::g3d::ResName* resName /* ? */);
    nw4r::math::VEC3 GetPosition(gfl::ScnMdlWrapper*, nw4r::g3d::ResMdl& resMdl);

    inline uint GetFlags() {
        return mFlags;
    }
public:
    uint mFlags;
    float mAnimationEndFrame;
    uint m_C;

    class nw4r::g3d::AnmObj* mTexPatAnim; // TexPatRes
    class nw4r::g3d::AnmObj* mMatClrAnim; // MatClrRes
    class nw4r::g3d::AnmObj* mTexSrtAnim; // TexSrtRes
    class nw4r::g3d::AnmObj* mChrAnim; // ChrRes
    class nw4r::g3d::AnmObj* mVisAnim; // VisRes
    class nw4r::g3d::AnmObj* mShpAnim; // ShpRes
};

// ASSERT_SIZE(NwAnm, 0x28);

#endif
