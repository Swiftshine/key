#ifndef FLUFF_EnvFade_Base_H
#define FLUFF_EnvFade_Base_H

#include <env/EnvManager_Scene.h>
#include <env/EnvObject.h>
#include <env/EnvUtil_State.h>
#include <object/FlfHandleObj.h>
#include <layout/LayoutObject.h>

namespace env {
    class EnvFade_Base : public EnvObject, public FlfHandleObj {
    public:
        enum LocalState {
            eState_State0,
            eState_FadeIn,
            eState_State2,
            eState_FadeOut,
        };

        EnvFade_Base(gfl::Task* pParentTask, EnvManager_Scene* pParentScene, s32 translucency, const char* pTaskName, u32 flagIndex);

        /* 0x08 */ ~EnvFade_Base();
        /* 0x0C */ void Update() override;

        /* 0x1C */ virtual bool FadeInReady() = 0;
        /* 0x20 */ virtual bool FadeOutReady() = 0;
        /* 0x24 */ virtual void vf24() = 0;
        /* 0x28 */ virtual void vf28() = 0;
        /* 0x2C */ virtual void UpdateLayout();
        /* 0x30 */ virtual void vf30() = 0;
        /* 0x34 */ virtual void FadeIn() = 0;
        /* 0x38 */ virtual void vf38() = 0;
        /* 0x3C */ virtual void FadeOut() = 0;

        layout::LayoutObject* CreateLayout(const char* pArchivePath, const char* pLayoutName, const char* pPaneName);
    protected:
        /* 0x18 */ EnvManager_Scene* mScene;
        /* 0x1C */ s32 mPriorityDrawXlu;
        /* 0x20 */ gfl::Pointer<layout::LayoutObject> mLayoutObject;
        /* 0x24 */ nw4r::lyt::Pane* mPane;
        /* 0x28 */ EnvUtil_State<LocalState> mState;
    };
}

#endif
