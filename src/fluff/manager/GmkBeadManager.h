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
private:
    static GmkBeadManager* sInstance;
public:
    struct GmkBeadManager_Info {
        GmkBeadManager_Info();
        ~GmkBeadManager_Info();
        bool HasHandle(FlfHandleObj* object);
        void fn_8051CFB4();
        bool IsEmpty();
        void ResetUserHandles(FlfHandleObj* handleObj);
        void SetUserHandle(FlfHandleObj* handleObj);

        int mNumUserHandles; // @ 0x0
        sound::SoundHandle mSoundHandle; // @ 0x4
        FlfHandle mUserHandles[8]; // @ 0xC
        u32 m_4C[2][128];
    };

    ASSERT_SIZE(GmkBeadManager_Info, 0x44C);
public:
    static void InitInstance(gfl::Task* parentTask);
    static void DestroyInstance();
    static GmkBeadManager* GetInstance();
    
    GmkBeadManager(gfl::Task* parentTask);
    virtual ~GmkBeadManager();
    virtual void vfC();
    void EnableBeadPopSwitch(GmkBeadPopItem* beadPopItem, const char* tags, bool assignHandle);
    GmkBeadManager_Info* GetInfoIfHandlePresent(FlfHandleObj* object);
    void fn_8051D854(bool);
    
private:
    gfl::Task mTask; // @ 0x4
    GmkBeadManager_Info mInfo; // @ 0x1C
    gfl::LinkedList<placeholder_t> mList; // @ 0x468
};

#endif
