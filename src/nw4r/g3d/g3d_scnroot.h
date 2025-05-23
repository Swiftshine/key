#ifndef NW4R_G3D_SCNROOT_H
#define NW4R_G3D_SCNROOT_H
#include "nw4r/types_nw4r.h"
#include "g3d_scnobj.h"
#include "g3d_camera.h"
#include "g3d_fog.h"
#include "g3d_light.h"

namespace nw4r
{
    namespace g3d
    {   
        class ScnRoot : public ScnGroup
        {
        public:
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
            void CalcAnmScn();
            void SetGlbSettings();
            
            void SetCameraID(u8 id);

            inline LightSetting& GetLightSetting() {
                return mLightSetting;
            }
        private:
            UNKWORD WORD_0xE8;
            UNKWORD WORD_0xEC;
            UNKWORD WORD_0xF0;
            u8 mCameraId;
            CameraData mCameraData[0x20]; // @ 0xF8
            u8 m_2278[48][0x20];
            LightSetting mLightSetting; // @ 0x2878
            UNKWORD WORD_0x2888;
        };
    }
}

#endif
