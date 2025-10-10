#ifndef FLUFF_GMKMOLEHOLERENDER_H
#define FLUFF_GMKMOLEHOLERENDER_H

#include <nw4r/g3d.h>
#include "types.h"
#include "gfl/gflCustomRenderObj.h"
#include "gfl/gflLinkedList.h"
#include "gfl/gflResFileInfo.h"

class GmkMoleHoleRender : public gfl::CustomRenderObj {
public:
    /* Structures */

    struct RenderUser {
        RenderUser();
        ~RenderUser();
        
        /* 0x00 */ bool mShouldUpdate;
        /* 0x04 */ nw4r::math::VEC3 mPosition;
    };

    /* Static Variables */

    static GmkMoleHoleRender* sInstance;

    inline static GmkMoleHoleRender* Instance() {
        return sInstance;
    }

    /* Static Methods */
    
    static void AddUser(RenderUser* pUser);
    static void RemoveUser(RenderUser* pUser);

    /* Class Members */

    /* 0x104 */ float mZPosition1;
    /* 0x108 */ float mZPosition2;
    /* 0x10C */ nw4r::g3d::ResTex mResTex1;
    /* 0x110 */ nw4r::g3d::ResTex mResTex2;
    /* 0x114 */ GXTexObj mTexObj1;
    /* 0x134 */ GXTexObj mTexObj2;
    /* 0x154 */ gfl::ResFileInfo* mFileInfo;
    /* 0x158 */ float m_158;
    /* 0x15C */ float m_15C;
    /* 0x160 */ gfl::LinkedList<RenderUser*> mUsers;
    /* 0x16C */ gfl::LinkedList<placeholder_t> mList; // list of what?
};

ASSERT_SIZE(GmkMoleHoleRender, 0x178);

#endif