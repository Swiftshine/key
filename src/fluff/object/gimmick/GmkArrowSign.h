#ifndef FLUFF_GMKARROWSIGN_H
#define FLUFF_GMKARROWSIGN_H

#include <vector>
#include "object/Gimmick.h"
#include "graphics/ModelWrapper.h"
#include "graphics/NwAnm.h"
#include "misc/ScopedPointers.h"
#include "graphics/FlfMdlDraw.h"


// size: 0x154
class GmkArrowSign : public Gimmick {
public:
    ENUM_CLASS(Parameter,
        Angle = 0, // int 0
        Texture = 1, // int 1
    );
    
    ENUM_CLASS(TextureType,
        Red = 0,
        Yellow = 1,
        TubeTown = 2,
        Blue = 3,
        BlubBlubOcean = 4,
        MysteriousUFO = 5
    );
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
    gfl::ScopedPointer<ModelWrapper> mArrowModel; // @ 0x130
    gfl::ScopedPointer<ModelWrapper> mBaseModel; // @ 0x134
    std::vector<ModelWrapper> mPoleUnitModels; // @ 0x138, size: 0xC
    gfl::ScopedPointer<NwAnm> mAnimations[2]; // @ 0x144
    gfl::ScopedPointer<FlfMdlDraw> mFlfMdlDraw; // @ 0x14C, for NURBS rendering
    BOOL mIsMysteriousUFO;  // @ 0x150
};

#endif
