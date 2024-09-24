#ifndef GFL_SCNMDLWRAPPER_H
#define GFL_SCNMDLWRAPPER_H

#include <nw4r/g3d/g3d_scnmdl.h>
#include "gflRenderObj.h"
#include "gflVec3.h"

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

        inline nw4r::g3d::ScnMdl* GetScnMdl() { return mScnMdl; }
        
        /* gfl::ScnMdlWrapper */
        virtual bool SetMatrix(MTX34* mtx);
        virtual bool SetMatrix_thunk(MTX34* mtx);
        virtual bool GSetMatrix(MTX34* mtx);
    private:
        nw4r::g3d::LightObj mLightObj;
        bool m_1C;
        gfl::Vec3 m_20;
        nw4r::g3d::ScnMdl* mScnMdl;
        void* m_30;
    };

    ASSERT_SIZE(ScnMdlWrapper, 0x34)
}


#endif
