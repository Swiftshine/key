#ifndef FLUFF_STAGEINFO_H
#define FLUFF_STAGEINFO_H

#include "types.h"

class StageInfo {
public:
    inline StageInfo() { }

    inline StageInfo(const StageInfo& other) {
        mStageID = other.mStageID;
        mResourceID = other.mResourceID;
        mSectionID = other.mSectionID;
    }

    inline StageInfo(s32 val) {
        mStageID = val;
        mResourceID = val;
        mSectionID = val;
    }

    inline StageInfo(s32 st, s32 re, s32 se) {
        mStageID = st;
        mResourceID = re;
        mSectionID = se;
    }

    inline StageInfo(const StageInfo* other) {
        mStageID = other->mStageID;
        mResourceID = other->mResourceID;
        mSectionID = other->mSectionID;
    }

    inline void operator=(const StageInfo& other) {
        mStageID = other.mStageID;
        mResourceID = other.mResourceID;
        mSectionID = other.mSectionID;
    }

    inline void operator=(const StageInfo* other) {
        mStageID = other->mStageID;
        mResourceID = other->mResourceID;
        mSectionID = other->mSectionID;
    }

    s32 GetStageID() const {
        return mStageID;
    }

    u32 GetResourceID() const {
        return mResourceID;
    }

    s32 GetSectionID() const {
        return mSectionID;
    }

    void SetStageID(s32 id) {
        mStageID = id;
    }

    void SetResourceID(s32 id) {
        mResourceID = id;
    }

    void SetSectionID(s32 id) {
        mSectionID = id;
    }
private:
    // The actual numeric stage number. Level 1 is 1, level 2 is 2...
    s32 mStageID;
    // This is used for finding files from disk. Level 1 is 101, level 2 is 102...
    u32 mResourceID;
    // This is used for stages that span multiple sections that need to be loaded seperately. A notable example is the world map.
    u32 mSectionID;
};

enum StageID {
    // Grass Land
    eStageID_FountainGardens   = 1,
    eStageID_FlowerFields      = 2,
    eStageID_RainbowFalls      = 3,
    eStageID_BigBeanVine       = 4,
    eStageID_MoleHole          = 5,
    eStageID_WeirdWoods        = 6,

    // Hot Land
    eStageID_PyramidSands      = 7,
    eStageID_LavaLanding       = 8,
    eStageID_CoolCave          = 9,
    eStageID_DinoJungle        = 10,
    eStageID_TemperTemple      = 11,
    eStageID_DuskDunes         = 12,

    // Treat Land
    eStageID_ToyTracks         = 13,
    eStageID_MushroomRun       = 14,
    eStageID_SweetsPark        = 15,
    eStageID_MelodyTown        = 16,
    eStageID_CocoaStation      = 17,
    eStageID_DarkManor         = 18,

    // Water Land
    eStageID_SplashBeach       = 19,
    eStageID_BlubBlubOcean     = 20,
    eStageID_SecretIsland      = 21,
    eStageID_DeepDiveDeep      = 22,
    eStageID_BoomBoatyard      = 23,
    eStageID_FossilReef        = 24,

    // Snow Land
    eStageID_SnowyFields       = 25,
    eStageID_CozyCabin         = 26,
    eStageID_MtSlide           = 27,
    eStageID_FrostyWheel       = 28,
    eStageID_FrigidFjords      = 29,
    eStageID_EvergreenLift     = 30,

    // Space Land
    eStageID_FutureCity        = 31,
    eStageID_TubeTown          = 32,
    eStageID_MysteriousUFO     = 33,
    eStageID_StellarWay        = 34,
    eStageID_MoonBase          = 35,
    eStageID_OuterRings        = 36,

    // Dream Land
    eStageID_WhispysForest     = 37,
    eStageID_TempestTowers     = 38,
    eStageID_CloudPalace       = 39,
    eStageID_CastleDedede      = 40,
    eStageID_MetaMelonIsle     = 41,
    eStageID_BattleshipHalberd = 42,

    // Bossfights
    eStageID_Fangora           = 43,
    eStageID_HotWings          = 44,
    eStageID_Squashini         = 45,
    eStageID_Capamari          = 46,
    eStageID_KingDedede        = 47,
    eStageID_MetaKnight        = 48,
    eStageID_YinYarn           = 49,

    // Misc.
    eStageID_WorldMap          = 50,
};

enum ResourceID {
    // Misc.
    eResourceID_WorldMap          = 0,

    // Quilty Square
    eResourceID_PatchCastle       = 100,

    // Grass Land
    eResourceID_FountainGardens   = 101,
    eResourceID_FlowerFields      = 102,
    eResourceID_RainbowFalls      = 103,
    eResourceID_BigBeanVine       = 104,
    eResourceID_MoleHole          = 105,
    eResourceID_WeirdWoods        = 106,

    // Hot Land
    eResourceID_PyramidSands      = 107,
    eResourceID_LavaLanding       = 108,
    eResourceID_CoolCave          = 109,
    eResourceID_DinoJungle        = 110,
    eResourceID_TemperTemple      = 111,
    eResourceID_DuskDunes         = 112,

    // Treat Land
    eResourceID_ToyTracks         = 113,
    eResourceID_MushroomRun       = 114,
    eResourceID_SweetsPark        = 115,
    eResourceID_MelodyTown        = 116,
    eResourceID_CocoaStation      = 117,
    eResourceID_DarkManor         = 118,

    // Water Land
    eResourceID_SplashBeach       = 119,
    eResourceID_BlubBlubOcean     = 120,
    eResourceID_SecretIsland      = 121,
    eResourceID_DeepDiveDeep      = 122,
    eResourceID_BoomBoatyard      = 123,
    eResourceID_FossilReef        = 124,

    // Snow Land
    eResourceID_SnowyFields       = 125,
    eResourceID_CozyCabin         = 126,
    eResourceID_MtSlide           = 127,
    eResourceID_FrostyWheel       = 128,
    eResourceID_FrigidFjords      = 129,
    eResourceID_EvergreenLift     = 130,

    // Space Land
    eResourceID_FutureCity        = 131,
    eResourceID_TubeTown          = 132,
    eResourceID_MysteriousUFO     = 133,
    eResourceID_StellarWay        = 134,
    eResourceID_MoonBase          = 135,
    eResourceID_OuterRings        = 136,

    // Dream Land
    eResourceID_WhispysForest     = 137,
    eResourceID_TempestTowers     = 138,
    eResourceID_CloudPalace       = 139,
    eResourceID_CastleDedede      = 140,
    eResourceID_MetaMelonIsle     = 141,
    eResourceID_BattleshipHalberd = 142,

    // Bossfights
    eResourceID_Fangora           = 301,
    eResourceID_HotWings          = 302,
    eResourceID_Squashini         = 303,
    eResourceID_Capamari          = 304,
    eResourceID_KingDedede        = 305,
    eResourceID_MetaKnight        = 306,
    eResourceID_YinYarn           = 307,
};

#endif
