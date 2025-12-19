#ifndef FLUFF_STAGEGRAPHICRESOURCES_H
#define FLUFF_STAGEGRAPHICRESOURCES_H


#include "types.h"

#include "stage/StageInfo.h"
#include "object/collision/ColData.h"
#include "gfl/gflResFileInfo.h"
#include "graphics/BGSTFile.h"
#include "graphics/BGSTLayer.h"
#include "graphics/BgBackImage.h"


class StageGraphicResources {
public:
    StageGraphicResources();
    ~StageGraphicResources();

    void SetStage(StageInfo& stage);
    bool IsLoadedFromFolder();
    void LoadLevelGraphics();
    bool fn_800C566C();
    void fn_800C56D0();
    void SetBGSTLayerEnabled(uint index, bool value);
    void fn_800C57C4();
    void fn_800C59A4();
    void fn_800C59BC();

    inline void SetUnk20(bool val) {
        m_20 = val;
    }
private:
    uint mLoadPhase;
    nw4r::math::VEC3 mBGPosition;
    bool m_10;
    bool m_11;
    StageInfo mStage;
    bool m_20;
    ColDataSegLabel* mColDataSegLabel;
    uint m_28;
    uint m_2C;
    gfl::ResFileInfo* mResFileInfo;
    uint m_34;
    uint m_38;
    uint m_3C;
    uint m_40;
    BGST::File* mBGSTFile;
    BGST::Layer* mBGSTLayers;
    BgBackImage* mBgBackImage;
};


#endif
