#ifndef FLUFF_FLFDEMOCTRL_H
#define FLUFF_FLFDEMOCTRL_H

#include "types.h"
#include <string>
#include <nw4r/g3d.h>
#include "gfl/gflLinkedList.h"
#include "gfl/gflResFileInfo.h"
#include "gfl/gflScnMdlWrapper.h"
#include "gfl/gflTask.h"
#include "graphics/FlfMdlDraw.h"
#include "misc/ScopedPointers.h"
#include "util/NURBSOption.h"
#include "object/PlayerBase.h"
#include "util/NURBSStructures.h"

// size: 0x24
class FlfDemoNodeCtrl {
public:
    FlfDemoNodeCtrl(nw4r::g3d::ResNode resNode) DONT_INLINE_CLASS;
    virtual ~FlfDemoNodeCtrl() DONT_INLINE_CLASS;
    const char* GetResName();
    void ResetOptions(NURBSStruct2* arg1);

    DECL_WEAK virtual void vfC();
    DECL_WEAK virtual void vf10();
    virtual void SetMatrix(nw4r::math::MTX34* matrices);
    virtual void vf18(float);
    virtual void vf1C();
    DECL_WEAK virtual uint vf20();
    virtual void vf24(int);
    virtual void SetCurrentFrame(int frame);
    virtual void SetUpdateRate(float rate);
    virtual void SetFullSortScene(uint sceneID);
    virtual void SetVisibility(bool visibility);
    virtual void SetMatrix(nw4r::math::MTX34& matrix);

    static void GetCharaResFileObject(gfl::ResFileObject& resFileObject, nw4r::g3d::ResNode* resNode, std::string& name);
    static std::string GetCharaResourceName(std::string& name);

    static inline void SetMTXTranslation(nw4r::math::MTX34& mtx, nw4r::math::VEC3& src) {
        mtx[0][3] = src.x;
        mtx[1][3] = src.y;
        mtx[2][3] = src.z;
    }
    
    static inline nw4r::math::VEC3 GetMTXTranslation(nw4r::math::MTX34& mtx) {
        return nw4r::math::VEC3(mtx[0][3], mtx[1][3], mtx[2][3]);
    }
protected:
    int m_4;
    int mFullSortSceneID;                      // @ 0x8
    nw4r::g3d::ResNode mResNode;               // @ 0xC
    gfl::Pointer<NURBSOption> mAnimNo;         // @ 0x10
    gfl::Pointer<NURBSOption> mBlendFrame;     // @ 0x14
    gfl::Pointer<NURBSOption> mUpdateRate;     // @ 0x18
    gfl::Pointer<NURBSOption> mLayer;          // @ 0x1C
    gfl::Pointer<NURBSOption> mVisibility;     // @ 0x20
};

// size: 0x34
class FlfDemoCharCtrl : public FlfDemoNodeCtrl {
public:
    FlfDemoCharCtrl(nw4r::g3d::ResNode resNode, std::string& name);
    virtual ~FlfDemoCharCtrl();

    /* FlfDemoNodeCtrl */
    virtual void vf1C() override;
    virtual uint vf20() override;
    virtual void vf24(int) override;
    virtual void SetCurrentFrame(int frame) override;
    virtual void SetUpdateRate(float rate) override;
    virtual void SetFullSortScene(uint sceneID) override;
    virtual void SetVisibility(bool visibility) override;
    virtual void SetMatrix(nw4r::math::MTX34& mtx) override;
private:
    std::string mResourcePath;              // @ 0x24
    gfl::Pointer<FlfMdlDraw> mFlfMdlDraw;   // @ 0x30
};

// size: 0x30
class FlfDemoPlayerCtrl : public FlfDemoNodeCtrl {
public:
    FlfDemoPlayerCtrl(nw4r::g3d::ResNode resNode, std::string& name);
    virtual ~FlfDemoPlayerCtrl();

    /* FlfDemoNodeCtrl */
    virtual void vf18(float) override;
    virtual void vf1C() override;
    virtual uint vf20() override;
    virtual void vf24(int) override;
    virtual void SetCurrentFrame(int frame) override;
    virtual void SetUpdateRate(float rate) override;
    virtual void SetFullSortScene(uint sceneID) override;
    virtual void SetVisibility(bool visibility) override;
    virtual void SetMatrix(nw4r::math::MTX34& mtx) override;
private:
    bool mIsPlayerStateDefault; // @ 0x24
    bool m_25;
    bool m_26;
    uint mCurrentFrame;
    PlayerBase* mPlayer;        // @ 0x2C
};

// size: 0x44
class FlfDemoBeadCtrl : public FlfDemoNodeCtrl {
public:
    FlfDemoBeadCtrl(nw4r::g3d::ResNode resNode, std::string& beadInfo);
    virtual ~FlfDemoBeadCtrl();

