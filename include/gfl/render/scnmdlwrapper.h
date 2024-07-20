#ifndef GFL_SCN_MDL_WRAPPER_H
#define GFL_SCN_MDL_WRAPPER_H

#include <nw4r/g3d/g3d_scnmdl.h>
// #include <nw4r/g3d/g3d_lightobj.h>
#include <flf_types.h>
#include <gfl/render/renderobj.h>

namespace nw4r { namespace g3d {
    class LightObjData;
    class LightObj {
        LightObjData* data;
    };
} }

namespace gfl {
    class ScnMdlWrapper : public RenderObj {
    public:
        ScnMdlWrapper();
        virtual ~ScnMdlWrapper();

    public:
        nw4r::g3d::LightObj lightObj;
        bool _1C;
        u8 pad[3];
        Vec3f _20;
        nw4r::g3d::ScnMdl* sceneModel;
        void* _30;
    };

    ASSERT_SIZE(ScnMdlWrapper, 0x34)
}

#endif
