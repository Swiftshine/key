#ifndef FLUFF_FLFDEMOCTRL_H
#define FLUFF_FLFDEMOCTRL_H

#include "types.h"
#include <string>
#include <nw4r/g3d.h>
#include "gfl/gflLinkedList.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/FlfMdlDraw.h"
#include "misc/ScopedPointers.h"
#include "gfl/gflScnMdlWrapper.h"
#include "gfl/gflTask.h"
#include "object/PlayerBase.h"

// size: 0x24
class FlfDemoNodeCtrl {
public:
    FlfDemoNodeCtrl(nw4r::g3d::ResNode* resNode);
    virtual ~FlfDemoNodeCtrl();
    
    virtual void vfC();
    virtual void vf10();
    virtual void vf14();
    virtual void vf18();
    virtual void vf1C();
    virtual void vf20();
    virtual void vf24();
    virtual void vf28();
    virtual void vf2C(float);
    virtual void vf30();
    virtual void vf34();
    virtual void SetMatrix(nw4r::math::MTX34& matrix);
private:
    int m_4;
    uint mFullSortSceneID;          // @ 0x8
    nw4r::g3d::ResNode mResNode;    // @ 0xC
    nw4r::g3d::ResName mAnimNo;     // @ 0x10
    nw4r::g3d::ResName mBlendFrame; // @ 0x14
    nw4r::g3d::ResName mUpdateRate; // @ 0x18
    nw4r::g3d::ResName mLayer;      // @ 0x1C
    nw4r::g3d::ResName mVisibility; // @ 0x20
};

// size: 0x34
class FlfDemoCharCtrl : public FlfDemoNodeCtrl {
private:
    std::string mResourcePath; // @ 0x24
    gfl::Pointer<FlfMdlDraw> mFlfMdlDraw; // @ 0x30
};

// size: 0x30
class FlfDemoPlayerCtrl : public FlfDemoNodeCtrl {
private:
    bool mIsPlayerStateDefault; // @ 0x24
    bool m_25;
    bool m_26;
    int m_28;
    PlayerBase* mPlayer; // @ 0x2C
};

// size: 0x44
class FlfDemoBeadCtrl : public FlfDemoNodeCtrl {
private:
    int mBeadType;  // @ 0x24
    int mBeadColor; // @ 0x28
    FlfHandle mBeadHandle; // @ 0x2C
    nw4r::math::VEC3 mBeadPosition; // @ 0x34
    bool mBeadCreated; // @ 0x40
};

// size: 0x2C
class FlfDemoGmkCtrl : public FlfDemoNodeCtrl {
private:
    FlfDemoGmkCtrl(nw4r::g3d::ResNode* resNode, std::string&);
private:
    FlfHandle mGimmickHandle; // @ 0x24
};

// size: 0x2C
// does "Flg" stand for "flag"?
class FlfDemoFlgCtrl : public FlfDemoNodeCtrl {
private:
    FlfDemoFlgCtrl(nw4r::g3d::ResNode* resNode, std::string&);
private:
    bool m_24;
    uint m_28;
};

// size: 0x28
class FlfDemoLoopCtrl : public FlfDemoNodeCtrl {
private:
    int m_24;
};

// size: 0x5C
class FlfDemoCtrl {
public:
    FlfDemoCtrl();
    virtual ~FlfDemoCtrl();
private:
    int mState; // @ 0x4
    std::string mResourcePath; // @ 0x8
    int m_14;
    gfl::ResFileObject mResFileObject; // @ 0x18
    gfl::LinkedList<gfl::ResFileObject> mResFileObjects; // @ 0x1C
    gfl::Pointer<FlfMdlDraw> mFlfMdlDraw; // @ 0x28
    gfl::ScnMdlWrapper* mModelWrapper; // @ 0x2C
    void* m_34;
    gfl::Task mTask; // @ 0x38
    gfl::LinkedList<FlfDemoNodeCtrl> mNodeCtrls; // @ 0x50
};


#endif