    /* FlfDemoNodeCtrl */
    virtual void SetVisibility(bool visibility) override;
    virtual void SetMatrix(nw4r::math::MTX34& mtx) override;
private:
    int mBeadType;                  // @ 0x24
    int mBeadColor;                 // @ 0x28
    FlfHandle mBeadHandle;          // @ 0x2C
    nw4r::math::VEC3 mBeadPosition; // @ 0x34
    bool mBeadCreated;              // @ 0x40
};

// size: 0x2C
class FlfDemoGmkCtrl : public FlfDemoNodeCtrl {
public:
    FlfDemoGmkCtrl(nw4r::g3d::ResNode resNode, std::string& tag);
    DECL_WEAK virtual ~FlfDemoGmkCtrl();

    /* FlfDemoNodeCtrl */

    virtual void vf24(int) override;
    virtual void SetVisibility(bool visibility) override;
    virtual void SetMatrix(nw4r::math::MTX34& mtx) override;
private:
    FlfHandle mGimmickHandle; // @ 0x24
};

// size: 0x2C
class FlfDemoFlgCtrl : public FlfDemoNodeCtrl {
public:
    FlfDemoFlgCtrl(nw4r::g3d::ResNode resNode, std::string& indexStr);
    DECL_WEAK virtual ~FlfDemoFlgCtrl();

    /* FlfDemoNodeCtrl */

    virtual void SetVisibility(bool visibility) override;
private:
    bool mFlagValue;    // @ 0x24
    size_t mFlagIndex;  // @ 0x28
};

// size: 0x28
class FlfDemoLoopCtrl : public FlfDemoNodeCtrl {
public:
    FlfDemoLoopCtrl(nw4r::g3d::ResNode resNode);
    DECL_WEAK virtual ~FlfDemoLoopCtrl();

    /* FlfDemoNodeCtrl */

    DECL_WEAK virtual void vf24(int) override;
private:
    int m_24;
};

// size: 0x8
class FlfDemoCamCtrl {
public:
    FlfDemoCamCtrl(nw4r::g3d::ResNode resNode);
    virtual ~FlfDemoCamCtrl();

    DECL_WEAK virtual void vfC();
    DECL_WEAK virtual void vf10();
    virtual void SetMatrix(nw4r::math::MTX34* matrices);

    static inline nw4r::math::VEC3 GetMTXTranslation(nw4r::math::MTX34& mtx) {
        return nw4r::math::VEC3(mtx[0][3], mtx[1][3], mtx[2][3]);
    }
private:
    nw4r::g3d::ResNode mResNode; // @ 0x4
};

// size unk
struct FlfDemoCtrlStruct {
    STRUCT_FILL(0x28);

    DECL_WEAK int GetUnk24();
};

// size: 0x5C
class FlfDemoCtrl {
public:
    FlfDemoCtrl();
    virtual ~FlfDemoCtrl();


    // vfC and vf10 have different signatures
    // but it's not clear what they are
    DECL_WEAK virtual void vfC();
    DECL_WEAK virtual void vf10();
    DECL_WEAK virtual void SetMatrices(nw4r::math::MTX34* matrices);

    void ResetFlfMdlDraw(const char* resourcePath);
    bool CheckState();
    void DestroyResources();
    void ClearNodeControls();
    void Update();
    void fn_802BB920();
    void fn_802BBA4C(int, nw4r::math::VEC2* vec);
    uint fn_802BBB28() DONT_INLINE_CLASS;
    float GetCurrentFrame();
    float GetEndFrame();
    bool IsAnimationDone();
    void SetMatrix(nw4r::math::VEC2*);
    void SetScnMdlWrapper();
    void AddNwBlendAnmWrapperResFileObjects();
    static void GetCount(NURBSOption* dst, const char* name);
    void fn_802BBE08(NURBSStruct2*);
private:
    int mState;                                             // @ 0x4
    std::string mResourcePath;                              // @ 0x8
    bool m_14;
    gfl::ResFileObject mResFileObject;                      // @ 0x18
    gfl::LinkedList<gfl::ResFileObject> mResFileObjects;    // @ 0x1C
    gfl::Pointer<FlfMdlDraw> mFlfMdlDraw;                   // @ 0x28
    gfl::ScnMdlWrapper* mScnMdlWrapper;                     // @ 0x2C
    gfl::Pointer<FlfDemoCamCtrl> mCamCtrl;                  // @ 0x30
    FlfDemoCtrlStruct* m_34;
    gfl::Task mTask;                                        // @ 0x38
    gfl::LinkedList<FlfDemoNodeCtrl*> mNodeCtrls;           // @ 0x50
};


#endif
