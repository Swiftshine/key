#ifndef FLUFF_GIMMICK_H
#define FLUFF_GIMMICK_H

#include <game/object/FlfGameObj.h>
#include <gfl/string/BasicString.h>
#include <game/stage/StageTask.h>

class Gimmick;

void fn_8051F7A0(void*, int);


const u32 INVALID_GIMMICK_ID = 0xFFFFFFFF;

extern "C" const char Stage_NullFilename;


class Gimmick : public FlfGameObj {
public:

    class GimmickBuildInfo {
    public:
        class CommonGimmickBuildInfo {
        public:
            bool mIsCommon;
            Gimmick* mpOwner;
        };
    public:
        int mGimmickID;
        Vec3f mPosition;
        Vec3f mRotation;
        bool m_1C;
        u8 m_1D;
        u8 m_1E;
        u8 m_1F;
        u32 m_20;
        u8 m_24;
        u8 m_25;
        u8 m_26;
        u8 m_27;
        u32 m_28;
        u32 m_2C;
        u32 m_30;
        int mIntParams[5];
        f32 mFloatParams[5];
        gfl::BasicString mStringParams[5];
        CommonGimmickBuildInfo* mpExtension;

        inline GimmickBuildInfo()
            : mGimmickID(INVALID_GIMMICK_ID)
            , mPosition()
            , mRotation()

            , m_24(65)
            , m_28(6)
            , m_2C(4)
            , m_30(0)

        {
            mpExtension = NULL;
            m_1C = false;

            for (int i = 0; i < 5; i++) {
                mIntParams[i] = 0;
                mFloatParams[i] = 0.0f;
                mStringParams[i] = &Stage_NullFilename;
            }
        }

        inline ~GimmickBuildInfo() { }

        inline void operator=(GimmickBuildInfo& src) {
            mGimmickID = src.mGimmickID;
            mPosition = src.mPosition;
            mRotation = src.mRotation;
            m_1C = src.m_1C;
            
        }
    };

    ASSERT_SIZE(GimmickBuildInfo, 0x9C)

public:
    // for the most basic gimmicks
    Gimmick(int gmkID);
    // for gimmicks that control things in-level
    Gimmick(int gmkID, const char* taskName);
    // for common gimmicks
    Gimmick(GimmickBuildInfo* info, const char* taskName);
    // similar to above?
    Gimmick(int gmkID, GimmickBuildInfo* info);

    virtual ~Gimmick();

    void fn_8004E650(const char*);

    void fn_8004EC4C();
    void fn_8004ED1C();


    // virtual functions

    void vf40(FlfGameObj*) override;
    void vf64(bool) override;

    virtual void    vf68();
    virtual Vec3f   vf6C();
    virtual u32     GetGimmickID();
    virtual int     vf74();
    virtual int     vf78();
    virtual int     vf7C();
    virtual int     vf80();
    virtual int     vf84();
    virtual int     OnPlayerCollision(class PlayerBase* player);
    virtual int     vf8C();
    virtual int     vf90();
    virtual int     vf94();
    virtual void    vf98();
    virtual int     vf9C();
    virtual void    vfA0();
    virtual int     vfA4();
    virtual Vec2f   vfAC();
    virtual void    vfB0();
    virtual Vec2f   vfB8();
    virtual void    Update();
    virtual void    vfC0();

public:
    int mGimmickID;
    u32 m_84;
    GimmickBuildInfo mStageBuildInfo;
    void* m_124;
    gfl::Task* mpTask;
    u32 m_12C;
};


ASSERT_SIZE(Gimmick, 0x130)

#endif
