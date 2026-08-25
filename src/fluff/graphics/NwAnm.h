#ifndef FLUFF_NWANM_H
#define FLUFF_NWANM_H

#include "types.h"
#include "gfl/gflResFileInfo.h"
#include "gfl/gflScnMdlWrapper.h"
#include <nw4r/g3d/g3d_anmobj.h>

class NwAnm {
public:
    /* Structures */

    enum AnimFlags {
        TexPat  = 1,
        TexChr  = 2,

        Vis     = 64,
    };

    NwAnm();

    /* Virtual Methods */

    /* 0x08 */ virtual ~NwAnm();

    /* Class Methods */

    void SetModelWrapper(gfl::ScnMdlWrapper* pScnMdlWrapper, bool);
    float GetCurrentFrame();
    void SetCurrentFrame(float);
    void SetUpdateRate(float);
    float GetUpdateRate();
    bool IsAnimationDone();
    bool HasAnim();
    void Play(gfl::ResFileObject& rResFileObject, const char* pResMdlName, const char* pAnimName, nw4r::g3d::ResName* pResName /* ?*/ );
    bool Init(nw4r::g3d::ResFile& rResFileObject, const char* pResMdlName, const char* pAnimName, nw4r::g3d::ResName* pResName /* ? */);
    nw4r::math::VEC3 GetPosition(gfl::ScnMdlWrapper* pScnMdlWrapper, nw4r::g3d::ResMdl& rResMdl);

    inline u32 GetFlags() const {
        return mFlags;
    }

    /* Class Members */

    /* 0x04 */ u32 mFlags;
    /* 0x08 */ float mAnimationEndFrame;
    /* 0x0C */ u32 m_C;
    /* 0x10 */ nw4r::g3d::AnmObj* mTexPatAnim;  // TexPatRes
    /* 0x14 */ nw4r::g3d::AnmObj* mMatClrAnim;  // MatClrRes
    /* 0x18 */ nw4r::g3d::AnmObj* mTexSrtAnim;  // TexSrtRes
    /* 0x1C */ nw4r::g3d::AnmObj* mChrAnim;     // ChrRes
    /* 0x20 */ nw4r::g3d::AnmObj* mVisAnim;     // VisRes
    /* 0x24 */ nw4r::g3d::AnmObj* mShpAnim;     // ShpRes
};

// ASSERT_SIZE(NwAnm, 0x28);

#endif
