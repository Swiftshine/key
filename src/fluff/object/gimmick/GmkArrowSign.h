#ifndef FLUFF_GMKARROWSIGN_H
#define FLUFF_GMKARROWSIGN_H

#include <vector>
#include "object/Gimmick.h"
#include "graphics/GmkPartsMdlSet.h"
#include "graphics/NwAnm.h"
#include "misc/ScopedPointers.h"
#include "graphics/FlfMdlDraw.h"

// size: 0x154
class GmkArrowSign : public Gimmick {
    struct VectorWrapper {
        ~VectorWrapper() { }

        std::vector<GmkPartsMdlSet*> mVec;
    };
public:
    enum Parameter {
        eParameter_Angle    = 0, // s32 0
        eParameter_Texture  = 1, // s32 1
    };

    enum TextureType {
        eTextureType_Red = 0,
        eTextureType_Yellow = 1,
        eTextureType_TubeTown = 2,
        eTextureType_Blue = 3,
        eTextureType_BlubBlubOcean = 4,
        eTextureType_MysteriousUFO = 5,
    };
public:
    static void AddResourceName(GimmickBuildInfo* buildInfo);
    static GmkArrowSign* Build(GimmickBuildInfo* buildInfo);

    GmkArrowSign(GimmickBuildInfo* buildInfo, const char* taskName) DONT_INLINE_CLASS;
    virtual ~GmkArrowSign();

    /* Gimmick */
    virtual void Update();

    const char* GetOrientationAnimationName();
    static std::string GetResourceName(GimmickBuildInfo* buildInfo);
private:
    /* 0x130 */ gfl::Pointer<GmkPartsMdlSet> mArrowModel;
    /* 0x134 */ gfl::Pointer<GmkPartsMdlSet> mBaseModel;
    /* 0x138 */ VectorWrapper mPoleUnitModels;
    /* 0x144 */ gfl::Pointer<NwAnm> mAnimations[2];
    /* 0x14C */ gfl::Pointer<FlfMdlDraw> mFlfMdlDraw; // for NURBS rendering
    /* 0x150 */ s32 mIsMysteriousUFO;
};

#endif
