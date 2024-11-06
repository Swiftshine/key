#ifndef GFL_RENDEROBJ_H
#define GFL_RENDEROBJ_H

#include "types.h"
#include <revolution/MEM.h>
#include <nw4r/g3d/g3d_scnobj.h>
#include <nw4r/g3d.h>
#include "gfl_types.h"

namespace gfl {
    class Scene;

    class RenderObj {
    public:
        RenderObj();
        virtual ~RenderObj();

        void SetActive(bool state);

        static bool XluSortCheck(nw4r::g3d::ScnLeaf* scnleaf, gfl::RenderObj* renderObj);
        static bool OpaSortCheck(nw4r::g3d::ScnLeaf* scnleaf, gfl::RenderObj* renderObj);

        virtual void vf0C();
        DECL_WEAK virtual nw4r::g3d::G3dObj* GetObject();
        virtual void SetUpdate(bool shouldUpdate);
        virtual void vf18(bool arg1);
        virtual bool vf1C();
        virtual void vf20(bool arg1);
        virtual void vf24();
        virtual void vf28(nw4r::math::VEC3& arg1) = 0;
        virtual float vf2C();
        virtual void vf30(float arg1);
        virtual bool vf34(float& arg0, float& arg1, float& arg2, float& arg3);
        virtual void Update(bool shouldUpdate);
        virtual void vf3C();
        virtual void vf40() = 0;
        virtual void ScnMdlProc() = 0;
        DECL_WEAK virtual void SetScene(gfl::Scene* scene);
        virtual gfl::Scene* GetScene();
    public:
        MEMAllocator* mAllocator;
        Scene* mScene;
        bool m_C;
        bool m_D;
        bool mShouldUpdate;
        bool mIsActive;
        f32 m_10;
        u32 m_14;
    };
};

#endif
