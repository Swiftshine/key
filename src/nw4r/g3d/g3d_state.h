#ifndef NW4R_G3D_STATE_H
#define NW4R_G3D_STATE_H
#include "nw4r/types_nw4r.h"
#include <revolution/GX.h>

namespace nw4r
{
    namespace g3d
    {
        namespace G3DState
        {
            struct IndMtxOp
            {
            };

            
            void SetViewPosNrmMtxArray(const math::MTX34 *, const math::MTX33 *,
                const math::MTX34 *);

            void SetRenderModeObj(const GXRenderModeObj&);
            GXRenderModeObj* GetRenderModeObj();
            void Invalidate(u32);
            void SetCameraProjMtx(int, bool);
            void SetLightSetting(LightSetting&);
        }
    }
}

#endif
