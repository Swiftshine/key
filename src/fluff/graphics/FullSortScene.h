#ifndef FLUFF_FULLSORTSCENE_H
#define FLUFF_FULLSORTSCENE_H

#include <types.h>

#include <gfl/gflScene.h>
#include <gfl/gflScnMdlWrapper.h>

#include <graphics/FullSortGroup.h>
#include <object/effect/EffectObj.h>

// size: 0x34
class FullSortScene : public gfl::Scene {
public:
    enum SceneID {
        eSceneID_Far_05  = 0,
        eSceneID_Far_04  = 1,
        eSceneID_Far_03  = 2,
        eSceneID_Far_02  = 3,
        eSceneID_Far_01  = 4,
        eSceneID_Map     = 5,
        eSceneID_Game    = 6,
        eSceneID_Near_01 = 7,
        eSceneID_Near_02 = 8,
        eSceneID_Near_03 = 9,
        eSceneID_Near_04 = 10,
        eSceneID_Near_05 = 11
    };

    FullSortScene(u8 heapID, u32 maxNumChildren, u32 maxNumScnObj);

    /* Virtual Methods */

    /* 0x08 */ virtual ~FullSortScene();

    /* 0x10 */ virtual void Insert(nw4r::g3d::ScnObj* object) override;
    /* 0x14 */ virtual bool Remove(nw4r::g3d::ScnObj* object) override;
    /* 0x18 */ virtual void DrawOpa() override;
    /* 0x1C */ virtual void DrawXlu() override;
    /* 0x20 */ virtual bool IsScnRootSizeValid() override;

    /* Class Methods */

    EffectObj* CreateEffectObject(const char* pEffectName, s32, s32);

    /* Class Members */

    /* 0x30 */ FullSortGroup* mFullSortGroup;
};

ASSERT_SIZE(FullSortScene, 0x34);

#endif
