#ifndef FLUFF_GMK_SIMPLE_MDL_ROT_Z
#define FLUFF_GMK_SIMPLE_MDL_ROT_Z

#include <game/object/Gimmick.h>
#include <nw4r/g3d/ScnMdl.h>

class GmkSimpleMdlRotZ {
public:
    GmkSimpleMdlRotZ(nw4r::g3d::ScnMdl*);

    virtual ~GmkSimpleMdlRotZ();
    virtual void vfC(nw4r::g3d::ScnMdl*, u32, void*);
    virtual void vf10();
    virtual void vf14();
    
public:
    float rotation;
    int _8;
    int _C;
};

ASSERT_SIZE(GmkSimpleMdlRotZ, 0x10)

#endif
