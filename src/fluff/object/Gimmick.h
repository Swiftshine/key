#ifndef FLUFF_GIMMICK_H
#define FLUFF_GIMMICK_H

#include "object/FlfGameObj.h"
#include "object/GimmickList.h"
#include "demo/EventDemoGimmickCommand.h"
#include "gfl/gflResFileInfo.h"
#include "gflTask.h"

#include <nw4r/math.h>
#include <utility>
#include <string>
#include <vector>

extern "C" const char Blank[];

struct GimmickVec {
    float x;
    float y;
    float z;
};

class StatedGimmick;

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
        inline GimmickBuildInfo()
            : mGimmickID(-1)
            , mPosition(0.0f, 0.0f, 0.0f)
            , mRotation(0.0f, 0.0f, 0.0f)
        {

            m_24 = 'A';
            mFullSortSceneIndex = 6;
            m_2C = 4;
            m_30 = 0;

            mExtension = nullptr;
            mCommonTag.mParts[0] = 0;

            for (uint i = 0; i < 5; i++) {
                mIntParams[i] = 0;
                mFloatParams[i] = 0.0f;
                mStringParams[i] = Blank;
            }
        }

        inline ~GimmickBuildInfo() { }

        inline void operator=(GimmickBuildInfo& other) {
            mGimmickID = other.mGimmickID;
            // mPosition = other.mPosition;
            // mRotation = other.mRotation;
            mCommonTag = other.mCommonTag;
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

        inline const char* GetCommonTag() {
            return mCommonTag.mParts;
        }

        inline uint GetCommonTagValue() {
            return mCommonTag.mWhole;
        }

    public:
        int mGimmickID;
        nw4r::math::VEC3 mPosition;
        nw4r::math::VEC3 mRotation;

        union {
            char mParts[4];
            uint mWhole;
        } mCommonTag;

        uint m_20;
        u8 m_24;
        u8 m_25;
        u8 m_26;
        u8 m_27;
        uint mFullSortSceneIndex;
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
    void ProcessCommand();
    void fn_8004ED1C();
    static void GetResFileInfo(gfl::ResFileObject& fileInfo, Gimmick* gimmick);
    static void GetResFileInfo(gfl::ResFileObject& fileInfo, Gimmick* gimmick, int gimmickID);
    static void SplitCommonTags(const char* tagList, std::vector<std::string>& dst);
    // virtual functions

    void vf40(FlfGameObj*) override;
    void vf64(bool) override;

    virtual void    vf68();
    virtual nw4r::math::VEC3   vf6C();
    virtual int     GetGimmickID();
    virtual int     vf74();
    virtual int     vf78();
    virtual int     vf7C();
    virtual int     vf80();
    virtual int     vf84();
    virtual int     vf88(FlfGameObj*, uint arg2);     
    virtual int     vf8C();
    virtual int     vf90();
    virtual int     vf94();
    virtual int     vf98();
    virtual int     vf9C();
    virtual void    vfA0();
    virtual int     vfA4();
    virtual void    vfA8();
    virtual nw4r::math::VEC2   vfAC();
    virtual void    vfB0();
    virtual void    vfB4();
    virtual nw4r::math::VEC2   vfB8();
    virtual void    Update();
    virtual bool    vfC0(const char*);

    inline StatedGimmick* ToStated() {
        return reinterpret_cast<StatedGimmick*>(this);
    }

    inline GimmickBuildInfo& GetGimmickBuildInfo() {
        return mBuildInfo;
    }

    inline GimmickBuildInfo* GetGimmickBuildInfoPtr() {
        return mBuildInfoPtr;
    }
public:
    int mGimmickID;
    GimmickBuildInfo* mBuildInfoPtr;
    GimmickBuildInfo mBuildInfo;
    void* m_124;
    gfl::Task* mTask;
    demo::EventDemoGimmickCommand* mCommand;
};

class StatedGimmick : public Gimmick {
public:
    void SetState(int value);
public:
    int mState;
    int mCounter;
};


// ASSERT_SIZE(Gimmick, 0x130);

#endif
