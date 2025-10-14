#ifndef FLUFF_FLFDEMOCTRL_H
#define FLUFF_FLFDEMOCTRL_H

#include "types.h"
#include <string>
#include <nw4r/g3d/res/g3d_resnode.h>
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
    /* Constructor */

    FlfDemoNodeCtrl(nw4r::g3d::ResNode resNode) DONT_INLINE_CLASS;

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfDemoNodeCtrl() DONT_INLINE_CLASS;
    /* 0x0C */ DECL_WEAK virtual void vfC();
    /* 0x10 */ DECL_WEAK virtual void vf10();
    /* 0x14 */ virtual void SetMatrix(nw4r::math::MTX34* matrices);
    /* 0x18 */ virtual void vf18(float);
    /* 0x1C */ virtual void vf1C();
    /* 0x20 */ DECL_WEAK virtual uint vf20();
    /* 0x24 */ virtual void vf24(int);
    /* 0x28 */ virtual void SetCurrentFrame(int frame);
    /* 0x2C */ virtual void SetUpdateRate(float rate);
    /* 0x30 */ virtual void SetFullSortScene(uint sceneID);
    /* 0x34 */ virtual void SetVisibility(bool visibility);
    /* 0x38 */ virtual void SetMatrix(nw4r::math::MTX34& matrix);

    /* Class Members */

    const char* GetResName();
    void ResetOptions(NURBSStruct2* arg1);

    /* Static Methods */

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

    /* Class Members */

    /* 0x04 */ int m_4;
    /* 0x08 */ int mFullSortSceneID;                 
    /* 0x0C */ nw4r::g3d::ResNode mResNode;          
    /* 0x10 */ gfl::Pointer<NURBSOption> mAnimNo;    
    /* 0x14 */ gfl::Pointer<NURBSOption> mBlendFrame;
    /* 0x18 */ gfl::Pointer<NURBSOption> mUpdateRate;
    /* 0x1C */ gfl::Pointer<NURBSOption> mLayer;     
    /* 0x20 */ gfl::Pointer<NURBSOption> mVisibility;
};

// size: 0x34
class FlfDemoCharCtrl : public FlfDemoNodeCtrl {
public:
    /* Constructor */

    FlfDemoCharCtrl(nw4r::g3d::ResNode resNode, std::string& name);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfDemoCharCtrl();

    /* 0x1C */ virtual void vf1C() override;
    /* 0x20 */ virtual uint vf20() override;
    /* 0x24 */ virtual void vf24(int) override;
    /* 0x28 */ virtual void SetCurrentFrame(int frame) override;
    /* 0x2C */ virtual void SetUpdateRate(float rate) override;
    /* 0x30 */ virtual void SetFullSortScene(uint sceneID) override;
    /* 0x34 */ virtual void SetVisibility(bool visibility) override;
    /* 0x38 */ virtual void SetMatrix(nw4r::math::MTX34& mtx) override;

    /* Class Members */

    /* 0x24 */ std::string mResourcePath;
    /* 0x30 */ gfl::Pointer<FlfMdlDraw> mFlfMdlDraw;
};

// size: 0x30
class FlfDemoPlayerCtrl : public FlfDemoNodeCtrl {
public:
    /* Constructor */

    FlfDemoPlayerCtrl(nw4r::g3d::ResNode resNode, std::string& name);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfDemoPlayerCtrl();

    /* 0x18 */ virtual void vf18(float) override;
    /* 0x1C */ virtual void vf1C() override;
    /* 0x20 */ virtual uint vf20() override;
    /* 0x24 */ virtual void vf24(int) override;
    /* 0x28 */ virtual void SetCurrentFrame(int frame) override;
    /* 0x2C */ virtual void SetUpdateRate(float rate) override;
    /* 0x30 */ virtual void SetFullSortScene(uint sceneID) override;
    /* 0x34 */ virtual void SetVisibility(bool visibility) override;
    /* 0x38 */ virtual void SetMatrix(nw4r::math::MTX34& mtx) override;

    /* Class Members */

    /* 0x24 */ bool mIsPlayerStateDefault;
    /* 0x25 */ bool m_25;
    /* 0x26 */ bool m_26;
    /* 0x28 */ uint mCurrentFrame;
    /* 0x2C */ PlayerBase* mPlayer;
};

// size: 0x44
class FlfDemoBeadCtrl : public FlfDemoNodeCtrl {
public:
    /* Constructor */

    FlfDemoBeadCtrl(nw4r::g3d::ResNode resNode, std::string& beadInfo);

    /* Virtual Methods  */

    /* 0x08 */ virtual ~FlfDemoBeadCtrl();

