#ifndef GFL_RENDEROBJ_H
#define GFL_RENDEROBJ_H

#include "types.h"
#include <revolution/MEM.h>

namespace gfl {
    class FullSortScene;

    class RenderObj {
        RenderObj();
        virtual ~RenderObj();

        virtual void vf0C();
        virtual void vf10();
        virtual void vf14();
        virtual void vf18();
        virtual void vf1C();
        virtual void vf20();
        virtual void vf24();
        virtual void vf28() = 0;
        virtual void vf2C();
        virtual void vf30();
        virtual void vf34();
        virtual void vf38();
        virtual void vf3C();
        virtual void vf40() = 0;
        virtual void vf44() = 0;
        virtual void vf48();
        virtual FullSortScene* GetFullSortScene();
    public:
        MEMAllocator* mpAllocator;
        FullSortScene* mpFullSortScene;
        bool m_C;
        bool m_D;
        bool m_E;
        bool mIsActive;
        f32 m_10;
        u32 m_14;
    };
};

#endif