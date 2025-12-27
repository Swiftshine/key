#ifndef GFL_SCNMDLWRAPPER_H
#define GFL_SCNMDLWRAPPER_H

#include <nw4r/g3d/g3d_scnmdl.h>
#include <nw4r/g3d/g3d_scnmdlexpand.h>

#include "gflRenderObj.h"
#include "gflAlloc.h"

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

        /* 0x4 */ bool mIsVisible;
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

        /* Static Methods */
        static void SetDefaultUpdateRate(float rate);
    private:
        /* 0x18 */ ByteCodeBuf mByteCodeXlu;
        /* 0x1C */ bool mIsVisible;
        /* 0x20 */ gfl::Vec3 m_20;
        /* 0x2C */ nw4r::g3d::ScnMdl* mScnMdl;
        /* 0x30 */ ScnMdlExpandWrapper* mExpandWrapper;
    };
}


#endif
