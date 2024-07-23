#ifndef FLUFF_NW_ANM_H
#define FLUFF_NW_ANM_H

#include <flf_types.h>
#include <nw4r/g3d/g3d_obj.h>

class NwAnm {
public:
    NwAnm();
    virtual ~NwAnm();

public:
    u32 _4;
    u32 _8;
    u32 _C;
    nw4r::g3d::G3dObj* _10;
    nw4r::g3d::G3dObj* _14;
    nw4r::g3d::G3dObj* _18;
    nw4r::g3d::G3dObj* _1C;
    nw4r::g3d::G3dObj* _20;
    nw4r::g3d::G3dObj* _24;
};

ASSERT_SIZE(NwAnm, 0x28);


#endif
