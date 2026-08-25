#ifndef FLUFF_ENVMANAGER_H
#define FLUFF_ENVMANAGER_H

#include <deque>
#include <nw4r/math.h>
#include "types.h"
#include "env/EnvObject.h"
#include "gfl/gflResFileInfo.h"

namespace env {
    // these all inherit from EnvObject
    class EnvFadeSimple;
    class EnvParts_Curtain;
    class EnvCtrl_WipeWindow;

    class EnvManager : public EnvObject {
    public:
        /* Structures */

        struct Substruct {
            f32 m_0;
            f32 m_4;
            s32 m_8;
            s32 m_C;
        };

        enum State {
            eState_LoadSaveDataTex  = 0,
            eState_CreateWipeWindow = 1,
            eState_State2           = 2,
            eState_State3           = 3,
        };

        /* Static Variables */

        static EnvManager* sInstance;

        EnvManager();

        /* Virtual Methods */
        /* 0x08 */ virtual ~EnvManager();
        /* 0x0C */ virtual void Update() override;
        /* 0x10 */ virtual void InitPlayGuide();
        /* 0x14 */ virtual void InitMessage();
        /* 0x18 */ virtual void CreateUnitAndPlayGuide();
        /* 0x1C */ virtual void LoadSaveDataTex();
        /* 0x20 */ virtual void CreateWipeWindow();
        /* 0x24 */ virtual void vf24(); // called for state 2
        /* 0x28 */ virtual void vf28(); // called for state 3

        /* Class Methods */

        void InitInstance(gfl::Task* pParentTask);
        void DestroyInstance();
        EnvManager* fn_80057074();

        /* Class Members */

        /* 0x0C */ std::string mSaveDataTexPath;
        /* 0x18 */ void* m_18;
        /* 0x1C */ std::deque<gfl::ResFileInfo> mSaveDataTex;
        /* 0x28 */ s32 mState;
        /* 0x2C */ gfl::Task* mUpdatePauseTask;
        /* 0x30 */ s32 m_30;
        /* 0x34 */ s32 m_34;
        /* 0x38 */ s32 m_38;
        /* 0x3C */ s32 m_3C;
        /* 0x40 */ s32 m_40;
        /* 0x44 */ s32 m_44;
        /* 0x48 */ s32 m_48;
        /* 0x4C */ f32 m_4C;
        /* 0x50 */ s32 m_50;
        /* 0x54 */ EnvFadeSimple* mEnvFadeSimple;
        /* 0x58 */ EnvParts_Curtain* mEnvPartsCurtain;
        /* 0x5C */ s32 m_5C;
        /* 0x60 */ s32 m_60;
        /* 0x64 */ s32 m_64;
        /* 0x68 */ s32 m_68;
        /* 0x6C */ s32 m_6C;
        /* 0x70 */ s32 m_70;
        /* 0x74 */ nw4r::math::VEC2 m_74;
        /* 0x7C */ Substruct m_7C;
        /* 0x8C */ bool m_8C;
        /* 0x90 */ EnvCtrl_WipeWindow* mEnvCtrlWipeWindow;
        /* 0x94 */ s32 m_94;
    };

    ASSERT_SIZE(EnvManager, 0x98);
}


#endif
