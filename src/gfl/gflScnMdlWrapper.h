#ifndef GFL_SCNMDLWRAPPER_H
#define GFL_SCNMDLWRAPPER_H

#include <nw4r/g3d/g3d_scnmdl.h>
#include "gflRenderObj.h"
#include "gflAlloc.h"
#include "gflScnMdlExpandWrapper.h"

namespace gfl {
    class ScnMdlWrapper : public RenderObj {
    public:
        ScnMdlWrapper();
        ScnMdlWrapper(nw4r::g3d::ResMdl& resMdl, uint flags);
        ScnMdlWrapper(nw4r::g3d::ResMdl& resMdl, uint flags, const char* name);
        
        virtual ~ScnMdlWrapper();

        inline nw4r::g3d::ScnMdl* GetScnMdl() { return mScnMdl; }
        
        void fn_8004DB94(nw4r::math::VEC3&);
        void fn_8065DCDC(float);
        nw4r::g3d::ResMdl GetResMdl(const char* modelName);

        /* gfl::RenderObj */
        virtual gfl::Vec3 vf28() override;
        virtual void UpdateFrame() override;
        virtual void ScnMdlProc(int) override;
        
        /* gfl::ScnMdlWrapper */
        virtual bool SetMatrix(nw4r::math::MTX34& mtx);
        virtual bool SetMatrix_thunk(nw4r::math::MTX34& mtx);
        virtual bool GetMatrix(nw4r::math::MTX34& dest);

        void GetShadowOffset(nw4r::math::VEC2& dst, const char*);
    private:
        /* 0x18 */ void* m_18;
        /* 0x1C */ bool mIsVisible;
        /* 0x20 */ nw4r::math::VEC3 m_20;
        /* 0x2C */ nw4r::g3d::ScnMdl* mScnMdl;
        /* 0x30 */ ScnMdlExpandWrapper* mScnMdlExpandWrapper;
    };

    ASSERT_SIZE(ScnMdlWrapper, 0x34);
}


#endif
