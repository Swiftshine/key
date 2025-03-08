#ifndef FLUFF_GMKWARPEXIT_H
#define FLUFF_GMKWARPEXIT_H

#include "object/Gimmick.h"
#include "misc/ScopedPointers.h"
#include "graphics/NwAnmCtrl.h"
#include "graphics/FbMokoMoko.h"
#include <nw4r/g3d.h>

// size: 0x144
class GmkWarpExit : Gimmick {
public:
    static GmkWarpExit* Build(GimmickBuildInfo* buildInfo);
    GmkWarpExit(GimmickBuildInfo* buildInfo);
    virtual ~GmkWarpExit();

    /* FlfGameObj */
    virtual void vf64(bool);
    
    /* Gimmick */
    void Update();
private:
    uint mFullSortSceneIndex; // @ 0x130
    float mZOrder3; // @ 0x134
    float mZOrder4; // @ 0x138
    gfl::Pointer<NwAnmCtrl> mAnimCtrl; // @ 0x13C
    G3dObjPointer<FbMokoMoko> mFbMokoMoko; // @ 0x140
};


#endif
