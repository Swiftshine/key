#ifndef GFL_RENDEROBJ_H
#define GFL_RENDEROBJ_H

#include "types.h"
#include <revolution/MEM.h>
#include <nw4r/g3d/g3d_scnobj.h>
#include "gfl/gflVec3.h"

namespace gfl {
    class Scene;

    class RenderObj {
    public:
        RenderObj();
        virtual ~RenderObj();

        void SetActive(bool state);

        static bool fn_80647DA4(nw4r::g3d::ScnLeaf* scnleaf, gfl::RenderObj* renderObj);
        static bool fn_80647E8C(nw4r::g3d::ScnLeaf* scnleaf, gfl::RenderObj* renderObj);

        virtual void vf0C();
        DECL_WEAK virtual int vf10();
        virtual void SetUpdate(bool shouldUpdate);
        virtual void vf18(bool arg1);
        virtual bool vf1C();
        virtual void vf20(bool arg1);
        virtual void vf24();
        virtual void vf28(gfl::Vec3& arg1) = 0;
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
