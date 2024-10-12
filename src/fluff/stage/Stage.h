#ifndef FLUFF_STAGE_H
#define FLUFF_STAGE_H

#include "types.h"

class Stage {
public:
    inline Stage() { }

    inline Stage(const Stage& other) {
        mStageID = other.mStageID;
        mResourceID = other.mResourceID;
        mSectionID = other.mSectionID;
    }

    inline Stage(int val) {
        mStageID = val;
        mResourceID = val;
        mSectionID = val;
    }

    inline Stage(int st, int re, int se) {
        mStageID = st;
        mResourceID = re;
        mSectionID = se;
    }

    inline Stage(const Stage* other) {
        mStageID = other->mStageID;
        mResourceID = other->mResourceID;
        mSectionID = other->mSectionID;
    }

    inline void operator=(const Stage& other) {
        mStageID = other.mStageID;
        mResourceID = other.mResourceID;
        mSectionID = other.mSectionID;
    }

    inline void operator=(const Stage* other) {
        mStageID = other->mStageID;
        mResourceID = other->mResourceID;
        mSectionID = other->mSectionID;
    }

    int GetStageID() const {
        return mStageID;
    }

    int GetResourceID() const {
        return mResourceID;
    }

    int GetSectionID() const {
        return mSectionID;
    }

    void SetStageID(int id) {
        mStageID = id;
    }

    void SetResourceID(int id) {
        mResourceID = id;
    }

    void SetSectionID(int id) {
        mSectionID = id;
    }
private:
    // The actual numeric stage number. Level 1 is 1, level 2 is 2...
    int mStageID;
    // This is used for finding files from disk. Level 1 is 101, level 2 is 102...
    int mResourceID;
    // This is used for stages that span multiple sections that need to be loaded seperately. A notable example is the world map.
    uint mSectionID;
};

ENUM_CLASS(StageIDs,
    // Misc.
    WorldMap = 50,

    // Grass Land
    FountainGardens   = 1,
    FlowerFields      = 2,
    RainbowFalls      = 3,
    BigBeanVine       = 4,
    MoleHole          = 5,
    WeirdWoods        = 6,

    // Hot Land
    PyramidSands      = 7,
    LavaLanding       = 8,
    CoolCave          = 9,
    DinoJungle        = 10,
    TemperTemple      = 11,
    DuskDunes         = 12,

    // Treat Land
    ToyTracks         = 13,
    MushroomRun       = 14,
    SweetsPark        = 15,
    MelodyTown        = 16,
    CocoaStation      = 17,
    DarkManor         = 18,

    // Water Land
    SplashBeach       = 19,
    BlubBlubOcean     = 20,
    SecretIsland      = 21,
    DeepDiveDeep      = 22,
    BoomBoatyard      = 23,
    FossilReef        = 24,

    // Snow Land
    SnowyFields       = 25,
    CozyCabin         = 26,
    MtSlide           = 27,
    FrostyWheel       = 28,
    FrigidFjords      = 29,
    EvergreenLift     = 30,

    // Space Land
    FutureCity        = 31,
    TubeTown          = 32,
    MysteriousUFO     = 33,
    StellarWay        = 34,
    MoonBase          = 35,
    OuterRings        = 36,

    // Dream Land
    WhispysForest     = 37,
    TempestTowers     = 38,
    CloudPalace       = 39,
    CastleDedede      = 40,
    MetaMelonIsle     = 41,
    BattleshipHalberd = 42,
);

ENUM_CLASS(ResourceIDs,
    // Misc.
    WorldMap          = 0,

    // Quilty Square
    PatchCastle       = 100,

    // Grass Land
    FountainGardens   = 101,
    FlowerFields      = 102,
    RainbowFalls      = 103,
    BigBeanVine       = 104,
    MoleHole          = 105,
    WeirdWoods        = 106,

    // Hot Land
    PyramidSands      = 107,
    LavaLanding       = 108,
    CoolCave          = 109,
    DinoJungle        = 110,
    TemperTemple      = 111,
    DuskDunes         = 112,

    // Treat Land
    ToyTracks         = 113,
    MushroomRun       = 114,
    SweetsPark        = 115,
    MelodyTown        = 116,
    CocoaStation      = 117,
    DarkManor         = 118,

    // Water Land
    SplashBeach       = 119,
    BlubBlubOcean     = 120,
    SecretIsland      = 121,
    DeepDiveDeep      = 122,
    BoomBoatyard      = 123,
    FossilReef        = 124,

    // Snow Land
    SnowyFields       = 125,
    CozyCabin         = 126,
    MtSlide           = 127,
    FrostyWheel       = 128,
    FrigidFjords      = 129,
    EvergreenLift     = 130,

    // Space Land
    FutureCity        = 131,
    TubeTown          = 132,
    MysteriousUFO     = 133,
    StellarWay        = 134,
    MoonBase          = 135,
    OuterRings        = 136,

    // Dream Land
    WhispysForest     = 137,
    TempestTowers     = 138,
    CloudPalace       = 139,
    CastleDedede      = 140,
    MetaMelonIsle     = 141,
    BattleshipHalberd = 142,

    // Bossfights
    Fangora           = 301,
    HotWings          = 302,
    Squashini         = 303,
    Capamari          = 304,
    KingDedede        = 305,
    MetaKnight        = 306,
    YinYarn           = 307,
);

#endif
