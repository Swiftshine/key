#ifndef FLUFF_STAGE_H
#define FLUFF_STAGE_H

#include <flf_types.h>



struct Stage {
    s32 _0;
    s32 stageID;
    u32 sectionID;
};

SCOPED_ENUM(StageIDs,
    // Misc.
    Stage_WorldMap          = 0,

    // Quilty Square
    Stage_PatchCastle       = 100,

    // Grass Land
    Stage_FountainGardens   = 101,
    Stage_FlowerFields      = 102,
    Stage_RainbowFalls      = 103,
    Stage_BigBeanVine       = 104,
    Stage_MoleHole          = 105,
    Stage_WeirdWoods        = 106,

    // Hot Land
    Stage_PyramidSands      = 107,
    Stage_LavaLanding       = 108,
    Stage_CoolCave          = 109,
    Stage_DinoJungle        = 110,
    Stage_TemperTemple      = 111,
    Stage_DuskDunes         = 112,

    // Treat Land
    Stage_ToyTracks         = 113,
    Stage_MushroomRun       = 114,
    Stage_SweetsPark        = 115,
    Stage_MelodyTown        = 116,
    Stage_CocoaStation      = 117,
    Stage_DarkManor         = 118,

    // Water Land
    Stage_SplashBeach       = 119,
    Stage_BlubBlubOcean     = 120,
    Stage_SecretIsland      = 121,
    Stage_DeepDiveDeep      = 122,
    Stage_BoomBoatyard      = 123,
    Stage_FossilReef        = 124,

    // Snow Land
    Stage_SnowyFields       = 125,
    Stage_CozyCabin         = 126,
    Stage_MtSlide           = 127,
    Stage_FrostyWheel       = 128,
    Stage_FrigidFjords      = 129,
    Stage_EvergreenLift     = 130,

    // Space Land
    Stage_FutureCity        = 131,
    Stage_TubeTown          = 132,
    Stage_MysteriousUFO     = 133,
    Stage_StellarWay        = 134,
    Stage_MoonBase          = 135,
    Stage_OuterRings        = 136,

    // Dream Land
    Stage_WhispysForest     = 137,
    Stage_TempestTowers     = 138,
    Stage_CloudPalace       = 139,
    Stage_CastleDedede      = 140,
    Stage_MetaMelonIsle     = 141,
    Stage_BattleshipHalberd = 142,

    // Bossfights
    Stage_Fangora           = 301,
    Stage_HotWings          = 302,
    Stage_Squashini         = 303,
    Stage_Capamari          = 304,
    Stage_KingDedede        = 305,
    Stage_MetaKnight        = 306,
    Stage_YinYarn           = 307,
);

#endif
