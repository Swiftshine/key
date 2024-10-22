#ifndef GFL_SCNMDLWRAPPER_H
#define GFL_SCNMDLWRAPPER_H

#include <nw4r/g3d/g3d_scnmdl.h>
#include "gflRenderObj.h"

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
        ScnMdlWrapper(nw4r::g3d::ResMdl& resMdl, uint flags);
        
        virtual ~ScnMdlWrapper();

        inline nw4r::g3d::ScnMdl* GetScnMdl() { return mScnMdl; }
        
        void fn_8004DB94(nw4r::math::VEC3&);

        /* gfl::RenderObj */
        virtual void vf28(nw4r::math::VEC3&) override;
        virtual void vf40() override;
        virtual void ScnMdlProc() override;
        
        /* gfl::ScnMdlWrapper */
        virtual bool SetMatrix(MTX34* mtx);
        virtual bool SetMatrix_thunk(MTX34* mtx);
        virtual bool GetMatrix(MTX34* mtx);
    private:
        nw4r::g3d::LightObj mLightObj;
        bool m_1C;
        nw4r::math::VEC3 m_20;
        nw4r::g3d::ScnMdl* mScnMdl;
        void* m_30;
    };

    ASSERT_SIZE(ScnMdlWrapper, 0x34)
}


#endif
