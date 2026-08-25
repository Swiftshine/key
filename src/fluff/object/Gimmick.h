#ifndef FLUFF_GIMMICK_H
#define FLUFF_GIMMICK_H

#include "object/FlfGameObj.h"
#include "object/GimmickList.h"
#include "demo/EventDemoGimmickCommand.h"
#include "gfl/gflResFileInfo.h"
#include "gflTask.h"
#include "gfl/gflVec3.h"
#include "misc/ScopedPointers.h"
#include "gfl/gflScnMdlWrapper.h"
#include "graphics/FullSortScene.h"
#include "manager/FlfMsgMng.h"
#include "manager/WaterRenderManager.h"

#include <nw4r/math.h>
#include <utility>
#include <string>
#include <vector>

class StatedGimmick;
class IObjHitCB;

/// @brief An interactable in-game object.
/// @note Size: `0x130`
class Gimmick : public FlfGameObj {
public:
    /* Structures */

    enum ParameterID {
        eParameterID_Param0 = 0,
        eParameterID_Param1 = 1,
        eParameterID_Param2 = 2,
        eParameterID_Param3 = 3,
        eParameterID_Param4 = 4
    };

    /// @note Size: `0x8`
    struct GimmickInfo {
        /* 0x0 */ bool mIsDeleted1;
        /* 0x1 */ bool mIsDeleted2;
        /* 0x2 */ bool m_2;
        /* 0x3 */ bool m_3;
        /* 0x4 */ Gimmick* mGimmick;
    };

    /// @brief Information for constructing new gimmicks.
    /// @note Size: `0x9C`
    class GimmickBuildInfo {
    public:
        inline GimmickBuildInfo()
            : mGimmickID(-1)
            , mPosition(0.0f, 0.0f, 0.0f)
            , mRotation(0.0f, 0.0f, 0.0f)
            , m_24(65)
            , mSceneID(6) // game index
            , mSceneOrder(4)
            , m_30(0)
            , mGimmickInfo(nullptr)
        {
            mIdentifier[0] = 0;

            for (s32 i = 0; i < 5; i++) {
                mIntParams[i] = 0;
                mFloatParams[i] = 0.0f;
                mStringParams[i] = "";
            }
        }

        inline ~GimmickBuildInfo() { }

        /* Helpful Inlines */

        inline bool IsCommon() {
            return mGimmickInfo->mIsDeleted1;
        }

        inline Gimmick* GetOwner() {
            return mGimmickInfo->mGimmick;
        }

        inline s32 GetIntParam(s32 index) {
            return mIntParams[index];
        }

        inline float GetFloatParam(s32 index) {
            return mFloatParams[index];
        }

        inline std::string& GetStringParam(s32 index) {
            return mStringParams[index];
        }

        inline bool GetBoolParam(s32 index) {
            return static_cast<bool>(mIntParams[index]);
        }

        inline bool CheckBoolParam(s32 index) {
            return mIntParams[index] == true;
        }

        /* Class Members */

        /* 0x00 */ s32 mGimmickID;
        /* 0x04 */ nw4r::math::VEC3 mPosition;
        /* 0x10 */ nw4r::math::VEC3 mRotation;

        /* 0x1C */ char mIdentifier[8];

        /* 0x24 */ u8 m_24;
        /* 0x28 */ uint mSceneID;
        /* 0x2C */ uint mSceneOrder;
        /* 0x30 */ uint m_30;
        /* 0x34 */ s32 mIntParams[5];
        /* 0x48 */ float mFloatParams[5];
        /* 0x5C */ std::string mStringParams[5];
        /* 0x98 */ GimmickInfo* mGimmickInfo;
    };
    // ASSERT_SIZE(GimmickBuildInfo, 0x9C);


    /// @brief  For the most basic gimmicks.
    Gimmick(s32 gimmickID);
    /// @brief For gimmicks that control things in-level
    Gimmick(s32 gimmickID, const char* pTaskName);
    /// @brief For "common" gimmicks.
    Gimmick(GimmickBuildInfo* pBuildInfo, const char* pTaskName);
    // unk
    Gimmick(GimmickBuildInfo* pBuildInfo);

    /* Virtual Methods */

    /* 0x08 */ virtual ~Gimmick();

    /* 0x68 */ virtual void vf68();
    /* 0x6C */ virtual nw4r::math::VEC3 vf6C();
    /* 0x70 */ virtual s32 GetGimmickID();
    /* 0x74 */ virtual s32 vf74(IObjHitCB* pOther);
    /* 0x78 */ virtual s32 vf78(IObjHitCB* pOther);
    /* 0x7C */ virtual s32 vf7C(IObjHitCB* pOther, s32);
    /* 0x80 */ virtual s32 vf80();
    /* 0x84 */ virtual s32 vf84();
    /* 0x88 */ virtual s32 vf88(FlfGameObj*, uint arg2);
    /* 0x8C */ virtual s32 vf8C(IObjHitCB* pOther, s32);
    /* 0x90 */ virtual s32 vf90();
    /* 0x94 */ virtual s32 vf94();
    /* 0x98 */ virtual s32 vf98();
    /* 0x9C */ virtual s32 vf9C();
    /* 0xA0 */ virtual void vfA0();
    /* 0xA4 */ virtual s32 vfA4();
    /* 0xA8 */ virtual void vfA8();
    /* 0xAC */ virtual void vfAC(bool);
    /* 0xB0 */ virtual void vfB0(s32);
    /* 0xB4 */ virtual void vfB4();
    /* 0xB8 */ virtual nw4r::math::VEC2 vfB8();
    /// @brief Executes processes.
    /* 0xBC */ virtual void Update() const;
    /* 0xC0 */ virtual bool vfC0(const char*);

    /* overrides */

    /* 0x40 */ void vf40(FlfGameObj*) override;
    /* 0x64 */ void UpdateWater(bool) override;

    /* Class Methods */

    gfl::Task* InitTask(const char* pTaskName);
    gfl::ScnMdlWrapper* CreateScnMdlWrapper(
        nw4r::g3d::ResFile resFile,
        const char* pResMdlName,
        uint flags,
        FullSortScene* pScene
    );

    void InitCommand();
    void ProcessCommand();
    void ClearGimmickCommands();
    void AddWaterRenderer(GmkWoolWaterRender* pRenderer);

    /* Helper Inlines */
    inline GimmickBuildInfo* GetBuildInfo() const {
        return mBuildInfoPtr;
    }

    inline StatedGimmick* ToStated() {
        return reinterpret_cast<StatedGimmick*>(this);
    }
    /* Static Methods */

    static void GetResFileObject(gfl::ResFileObject& rDest, Gimmick* pGimmick) DONT_INLINE_CLASS;
    static void GetResFileObject(gfl::ResFileObject& rDest, Gimmick* pGimmick, s32 gimmickID) DONT_INLINE_CLASS;

    /* Class Members */

    /* 0x080 */ s32 mGimmickID;
    /* 0x084 */ GimmickBuildInfo* mBuildInfoPtr;
    /* 0x088 */ GimmickBuildInfo mBuildInfo;
    /* 0x124 */ gfl::Pointer<WaterRenderManager> mWaterRenderManager;
    /* 0x128 */ gfl::Pointer<gfl::Task> mTask;
    /* 0x12C */ demo::EventDemoGimmickCommand* mCommand;
};

class StatedGimmick : public Gimmick {
public:
    /* Class Methods */

    void SetState(s32 value);

    /* Class Members */
    /* 0x130 */ s32 mState;
    /* 0x134 */ s32 mCounter;
};

#endif