    /* 0x34 */ virtual void SetVisibility(bool visibility) override;
    /* 0x38 */ virtual void SetMatrix(nw4r::math::MTX34& mtx) override;

    /* Class Members */

    /* 0x24 */ int mBeadType;                 
    /* 0x28 */ int mBeadColor;                
    /* 0x2C */ FlfHandle mBeadHandle;         
    /* 0x34 */ nw4r::math::VEC3 mBeadPosition;
    /* 0x40 */ bool mBeadCreated;             
};

// size: 0x2C
class FlfDemoGmkCtrl : public FlfDemoNodeCtrl {
public:
    /* Constructor */

    FlfDemoGmkCtrl(nw4r::g3d::ResNode resNode, std::string& tag);

    /* Virtual Methods */

    /* 0x08 */ DECL_WEAK virtual ~FlfDemoGmkCtrl();

    /* 0x24 */ virtual void vf24(int) override;
    /* 0x34 */ virtual void SetVisibility(bool visibility) override;
    /* 0x38 */ virtual void SetMatrix(nw4r::math::MTX34& mtx) override;

    /* Class Members */

    /* 0x24 */ FlfHandle mGimmickHandle;
};

// size: 0x2C
class FlfDemoFlgCtrl : public FlfDemoNodeCtrl {
public:
    /* Constructor */

    FlfDemoFlgCtrl(nw4r::g3d::ResNode resNode, std::string& indexStr);

    /* Virtual Methods */

    /* 0x08 */ DECL_WEAK virtual ~FlfDemoFlgCtrl();

    /* 0x34 */ virtual void SetVisibility(bool visibility) override;

    /* Class Members */

    /* 0x24 */ bool mFlagValue;
    /* 0x28 */ size_t mFlagIndex;
};

// size: 0x28
class FlfDemoLoopCtrl : public FlfDemoNodeCtrl {
public:
    /* Constructor */
    
    FlfDemoLoopCtrl(nw4r::g3d::ResNode resNode);

    /* Virtual Methods */

    /* 0x08 */ DECL_WEAK virtual ~FlfDemoLoopCtrl();

    /* 0x24 */ DECL_WEAK virtual void vf24(int) override;

    /* Class Members */

    /* 0x24 */ int m_24;
};

// size: 0x8
class FlfDemoCamCtrl {
public:
    /* Constructor */

    FlfDemoCamCtrl(nw4r::g3d::ResNode resNode);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfDemoCamCtrl();
    /* 0x0C */ DECL_WEAK virtual void vfC();
    /* 0x10 */ DECL_WEAK virtual void vf10();
    /* 0x14 */ virtual void SetMatrix(nw4r::math::MTX34* matrices);

    /* Static Methods */

    static inline nw4r::math::VEC3 GetMTXTranslation(nw4r::math::MTX34& mtx) {
        return nw4r::math::VEC3(mtx[0][3], mtx[1][3], mtx[2][3]);
    }

    /* Class Members */

    /* 0x04 */ nw4r::g3d::ResNode mResNode;
};

// size unk
struct FlfDemoCtrlStruct {
    STRUCT_FILL(0x28);

    DECL_WEAK int GetUnk24();
};

// size: 0x5C
class FlfDemoCtrl {
public:
    /* Constructor */

    FlfDemoCtrl();

    /* Virtual Methods */

    /* 0x08 */ virtual ~FlfDemoCtrl();
    /* 0x0C */ DECL_WEAK virtual void vfC(/* unknown signature */);
    /* 0x10 */ DECL_WEAK virtual void vf10(/* unknown signature */);
    /* 0x14 */ DECL_WEAK virtual void SetMatrices(nw4r::math::MTX34* matrices);

    /* Class Methods */

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

    /* Class Members */

    /* 0x04 */ int mState;
    /* 0x08 */ std::string mResourcePath;
    /* 0x14 */ bool m_14;
    /* 0x18 */ gfl::ResFileObject mResFileObject;
    /* 0x1C */ gfl::LinkedList<gfl::ResFileObject> mResFileObjects;
    /* 0x28 */ gfl::Pointer<FlfMdlDraw> mFlfMdlDraw;
    /* 0x2C */ gfl::ScnMdlWrapper* mScnMdlWrapper;
    /* 0x30 */ gfl::Pointer<FlfDemoCamCtrl> mCamCtrl;
    /* 0x34 */ FlfDemoCtrlStruct* m_34;
    /* 0x38 */ gfl::Task mTask;
    /* 0x50 */ gfl::LinkedList<FlfDemoNodeCtrl*> mNodeCtrls;
};


#endif
