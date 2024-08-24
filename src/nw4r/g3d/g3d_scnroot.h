#ifndef NW4R_G3D_SCNROOT_H
#define NW4R_G3D_SCNROOT_H

#include "nw4r/types_nw4r.h"
#include "g3d_scnobj.h"
#include "g3d_camera.h"
#include "g3d_fog.h"

namespace nw4r
{
    namespace g3d
    {
        class ScnRoot : public ScnGroup
        {
        public:
            static ScnRoot* Construct(MEMAllocator*, u32*, u32, u32, u32, u32);
            
            Camera GetCamera(int);
            Camera GetCurrentCamera();
            void SetCurrentCamera(int);
            Fog GetFog(int);

            void UpdateFrame();
            void CalcWorld();
            void CalcMaterial();
            void CalcVtx();
            void CalcView();
            void GatherDrawScnObj();
            void ZSort();
            void DrawOpa();
            void DrawXlu();

            u8 GetCurrentCameraID() const { return mCameraId; }

        private:
            u32 WORD_0xE8;
            u32 WORD_0xEC;
            u32 WORD_0xF0;
            u8 mCameraId;
        };
    }
}

#endif
