#ifndef FLUFF_GMKMOLEHOLERENDER_H
#define FLUFF_GMKMOLEHOLERENDER_H

#include <nw4r/g3d.h>
#include "types.h"
#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflLinkedList.h"
#include "gfl/gflResFileInfo.h"

class GmkMoleHoleRender : public gfl::CustomRenderObj {
private:
    static GmkMoleHoleRender* sInstance;
public:
    struct RenderUser {
        RenderUser();
        ~RenderUser();
        
        bool mShouldUpdate;
        nw4r::math::VEC3 mPosition;
    };
public:
    inline static GmkMoleHoleRender* Instance() {
        return sInstance;
    }

    static void AddUser(void* user);
    static void RemoveUser(void* user);

    inline void InitInstance();
    inline void DestroyInstance();
private:
    float mZPosition1; // @ 0x104
    float mZPosition2; // @ 0x108
    nw4r::g3d::ResTex mResTex1; // @ 0x10C
    nw4r::g3d::ResTex mResTex2; // @ 0x110
    GXTexObj mTexObj1; // @ 0x114, size: 0x20
    GXTexObj mTexObj2; // @ 0x134
    gfl::ResFileInfo* mFileInfo; // @ 0x154
    float m_158;
    float m_15C;
    gfl::LinkedList<RenderUser*> mUsers; // @ 0x160, size: 0xC
    gfl::LinkedList<placeholder_t> mList; // @ 0x16C
};

ASSERT_SIZE(GmkMoleHoleRender, 0x178);

#endif