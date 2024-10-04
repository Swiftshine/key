#ifndef FLUFF_GIMMICK_H
#define FLUFF_GIMMICK_H

#include "object/FlfGameObj.h"
#include "object/GimmickList.h"
#include "manager/GimmickManager.h"
#include "demo/event_demo/EventDemoGimmickCommand.h"
#include "gflVec3.h"
#include "gflVec2.h"
#include "gflTask.h"

#include <nw4r/math.h>
#include <utility>
#include <string>

extern "C" const char Blank[];

struct GimmickVec {
    float x;
    float y;
    float z;
};

class Gimmick : public FlfGameObj {
public:
    ENUM_CLASS(ParameterID,
        FIRST = 0,
        SECOND = 1,
        THIRD = 2,
        FOURTH = 3,
        FIFTH = 4
    );

    class GimmickBuildInfo {
    public:

        // this constructor was matching a while ago, what happened?
        inline GimmickBuildInfo() {
            const float zero = 0.0f;

            mGimmickID = -1;

            mPosition.x = zero;
            mPosition.y = zero;
            mPosition.z = zero;

            mRotation.x = zero;
            mRotation.y = zero;
            mRotation.z = zero;

            m_24 = 'A';
            m_28 = 6;
            m_2C = 4;
            m_30 = 0;

            mExtension = nullptr;
            m_1C = false;

            for (uint i = 0; i < 5; i++) {
                mIntParams[i] = 0;
                mFloatParams[i] = zero;
                mStringParams[i] = Blank;
            }
        }

        inline ~GimmickBuildInfo() { }

        inline void operator=(GimmickBuildInfo& other) {
            mGimmickID = other.mGimmickID;
            // mPosition = other.mPosition;
            // mRotation = other.mRotation;
            m_1C = other.m_1C;
        }

        inline int GetGimmickID() {
            return mGimmickID;
        }

        inline bool IsCommon() {
            return mExtension->first;
        }

        inline Gimmick* GetOwner() {
            return mExtension->second;
        }

        inline int GetIntParam(int index) {
            return mIntParams[index];
        }

        inline float GetFloatParam(int index) {
            return mFloatParams[index];
        }

        inline std::string& GetStringParam(int index) {
            return mStringParams[index];
        }

        inline bool GetBoolParam(int index) {
            return static_cast<bool>(mIntParams[index]);
        }
    public:
        int mGimmickID;

        union {
            struct {
                float x;
                float y;
                float z;
            };
        } mPosition;

        union {
            struct {
                float x;
                float y;
                float z;
            };

        } mRotation;

        bool m_1C;
        u8 m_1D;
        u8 m_1E;
        u8 m_1F;
        uint m_20;
        u8 m_24;
        u8 m_25;
        u8 m_26;
        u8 m_27;
        uint m_28;
        uint m_2C;
        uint m_30;
        int mIntParams[5];
        float mFloatParams[5];
        std::string mStringParams[5];
        // bool - indicates whether or not this is a common gimmick
        // Gimmick* - owner
        std::pair<bool, Gimmick*>* mExtension;
    };

    // ASSERT_SIZE(GimmickBuildInfo, 0x9C);
public:
    // For the most basic gimmicks
    Gimmick(int gmkID);

    // For gimmicks that control things in-level
    Gimmick(int gmkID, const char* taskName);

    // For common gimmicks
    Gimmick(GimmickBuildInfo* info, const char* taskName);

    // unk
    Gimmick(GimmickBuildInfo* info);

    virtual ~Gimmick();

    void fn_8004E650(const char*);

    void InitCommand();
    void fn_8004ED1C();


    // virtual functions

    void vf40(FlfGameObj*) override;
    void vf64(bool) override;

    virtual void    vf68();
    virtual gfl::Vec3   vf6C();
    virtual u32     GetGimmickID();
    virtual int     vf74();
    virtual int     vf78();
    virtual int     vf7C();
    virtual int     vf80();
    virtual int     vf84();
    virtual bool    vf88(FlfGameObj*, uint arg2);     
    virtual int     vf8C();
    virtual int     vf90();
    virtual int     vf94();
    virtual void    vf98();
    virtual int     vf9C();
    virtual void    vfA0();
    virtual int     vfA4();
    virtual void    vfA8();
    virtual gfl::Vec2   vfAC();
    virtual void    vfB0();
    virtual void    vfB4();
    virtual gfl::Vec2   vfB8();
    virtual void    Update();
    virtual void    vfC0();

public:
    int mGimmickID;
    uint m_84;
    GimmickBuildInfo mBuildInfo;
    void* m_124;
    gfl::Task* mTask;
    demo::EventDemoGimmickCommand* mCommand;
};


// ASSERT_SIZE(Gimmick, 0x130);

#endif
