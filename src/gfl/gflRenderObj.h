#ifndef GFL_RENDEROBJ_H
#define GFL_RENDEROBJ_H

#include "types.h"
#include <revolution/MEM.h>
#include <nw4r/g3d/g3d_scnobj.h>
#include "gfl_types.h"
#include "gflVec3.h"

namespace gfl {
    class Scene;

    class RenderObj {
    public:
        RenderObj();

        void SetActive(bool state);

        /* 0x08 */ virtual ~RenderObj();
        /* 0x0C */ virtual int vf0C();
        /* 0x10 */ DECL_WEAK virtual nw4r::g3d::G3dObj* GetObject();
        /* 0x14 */ virtual void SetUpdate(bool shouldUpdate);
        /* 0x18 */ virtual void vf18(bool arg1);
        /* 0x1C */ virtual bool vf1C();
        /* 0x20 */ virtual void vf20(bool arg1);
        /* 0x24 */ virtual bool vf24();
        /* 0x28 */ virtual gfl::Vec3 vf28() = 0;
        /* 0x2C */ virtual float GetUpdateRate();
        /* 0x30 */ virtual void SetUpdateRate(float rate);
        /* 0x34 */ virtual bool vf34(float arg0, float arg1, float arg2, float arg3);
        /* 0x38 */ virtual void Update(bool shouldUpdate);
        /* 0x3C */ virtual bool ShouldUpdate();
        /* 0x40 */ virtual void UpdateFrame() = 0;
        /* 0x44 */ virtual void ScnMdlProc(int) = 0;
        /* 0x48 */ DECL_WEAK virtual void SetScene(gfl::Scene* scene);
        /* 0x4C */ virtual gfl::Scene* GetScene();
    public:
        /* 0x04 */ MEMAllocator* mAllocator;
        /* 0x08 */ Scene* mScene;
        /* 0x0C */ bool m_C;
        /* 0x0D */ bool m_D;
        /* 0x0E */ bool mShouldUpdate;
        /* 0x0F */ bool mIsActive;
        /* 0x10 */ float mUpdateRate;
        /* 0x14 */ int m_14;
    };
};

#endif
