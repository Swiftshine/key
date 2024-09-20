#ifndef GFL_CUSTOMRENDEROBJ_H
#define GFL_CUSTOMRENDEROBJ_H

#include "gflRenderObj.h"

namespace gfl {
    class CustomRenderObj : public nw4r::g3d::ScnLeaf, public gfl::RenderObj {
    public:
        CustomRenderObj(bool arg1, bool arg2);
        void Destroy();
        void fn_8065D0E8(bool arg1);
        void fn_8065D1F0(bool arg1);
        void fn_8065D304(bool arg1);
        void fn_8065D374();
        void G3dProc(void* arg1);
        void fn_8065D5C4(void* arg1);
        void fn_8065D5D0(void* arg1);

        virtual void G3dProc(unsigned long, unsigned long, void*) override;
        virtual ~CustomRenderObj();
    private:
        bool m_100;
        bool m_101;
        bool m_102;
    };
}

#endif
