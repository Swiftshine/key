#ifndef GFL_SCN_MDL_WRAPPER_H
#define GFL_SCN_MDL_WRAPPER_H

#include <nw4r/g3d/g3d_scnmdl.h>
// #include <nw4r/g3d/g3d_lightobj.h>
#include <gfl/gfl_types.h>
#include <gfl/render/RenderObj.h>
#include <gfl/math/Vector3F.h>

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
        nw4r::g3d::LightObj mLightObj;
        bool m_1C;
        gfl::Vec3 m_20;
        nw4r::g3d::ScnMdl* mpScnMdl;
        void* mp_30;
    };

    ASSERT_SIZE(ScnMdlWrapper, 0x34)
}

#endif
