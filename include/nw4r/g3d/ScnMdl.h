#ifndef NW4R_G3D_SCNMDL_H
#define NW4R_G3D_SCNMDL_H

#include <revolution/MEM.h>

namespace nw4r {
namespace g3d {
    class ResMdlData;
    typedef ResMdlData* ResMdl;

    class ScnMdl {
    public:
        ScnMdl* Construct(MEMAllocator*, unsigned long*, nw4r::g3d::ResMdl, unsigned long, int);
    };
    
} // g3d
} // nw4r

#endif
