#ifndef FLUFF_GMKBEADMANAGER_H
#define FLUFF_GMKBEADMANAGER_H

// #pragma inline off

#include "types.h"
#include "object/FlfHandleObj.h"
#include "gfl/gflTask.h"
#include "gfl/gflLinkedList.h"
#include "sound/SoundHandle.h"

class GmkBead;
class GmkBeadPopItem;

class GmkBeadManager {
public:
    /* Static Variables */

    static GmkBeadManager* sInstance;

    /* Structures */

    struct GmkBeadManager_Info {
        GmkBeadManager_Info();
        ~GmkBeadManager_Info();
        bool HasHandle(FlfHandleObj* pHandleObj);
        void fn_8051CFB4();
        bool IsEmpty();
        void ResetUserHandles(FlfHandleObj* pHandleObj);
        void SetUserHandle(FlfHandleObj* pHandleObj);

        /* 0x00 */ int mNumUserHandles;
        /* 0x04 */ sound::SoundHandle mSoundHandle;
        /* 0x0C */ FlfHandle mUserHandles[8];
        /* 0x4C */ u32 m_4C[2][128];
    };

    ASSERT_SIZE(GmkBeadManager_Info, 0x44C);

    /* Constructor */

    GmkBeadManager(gfl::Task* pParentTask);

    /* Virtual Methods */

    /* 0x8 */ virtual ~GmkBeadManager();
    /* 0xC */ virtual void vfC();

    /* Class Methods */

    void EnableBeadPopSwitch(GmkBeadPopItem* pBeadPopItem, const char* pTags, bool assignHandle);
    GmkBeadManager_Info* GetInfoIfHandlePresent(FlfHandleObj* pHandleObj);
    void fn_8051D854(bool);

    /* Static Methods */

    static void InitInstance(gfl::Task* pParentTask);
    static void DestroyInstance();
    static GmkBeadManager* GetInstance();

    /* Class Members */

    /* 0x004 */ gfl::Task mTask;
    /* 00x1C */ GmkBeadManager_Info mInfo;
    /* 0x468 */ gfl::LinkedList<placeholder_t> mList;
};

#endif
