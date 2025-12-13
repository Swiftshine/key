#ifndef GFL_CUSTOMRENDEROBJ_H
#define GFL_CUSTOMRENDEROBJ_H

#include "gflRenderObj.h"
#include "gflVec3.h"

namespace gfl {
    class CustomRenderObj : public nw4r::g3d::ScnLeaf, public gfl::RenderObj {
    public:
        CustomRenderObj(bool opa, bool xlu, const char* pName = nullptr);

        /* gfl::CustomRenderObj */

        /* 0x84 */ virtual void vf84();
        /* 0x88 */ virtual void vf88();
        /* 0x8C */ virtual void vf8C();
        /* 0x90 */ virtual void vf90();
        /* 0x94 */ virtual void vf94(bool arg1);
        /* 0x98 */ virtual void vf98(bool arg1);
        /* 0x9C */ virtual void ToggleUpdate(bool update);
        /* 0xA0 */ virtual void vfA0();
        /* 0xA4 */ virtual void FrameUpdate();
        /* 0xA8 */ virtual void ScnLeafProc(void* pArg1);
        /* 0xAC */ virtual void DoFrameUpdate();
        /* 0xB0 */ virtual void BeforeCalcWorld(void* pInfo, u32* pParam);  // usually, this does nothing
        /* 0xB4 */ virtual void AfterCalcWorld(void* pInfo, u32* pParam);   // ^
        /* 0xB8 */ virtual void BeforeCalcView(void* pInfo, u32* pParam);   // ^
        /* 0xBC */ virtual void AfterCalcView(void* pInfo, u32* pParam);    // ^
        /* 0xC0 */ virtual void DrawOpa();
        /* 0xC4 */ virtual void DrawXlu();

        /* nw4r::g3d::ScnLeaf */

        /* 0x0C */ virtual void G3dProc(u32 task, u32 param, void* pInfo) override;
        /* 0x10 */ virtual ~CustomRenderObj();

        /* gfl::RenderObj */

        virtual DECL_WEAK nw4r::g3d::G3dObj* GetObject() override;
        virtual void vf18(bool arg1) override;
        virtual void vf20(bool arg1) override;
        virtual gfl::Vec3 vf28() override;
        virtual void Update(bool shouldUpdate) override;
        virtual void UpdateFrame() override;
        virtual void ScnMdlProc(int) override;
    private:
        /* 0x100 */ bool mOpa;
        /* 0x101 */ bool mXlu;
        /* 0x102 */ bool mOptionsSet;
        PAD(1);
    };
}

#endif
