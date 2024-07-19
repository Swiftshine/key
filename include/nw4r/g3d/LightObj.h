#ifndef NW4R_G3D_LIGHTOBJ_H
#define NW4R_G3D_LIGHTOBJ_H

#include <revolution/GX.h>

namespace nw4r {
namespace g3d {

    class LightObjData {
        LightObjData();
        ~LightObjData();
    public:
        u32 mFlags;
        GXLightObj mLightObj;
    };

    class LightObj {
    public:
        LightObj();
        ~LightObj();
    public:
        LightObjData* data;
    };

} // g3d
} // nw4r

#endif
