#ifndef FLUFF_FULLSORTSCENE_H
#define FLUFF_FULLSORTSCENE_H

#include "types.h"
#include "gfl/gflScene.h"
#include "gfl/gflScnMdlWrapper.h"
#include "graphics/FullSortGroup.h"
#include "object/effect/EffectObj.h"

// size: 0x34
class FullSortScene : public gfl::Scene {
public:
    

    FullSortScene(u8 heapID, uint maxNumChildren, uint maxNumScnObj);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FullSortScene();

    /* 0x10 */ virtual void Insert(nw4r::g3d::ScnObj* object) override;
    /* 0x14 */ virtual void Remove(nw4r::g3d::ScnObj* object) override;
    /* 0x18 */ virtual void DrawOpa() override;
    /* 0x1C */ virtual void DrawXlu() override;
    /* 0x20 */ virtual bool IsScnRootSizeValid() override;

    /* Class Methods */

    EffectObj* CreateEffectObject(const char* pEffectName, int, int);

    /* Class Members */

    /* 0x30 */ FullSortGroup* mFullSortGroup;
};

ASSERT_SIZE(FullSortScene, 0x34);

#endif
