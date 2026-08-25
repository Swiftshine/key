#ifndef FLUFF_GMKBEADDROP_H
#define FLUFF_GMKBEADDROP_H

#include "object/Gimmick.h"
#include "util/BeadDropperInfo.h"
#include "util/GeneratorInfo.h"
#include "gfl/gflVec3.h"
#include "graphics/FlfMdlDraw.h"
#include "misc/ScopedPointers.h"

// size: 0x190
class GmkBeadDrop : public Gimmick {
public:
    enum State {
        eState_Idle     = 1,
        eState_Spawn    = 2,
        eState_Complete = 3,
    };

    enum Parameter {
        eParameter_BeadType         = 0, // s32 0
        eParameter_BeadColor        = 1, // s32 1
        eParameter_InitialBeadFunds = 2, // s32 2
    };
public:
    static GmkBeadDrop* Build(GimmickBuildInfo* buildInfo);
    GmkBeadDrop(GimmickBuildInfo* buildInfo, const char* taskName);
    virtual ~GmkBeadDrop();
    void Init(GimmickBuildInfo* buildInfo);

    /* FlfGameObj */
    virtual void SetState(FlfGameObj* setter, const std::string& state);

    /* Gimmick */
    virtual void Update();

    void SetState(s32 stateValue) DONT_INLINE_CLASS;
    void SpawnBeads();
    bool CanSpawnBeads();
    void UpdateFlfMdl();
    f32 fn_802E1AEC(f32, f32, nw4r::math::VEC3&) DONT_INLINE_CLASS;
    void SetSpawnState() DONT_INLINE_CLASS;
private:
    s32 mState;         // @ 0x130
    s32 mCounter;       // @ 0x134
    gfl::Vec3 mOffset;  // @ 0x138
    f32 mCompletionPercentage; // @ 0x144; on a scale of 0.0 to 1.0
    std::string m_148;  // size: 0xC
    BeadDropperInfo mBeadDropperInfo; // @ 0x154, size: 0x1C
    gfl::Pointer<FlfMdlDraw> mFlfMdlDraw; // @ 0x170
    GeneratorInfo mGeneratorInfo; // @ 0x174, size: 0x1C
};


#endif
