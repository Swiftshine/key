#ifndef FLUFF_FULLSORTSCENE_H
#define FLUFF_FULLSORTSCENE_H

#include "types.h"
#include "gfl/gflScene.h"
#include "gfl/gflScnMdlWrapper.h"
#include "graphics/FullSortGroup.h"

// size: 0x34
class FullSortScene : public gfl::Scene {
public:
    FullSortScene(u8 heapID, uint maxNumChildren, uint maxNumScnObj);
    virtual ~FullSortScene();

    /* gfl::Scene */
    virtual void Insert(nw4r::g3d::ScnObj* object);
    virtual void Remove(nw4r::g3d::ScnObj* object);
    virtual void DrawOpa();
    virtual void DrawXlu();
    virtual bool IsScnRootSizeValid();
private:
    FullSortGroup* mFullSortGroup;
};

ASSERT_SIZE(FullSortScene, 0x34);

#endif
