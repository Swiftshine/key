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
    ENUM_CLASS(State,
        Idle        = 1,
        Spawn       = 2,
        Complete    = 3,
    );
    
    ENUM_CLASS(Parameter,
        BeadType            = 0, // int 0
        BeadColor           = 1, // int 1
        InitialBeadFunds    = 2, // int 2
    );
public:
    static GmkBeadDrop* Build(GimmickBuildInfo* buildInfo);
    GmkBeadDrop(GimmickBuildInfo* buildInfo, const char* taskName);
    virtual ~GmkBeadDrop();
    void Init(GimmickBuildInfo* buildInfo);

    /* FlfGameObj */
    virtual void SetState(FlfGameObj* setter, std::string& state);
    
    /* Gimmick */
    virtual void Update();
    
    void SetState(int stateValue) DONT_INLINE_CLASS;
    void SpawnBeads();
    bool CanSpawnBeads();
    void UpdateFlfMdl();
    float fn_802E1AEC(float&, float&, nw4r::math::VEC3&);
    void SetSpawnState() DONT_INLINE_CLASS;
private:
    int mState;         // @ 0x130
    int mCounter;       // @ 0x134
    gfl::Vec3 m_138;
    float mCompletionPercentage; // @ 0x144; on a scale of 0.0 to 1.0
    std::string m_148;  // size: 0xC
    BeadDropperInfo mBeadDropperInfo; // @ 0x154, size: 0x1C
    gfl::Pointer<FlfMdlDraw> mFlfMdlDraw; // @ 0x170
    GeneratorInfo mGeneratorInfo; // @ 0x174, size: 0x1C
};


#endif