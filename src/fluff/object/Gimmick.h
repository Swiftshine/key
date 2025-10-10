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

class StatedGimmick;
class IObjHitCB;

/// @brief An interactable in-game object.
/// @note Size: `0x130`
class Gimmick : public FlfGameObj {
public:
    /* Structures */

    ENUM_CLASS(ParameterID,
        FIRST   = 0,
        SECOND  = 1,
        THIRD   = 2,
        FOURTH  = 3,
        FIFTH   = 4
    );

    /// @note Size: `0x8`
    struct GimmickInfo {
        /* 0x0 */ bool mIsCommon;
        /* 0x1 */ bool mIsDeleted;
        /* 0x2 */ bool m_2;
        /* 0x3 */ bool m_3;
        /* 0x4 */ Gimmick* mGimmick;
    };

    /// @brief Information for constructing new gimmicks.
    /// @note Size: `0x9C`
    class GimmickBuildInfo {
    public:
        /* Constructor + Destructor */

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

            mGimmickInfo = nullptr;
            mCommonTag.mParts[0] = 0;

            for (uint i = 0; i < 5; i++) {
                mIntParams[i] = 0;
                mFloatParams[i] = 0.0f;
                mStringParams[i] = Blank;
            }
        }

        inline ~GimmickBuildInfo() { }

        inline void operator=(GimmickBuildInfo& rOther) {
            mGimmickID = rOther.mGimmickID;
            // mPosition = other.mPosition;
            // mRotation = other.mRotation;
            mCommonTag = rOther.mCommonTag;
        }

        /* Helpful Inlines */

        inline bool IsCommon() {
            return mGimmickInfo->mIsCommon;
        }

        inline Gimmick* GetOwner() {
            return mGimmickInfo->mGimmick;
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

        /* Class Members */

        /* 0x00 */ int mGimmickID;
        /* 0x04 */ nw4r::math::VEC3 mPosition;
        /* 0x10 */ nw4r::math::VEC3 mRotation;

        /* 0x1C */ union {
            char mParts[4];
            uint mWhole;
        } mCommonTag;

        /* 0x20 */ uint m_20;
        /* 0x24 */ bool m_24;
        /* 0x28 */ uint mFullSortSceneIndex;
        /* 0x2C */ uint m_2C;
        /* 0x30 */ uint m_30;
        /* 0x34 */ int mIntParams[5];
        /* 0x48 */ float mFloatParams[5];
        /* 0x5C */ std::string mStringParams[5];
        /* 0x98 */ GimmickInfo* mGimmickInfo;
    };
    // ASSERT_SIZE(GimmickBuildInfo, 0x9C);

    /* Constructors */
    /// @brief  For the most basic gimmicks.
    Gimmick(int gmkID);
    /// @brief For gimmicks that control things in-level
    Gimmick(int gmkID, const char* pTaskName);
    /// @brief For "common" gimmicks.
    Gimmick(GimmickBuildInfo* pBuildInfo, const char* pTaskName);
    // unk
    Gimmick(GimmickBuildInfo* pBuildInfo);

    /* Virtual Methods */

    /* 0x08 */ virtual ~Gimmick();

    /* -> FlfGameObj */

    /* 0x40 */ void vf40(FlfGameObj*) override;
    /* 0x64 */ void vf64(bool) override;

    /* Gimmick */

    /* 0x68 */ virtual void vf68();
    /* 0x6C */ virtual nw4r::math::VEC3 vf6C();
    /* 0x70 */ virtual int GetGimmickID();
    /* 0x74 */ virtual int vf74(IObjHitCB* pOther);
    /* 0x78 */ virtual int vf78(IObjHitCB* pOther);
    /* 0x7C */ virtual int vf7C(IObjHitCB* pOther, int);
    /* 0x80 */ virtual int vf80();
    /* 0x84 */ virtual int vf84();
    /* 0x88 */ virtual int vf88(FlfGameObj*, uint arg2);     
    /* 0x8C */ virtual int vf8C(IObjHitCB* pOther, int);
    /* 0x90 */ virtual int vf90();
    /* 0x94 */ virtual int vf94();
    /* 0x98 */ virtual int vf98();
    /* 0x9C */ virtual int vf9C();
    /* 0xA0 */ virtual void vfA0();
    /* 0xA4 */ virtual int vfA4();
    /* 0xA8 */ virtual void vfA8();
    /* 0xAC */ virtual void vfAC(bool);
    /* 0xB0 */ virtual void vfB0(int);
    /* 0xB4 */ virtual void vfB4();
    /* 0xB8 */ virtual nw4r::math::VEC2 vfB8();
    /// @brief Executes processes.
    /* 0xBC */ virtual void Update();
    /* 0xC0 */ virtual bool vfC0(const char*);

    /* Class Methods */

    void fn_8004E650(const char*);
    void InitCommand();
    void ProcessCommand();
    void fn_8004ED1C();

    /* Static Methods */

    static void GetResFileInfo(gfl::ResFileObject& rDest, Gimmick* pGmk);
    static void GetResFileInfo(gfl::ResFileObject& rDest, Gimmick* pGmk, int gimmickID);
    /// @brief Splits a formatted tag list into a vector of individual tags.
    /// @param pTagList The formatted tag list. E.g. "tag1;tag2;tag3;"
    /// @param rDest The destination vector.
    static void SplitCommonTags(const char* pTagList, std::vector<std::string>& rDest);


    inline StatedGimmick* ToStated() {
        return reinterpret_cast<StatedGimmick*>(this);
    }

    /* Class Members */

    /* 0x080 */ int mGimmickID;
    /* 0x084 */ GimmickBuildInfo* mBuildInfoPtr;
    /* 0x088 */ GimmickBuildInfo mBuildInfo;
    /* 0x124 */ void* m_124;
    /* 0x128 */ gfl::Task* mTask;
    /* 0x12C */ demo::EventDemoGimmickCommand* mCommand;
};

class StatedGimmick : public Gimmick {
public:
    /* Class Methods */

    void SetState(int value);

    /* Class Members */
    /* 0x130 */ int mState;
    /* 0x134 */ int mCounter;
};

#endif
