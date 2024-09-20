#ifndef FLUFF_STAGEGRAPHICRESOURCES_H
#define FLUFF_STAGEGRAPHICRESOURCES_H


#include "types.h"
#include "gfl/gflVec3.h"
#include "stage/Stage.h"
#include "object/collision/ColDataSegLabel.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/BGSTFile.h"
#include "graphics/FbDof.h"
class StageGraphicResources {
public:

private:
    uint mLoadPhase;
    gfl::Vec3 mBGPosition;
    bool m_10;
    bool m_11;
    Stage mStage;
    uint m_20;
    ColDataSegLabel* mColDataSegLabel;
    uint m_28;
    uint m_2C;
    gfl::ResFileInfo* mResFileInfo;
    uint m_34;
    uint m_38;
    uint m_3C;
    uint m_40;
    BGSTFile* mBGSTFile;
    void* m_48; // i labeled this as "depth of field" in my ghidra project at some point. unsure of what this is for now
    FbDof* mFbDof;
};


#endif