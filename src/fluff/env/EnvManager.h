#ifndef FLUFF_ENVMANAGER_H
#define FLUFF_ENVMANAGER_H

#include <deque>
#include <nw4r/math.h>
#include "types.h"
#include "env/EnvObject.h"
#include "gfl/gflResFileInfo.h"

namespace env {

    class EnvManager : public EnvObject {
    public:
        static EnvManager* sInstance;

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

        void InitInstance(gfl::Task* parentTask);
        void DestroyInstance();
        EnvManager* fn_80057074();
        EnvManager();
        virtual ~EnvManager();

        virtual void ProcessState();
        virtual void InitPlayGuide();
        virtual void InitMessage();
        virtual void CreateUnitAndPlayGuide();
        virtual void LoadSaveDataTex();
        virtual void CreateWipeWindow();
        virtual void vf24(); // called for state 2
        virtual void vf28(); // called for state 3

        std::string mSaveDataTexPath;
        void* m_18;
        std::deque<gfl::ResFileInfo> mSaveDataTex;
        int mState;
        gfl::Task* mUpdatePauseTask;
        int m_30;
        int m_34;
        int m_38;
        int m_3C;
        int m_40;
        int m_44;
        int m_48;
        float m_4C;
        int m_50;
        EnvObject* mEnvFadeSimple; // env::EnvFadeSimple
        EnvObject* mEnvPartsCurtain; // env::EnvParts_Curtain
        int m_5C;
        int m_60;
        int m_64;
        int m_68;
        int m_6C;
        int m_70;
        nw4r::math::VEC2 m_74;
        Substruct m_7C;
        bool m_8C;
        EnvObject* mEnvCtrlWipeWindow; // env::EnvCtrl_WipeWindow
        int m_94;
    };

    // ASSERT_SIZE(EnvManager, 0x98);
}


#endif
