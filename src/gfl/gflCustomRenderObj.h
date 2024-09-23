#ifndef GFL_CUSTOMRENDEROBJ_H
#define GFL_CUSTOMRENDEROBJ_H

#include "gflRenderObj.h"

namespace gfl {
    class CustomRenderObj : public nw4r::g3d::ScnLeaf, public gfl::RenderObj {
    public:
        CustomRenderObj(bool arg1, bool arg2);

        /* nw4r::g3d::ScnLeaf */

        virtual void G3dProc(u32, u32, void*) override;
        virtual ~CustomRenderObj();

        /* gfl::RenderObj */

        virtual int vf10() override;
        virtual void vf18() override;
        virtual void vf20(float& arg1) override;
        virtual void vf28() override;
        virtual void SetUpdate(bool arg1) override;
        virtual void vf40() override;
        virtual void vf44() override;

        /* gfl::CustomRenderObj */
        virtual void vf78();
        virtual void vf7C();
        virtual void vf80();
        virtual void vf84();
        virtual void vf88();
        virtual void vf8C();
        virtual void vf90();
        virtual void vf94();
        // calls nw4r::g3d::ScnLeaf::G3dProc(1, 0, arg1)
        virtual void Proc(void* arg1); 
        virtual void vf9C();
        virtual void vfA0();
        virtual void vfA4();
        virtual void vfA8();
        virtual void vfAC();
        virtual void vfB0();
        virtual void Render();
    private:
        bool m_100;
        bool m_101;
        bool m_102;
    };
}

#endif
