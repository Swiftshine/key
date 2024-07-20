#ifndef GFL_RENDER_OBJ_H
#define GFL_RENDER_OBJ_H

#include <flf_types.h>
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
        MEMAllocator* allocator;
        FullSortScene* fullSortScene;
        bool _C;
        bool _D;
        bool _E;
        bool active;
        f32 _10;
        u32 _14;
    };

    ASSERT_SIZE(RenderObj, 0x18)
}

#endif
