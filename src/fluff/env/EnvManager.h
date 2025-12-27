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
            float m_0;
            float m_4;
            int m_8;
            int m_C;
        };

        ENUM_CLASS(State,
            LoadSaveDataTex =  0,
            CreateWipeWindow = 1,
            State_2 = 2,
            State_3 = 3
        );

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
        /* 0x28 */ int mState;
        /* 0x2C */ gfl::Task* mUpdatePauseTask;
        /* 0x30 */ int m_30;
        /* 0x34 */ int m_34;
        /* 0x38 */ int m_38;
        /* 0x3C */ int m_3C;
        /* 0x40 */ int m_40;
        /* 0x44 */ int m_44;
        /* 0x48 */ int m_48;
        /* 0x4C */ float m_4C;
        /* 0x50 */ int m_50;
        /* 0x54 */ EnvFadeSimple* mEnvFadeSimple;
        /* 0x58 */ EnvParts_Curtain* mEnvPartsCurtain;
        /* 0x5C */ int m_5C;
        /* 0x60 */ int m_60;
        /* 0x64 */ int m_64;
        /* 0x68 */ int m_68;
        /* 0x6C */ int m_6C;
        /* 0x70 */ int m_70;
        /* 0x74 */ nw4r::math::VEC2 m_74;
        /* 0x7C */ Substruct m_7C;
        /* 0x8C */ bool m_8C;
        /* 0x90 */ EnvCtrl_WipeWindow* mEnvCtrlWipeWindow;
        /* 0x94 */ int m_94;
    };

    // ASSERT_SIZE(EnvManager, 0x98);
}


#endif
