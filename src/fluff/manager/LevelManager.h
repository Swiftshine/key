#ifndef FLUFF_LEVELMANAGER_H
#define FLUFF_LEVELMANAGER_H

#include "types.h"
#include "stage/Stage.h"
#include "object/collision/ColObjTree.h"
#include "manager/GmkMng.h"
#include "stage/StageGraphicResources.h"
#include "gfl/gflPointer.h"
#include <nw4r/math.h>

class LevelManager {
public:
    LevelManager(Stage& stage);
    ~LevelManager();
    
    void SetGraphicsStage() DONT_INLINE_CLASS;
    bool IsLoadedFromFolder() DONT_INLINE_CLASS;
    void ResetPhase() DONT_INLINE_CLASS;
    void InitColObjTree() DONT_INLINE_CLASS;
    void LoadLevelGraphics() DONT_INLINE_CLASS;
    bool fn_800444C0() DONT_INLINE_CLASS;
    void fn_800444C8() DONT_INLINE_CLASS;
    void SetBGSTEntryEnabled(uint index, bool value) DONT_INLINE_CLASS;
    // related to loading phase
    void fn_800444D8() DONT_INLINE_CLASS;
    void fn_80044564() DONT_INLINE_CLASS;
    void fn_8004456C() DONT_INLINE_CLASS;
    void fn_80044574(bool val) DONT_INLINE_CLASS;


private:
    int mLoadPhase;
    Stage mStage;
    gfl::Pointer<ColObjTree> mColObjTree;
    gfl::Pointer<GmkMng> mGimmickManager;
    StageGraphicResources mGraphicResources;
};

#endif
