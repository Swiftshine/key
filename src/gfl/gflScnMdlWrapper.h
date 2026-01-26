#ifndef GFL_SCNMDLWRAPPER_H
#define GFL_SCNMDLWRAPPER_H

#include <nw4r/g3d/g3d_scnmdl.h>
#include <nw4r/g3d/g3d_scnmdlexpand.h>

#include "gflAlloc.h"
#include "gflColor.h"
#include "gflMtx34.h"
#include "gflPointer.h"
#include "gflRenderObj.h"

namespace gfl {
    /// @note Size: `0xC`
    class ScnMdlExpandWrapper {
    public:
        inline ScnMdlExpandWrapper() {
            // blah
        }

        /* 0x8 */ inline virtual ~ScnMdlExpandWrapper() {
            if (mScnMdlExpand != nullptr) {
                mScnMdlExpand->Destroy();
            }
        }

        /* Class Members */

        /* 0x4 */ bool mOptionsSet;
        /* 0x8 */ nw4r::g3d::ScnMdlExpand* mScnMdlExpand;
    };

    /// @note Size: `0x34`
    class ScnMdlWrapper : public RenderObj {
    private:
        struct ByteCodeBuf {
            DECL_WEAK ByteCodeBuf();
            ~ByteCodeBuf();

            void* mPtr;
        };
    public:
        static float DefaultUpdateRate;

        ScnMdlWrapper(void* pData, uint bufferOptions, const char* pName);

        ScnMdlWrapper();
        ScnMdlWrapper(nw4r::g3d::ResMdl& rResMdl, uint flags);
        
        /* Virtual Methods */

        /* 0x08 */ virtual ~ScnMdlWrapper();

        /* 0x50 */ virtual bool SetMatrix(const gfl::Mtx34& rMtx);
        /* 0x54 */ virtual void SetMatrix_thunk(const gfl::Mtx34& rMtx);
        /* 0x58 */ virtual bool GetMatrix(gfl::Mtx34& rMtx);
        
        /* Overrides */

        /* 0x10 */ virtual nw4r::g3d::G3dObj* GetObject() override;
        /* 0x18 */ virtual void vf18(bool arg1) override;
        /* 0x20 */ virtual void vf20(bool arg1) override;
        /* 0x28 */ virtual gfl::Vec3 vf28() override;
        /* 0x38 */ virtual void Update(bool shouldUpdate) override;
        /* 0x40 */ virtual void UpdateFrame() override;
        /* 0x44 */ virtual void DoG3dProc(void* pInfo) override;
        
        /* Class Methods */

        void SetChanAmbColor_Color(gfl::Color color);
        void SetChanAmbColor_Alpha(u8 alpha);

        void GetShadowOffset(nw4r::math::VEC2& dst, const char*);
        inline nw4r::g3d::ScnMdl* GetScnMdl() { return mScnMdl; }
        void fn_8004DB94(nw4r::math::VEC3&);
        void fn_8065DCDC(float);
        nw4r::g3d::ResMdl GetResMdl(const char* modelName);
        
        /* Static Methods */

        static void SetDefaultUpdateRate(float rate);

        /* 0x18 */ ByteCodeBuf mByteCodeXlu;
        /* 0x1C */ bool mOptionsSet;
        /* 0x20 */ gfl::Vec3 m_20;
        /* 0x2C */ nw4r::g3d::ScnMdl* mScnMdl;
        /* 0x30 */ gfl::Pointer<ScnMdlExpandWrapper> mExpandWrapper;
    };
}


#endif
