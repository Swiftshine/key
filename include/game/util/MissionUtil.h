#ifndef FLUFF_UTIL_MISSION_H
#define FLUFF_UTIL_MISSION_H


#include <flf_types.h>
#include <gfl/string/BasicString.h>

namespace FluffUtil {
namespace Mission {
    // Prefixes to enumerators are defined by what the corresponding mapbin is prefixed with for each Quilty Square resident.
    // mb - Beadrix - bead collection
    // mt - Mara - time trial against Mara
    // md - Buster - defeating enemies
    // ms - Zeke - seeking Zeke
    // mc - Carrie - carrying Carrie to the goal

    SCOPED_ENUM(MissionID,
        NoMission = 0,

        // Beadrix's Run - Collect beads within the time limit
        MB_FlowerFields = 100,
        MB_PyramidSands = 101,
        MB_BigBeanVine = 102,
        MB_SweetsPark = 103,
        MB_BlubBlubOcean = 104,
        MB_DeepDiveDeep = 105,
        MB_LavaLanding = 106,
        MB_MtSlide = 107,
        MB_StellarWay = 108,
        MB_DinoJungle = 109,
        MB_MushroomRun = 110,
        MB_FountainGardens = 111,
        MB_WhispysForest = 112,
        MB_CozyCabin = 113,
        MB_FutureCity = 114,
        MB_MoleHole = 115,
        MB_EvergreenLift = 116,
        MB_MoonBase = 117,
        MB_BattleshipHalberd = 118,
        MB_OuterRings = 119,

        // Mara's Race - Reach the goal before Mara
        MT_PatchCastle = 200,
        MT_FountainGardens = 201,
        MT_FlowerFields = 202,
        MT_RainbowFalls = 203,
        MT_BigBeanVine = 204,
        MT_PyramidSands = 205,
        MT_LavaLanding = 206,
        MT_CoolCave = 207,
        MT_DinoJungle = 208,
        MT_ToyTracks = 209,
        MT_MushroomRun = 210,
        MT_SweetsPark = 211,
        MT_MelodyTown = 212,
        MT_SplashBeach = 213,
        MT_BlubBlubOcean = 214,
        MT_SecretIsland = 215,
        MT_DeepDiveDeep = 216,
        MT_SnowyFields = 217,
        MT_CozyCabin = 218,
        MT_FrostyWheel = 219,
        MT_FutureCity = 220,
        MT_TubeTown = 221,
        MT_StellarWay = 222,
        MT_WhispysForest = 223,
        MT_TempestTowers = 224,
        MT_CloudPalace = 225,
        MT_CastleDedede = 226,
        MT_MoleHole = 227,
        MT_DarkManor = 228,
        MT_FossilReef = 229,

        // Buster's Training - Defeat enemies within the time limit
        MD_SweetsPark = 300,
        MD_RainbowFalls = 301,
        MD_PyramidSands = 302,
        MD_MushroomRun = 303,
        MD_MelodyTown = 304,
        MD_CoolCave = 305,
        MD_DinoJungle = 306,
        MD_SplashBeach = 307,
        MD_BlubBlubOcean = 308,
        MD_SnowyFields = 309,
        MD_FrostyWheel = 310,
        MD_MysteriousUFO = 311,
        MD_StellarWay = 312,
        MD_WhispysForest = 313,
        MD_TempestTowers = 314,
        MD_CloudPalace = 315,
        MD_WeirdWoods = 316,
        MD_DarkManor = 317,
        MD_BoomBoatyard = 318,
        MD_EvergreenLift = 319,

        // Carrie's Transport - Carry Carrie to the goal within the time limit
        MC_PatchCastle = 400,
        MC_FountainGardens = 401,
        MC_FlowerFields = 402,
        MC_LavaLanding = 403,
        MC_MushroomRun = 404,
        MC_MelodyTown = 405,
        MC_SplashBeach = 406,
        MC_SecretIsland = 407,
        MC_CozyCabin = 408,
        MC_TubeTown = 409,
        MC_BigBeanVine = 410,
        MC_TempestTowers = 411,

        // Zeke's Hide-and-Seek - Find Zeke's clones within the time limit
        MS_FountainGardens = 500,
        MS_RainbowFalls = 501,
        MS_BigBeanVine = 502,
        MS_PyramidSands = 503,
        MS_CoolCave = 504,
        MS_FlowerFields = 505,
        MS_DinoJungle = 506,
        MS_ToyTracks = 507,
        MS_MushroomRun = 508,
        MS_SweetsPark = 509,
        MS_MelodyTown = 510,
        MS_SplashBeach = 511,
        MS_BlubBlubOcean = 512,
        MS_SnowyFields = 513,
        MS_FutureCity = 514,
        MS_TempestTowers = 515,
        MS_MoleHole = 516,
        MS_DarkManor = 517
    );

    SCOPED_ENUM(MissionType,
        None    = 0,
        Bead    = 1,
        Time    = 2,
        Defeat  = 3,
        Carry   = 4,
        Seek    = 5,
    );
    
    SCOPED_ENUM(MissionIndicator,
        None    = 'N', 
        Bead    = 'B',
        Time    = 'T',
        Defeat  = 'D',
        Carry   = 'C',
        Seek    = 'S',
    );

    SCOPED_ENUM(MissionCode,
        None    = -1,
        Bead    = 0,
        Time    = 1,
        Seek    = 2,
        Carry   = 3,
        Defeat  = 4,
    );

    SCOPED_ENUM(MissionCount,
        None    = 0,
        Bead    = 20,
        Time    = 30,
        Defeat  = 20,
        Carry   = 12,
        Seek    = 18,
    );

    SCOPED_ENUM(MissionIDBase,
        None    = 0,
        Bead    = 100,
        Time    = 200,
        Defeat  = 300,
        Carry   = 400,
        Seek    = 500,    
    );

    static const char MissionIndicators[] = "NBTDCS";

    int  GetMissionTypeByCode(int code);
    int  GetMissionCodeByType(int type);
    int  GetMissionCountByType(int type);
    int  GetMissionIDBaseByType(int type);
    char GetMissionIdentifierByType(int type);
    bool HasMissionIndicator(int type, gfl::BasicString* str);
    int  GetMissionIDByInfo(int type, int index);
    void GetMissionInfoByID(int id, int* destType, int* destIndex);
    int  GetMissionTypeByID(int id);
    int  GetMissionIndexByID(int id);
    u32  GetMissionMagic(gfl::BasicString* str);
} // Mission
} // FluffUtil

#endif
