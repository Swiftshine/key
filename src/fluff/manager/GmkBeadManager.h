#ifndef FLUFF_GMKBEADMANAGER_H
#define FLUFF_GMKBEADMANAGER_H

#include "types.h"
#include "object/FlfHandleObj.h"
#include "gfl/gflTask.h"
#include "gfl/gflLinkedList.h"

class GmkBead;
class GmkBeadPopItem;

class GmkBeadManager {
private:
    static GmkBeadManager* sInstance;

    struct GmkBeadManager_Info {
        bool HasHandle(FlfHandleObj* object);

        int mNumUserHandles;
        int m_4;
        int m_8;
        FlfHandle mUserHandles[8];
        u32 m_4C[2][128];
    };

    ASSERT_SIZE(GmkBeadManager_Info, 0x44C);
public:
    static void CreateInstance();
    static void DestroyInstance();
    static GmkBeadManager* GetInstance();
    
    GmkBeadManager(gfl::Task* parentTask);
    virtual ~GmkBeadManager();
    virtual void vfC();
    void EnableBeadPopSwitch(GmkBeadPopItem*, const char* tags, bool);
    GmkBeadManager_Info* GetInfoIfHandlePresent(FlfHandleObj* object);
    void fn_8051D854(bool);
    
private:
    gfl::Task* mTask; // @ 0x4
    GmkBeadManager_Info mInfo; // @ 0x1C
    gfl::LinkedList<placeholder_t> mList; // @ 0x468
};

#endif
