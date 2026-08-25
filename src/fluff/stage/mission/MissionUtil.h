#ifndef FLUFF_MISSIONUTIL_H
#define FLUFF_MISSIONUTIL_H

#include "types.h"
#include <string>


namespace MissionUtil {
    /*

    Prefixes to enumerators are defined by what the corresponding mapbin
    is prefixed with for each Quilty Square resident.

    mb - Beadrix - bead collection
    mt - Mara - time trial against Mara
    md - Buster - defeating enemies
    ms - Zeke - seeking Zeke
    mc - Carrie - carrying Carrie to the goal

    */

    enum MissionID {
        eMissionID_NoMission               = 0,

        // Beadrix's Run - Collect beads within the time limit
        eMissionID_MB_FlowerFields         = 100,
        eMissionID_MB_PyramidSands         = 101,
        eMissionID_MB_BigBeanVine          = 102,
        eMissionID_MB_SweetsPark           = 103,
        eMissionID_MB_BlubBlubOcean        = 104,
        eMissionID_MB_DeepDiveDeep         = 105,
        eMissionID_MB_LavaLanding          = 106,
        eMissionID_MB_MtSlide              = 107,
        eMissionID_MB_StellarWay           = 108,
        eMissionID_MB_DinoJungle           = 109,
        eMissionID_MB_MushroomRun          = 110,
        eMissionID_MB_FountainGardens      = 111,
        eMissionID_MB_WhispysForest        = 112,
        eMissionID_MB_CozyCabin            = 113,
        eMissionID_MB_FutureCity           = 114,
        eMissionID_MB_MoleHole             = 115,
        eMissionID_MB_EvergreenLift        = 116,
        eMissionID_MB_MoonBase             = 117,
        eMissionID_MB_BattleshipHalberd    = 118,
        eMissionID_MB_OuterRings           = 119,

        // Mara's Race - Reach the goal before Mara
        eMissionID_MT_PatchCastle          = 200,
        eMissionID_MT_FountainGardens      = 201,
        eMissionID_MT_FlowerFields         = 202,
        eMissionID_MT_RainbowFalls         = 203,
        eMissionID_MT_BigBeanVine          = 204,
        eMissionID_MT_PyramidSands         = 205,
        eMissionID_MT_LavaLanding          = 206,
        eMissionID_MT_CoolCave             = 207,
        eMissionID_MT_DinoJungle           = 208,
        eMissionID_MT_ToyTracks            = 209,
        eMissionID_MT_MushroomRun          = 210,
        eMissionID_MT_SweetsPark           = 211,
        eMissionID_MT_MelodyTown           = 212,
        eMissionID_MT_SplashBeach          = 213,
        eMissionID_MT_BlubBlubOcean        = 214,
        eMissionID_MT_SecretIsland         = 215,
        eMissionID_MT_DeepDiveDeep         = 216,
        eMissionID_MT_SnowyFields          = 217,
        eMissionID_MT_CozyCabin            = 218,
        eMissionID_MT_FrostyWheel          = 219,
        eMissionID_MT_FutureCity           = 220,
        eMissionID_MT_TubeTown             = 221,
        eMissionID_MT_StellarWay           = 222,
        eMissionID_MT_WhispysForest        = 223,
        eMissionID_MT_TempestTowers        = 224,
        eMissionID_MT_CloudPalace          = 225,
        eMissionID_MT_CastleDedede         = 226,
        eMissionID_MT_MoleHole             = 227,
        eMissionID_MT_DarkManor            = 228,
        eMissionID_MT_FossilReef           = 229,

        // Buster's Training - Defeat enemies within the time limit
        eMissionID_MD_SweetsPark           = 300,
        eMissionID_MD_RainbowFalls         = 301,
        eMissionID_MD_PyramidSands         = 302,
        eMissionID_MD_MushroomRun          = 303,
        eMissionID_MD_MelodyTown           = 304,
        eMissionID_MD_CoolCave             = 305,
        eMissionID_MD_DinoJungle           = 306,
        eMissionID_MD_SplashBeach          = 307,
        eMissionID_MD_BlubBlubOcean        = 308,
        eMissionID_MD_SnowyFields          = 309,
        eMissionID_MD_FrostyWheel          = 310,
        eMissionID_MD_MysteriousUFO        = 311,
        eMissionID_MD_StellarWay           = 312,
        eMissionID_MD_WhispysForest        = 313,
        eMissionID_MD_TempestTowers        = 314,
        eMissionID_MD_CloudPalace          = 315,
        eMissionID_MD_WeirdWoods           = 316,
        eMissionID_MD_DarkManor            = 317,
        eMissionID_MD_BoomBoatyard         = 318,
        eMissionID_MD_EvergreenLift        = 319,

        // Carrie's Transport - Carry Carrie to the goal within the time limit
        eMissionID_MC_PatchCastle          = 400,
        eMissionID_MC_FountainGardens      = 401,
        eMissionID_MC_FlowerFields         = 402,
        eMissionID_MC_LavaLanding          = 403,
        eMissionID_MC_MushroomRun          = 404,
        eMissionID_MC_MelodyTown           = 405,
        eMissionID_MC_SplashBeach          = 406,
        eMissionID_MC_SecretIsland         = 407,
        eMissionID_MC_CozyCabin            = 408,
        eMissionID_MC_TubeTown             = 409,
        eMissionID_MC_BigBeanVine          = 410,
        eMissionID_MC_TempestTowers        = 411,

        // Zeke's Hide-and-Seek - Find Zeke's clones within the time limit
        eMissionID_MS_FountainGardens   = 500,
        eMissionID_MS_RainbowFalls      = 501,
        eMissionID_MS_BigBeanVine      = 502,
        eMissionID_MS_PyramidSands     = 503,
        eMissionID_MS_CoolCave         = 504,
        eMissionID_MS_FlowerFields     = 505,
        eMissionID_MS_DinoJungle       = 506,
        eMissionID_MS_ToyTracks        = 507,
        eMissionID_MS_MushroomRun      = 508,
        eMissionID_MS_SweetsPark       = 509,
        eMissionID_MS_MelodyTown       = 510,
        eMissionID_MS_SplashBeach      = 511,
        eMissionID_MS_BlubBlubOcean    = 512,
        eMissionID_MS_SnowyFields      = 513,
        eMissionID_MS_FutureCity       = 514,
        eMissionID_MS_TempestTowers    = 515,
        eMissionID_MS_MoleHole         = 516,
        eMissionID_MS_DarkManor        = 517
    };

    enum MissionType {
        eMissionType_None    = 0,
        eMissionType_Bead    = 1,
        eMissionType_Time    = 2,
        eMissionType_Defeat  = 3,
        eMissionType_Carry   = 4,
        eMissionType_Seek    = 5,
    };

    enum MissionIndicator {
        eMissionIndicator_None    = 'N',
        eMissionIndicator_Bead    = 'B',
        eMissionIndicator_Time    = 'T',
        eMissionIndicator_Defeat  = 'D',
        eMissionIndicator_Carry   = 'C',
        eMissionIndicator_Seek    = 'S',
    };

    enum MissionCode {
        eMissionCode_None    = -1,
        eMissionCode_Bead    = 0,
        eMissionCode_Time    = 1,
        eMissionCode_Seek    = 2,
        eMissionCode_Carry   = 3,
        eMissionCode_Defeat  = 4,
    };

    enum MissionCount {
        eMissionCount_None    = 0,
        eMissionCount_Bead    = 20,
        eMissionCount_Time    = 30,
        eMissionCount_Defeat  = 20,
        eMissionCount_Carry   = 12,
        eMissionCount_Seek    = 18,
    };

    enum MissionIDBase {
        eMissionIDBase_None    = 0,
        eMissionIDBase_Bead    = 100,
        eMissionIDBase_Time    = 200,
        eMissionIDBase_Defeat  = 300,
        eMissionIDBase_Carry   = 400,
        eMissionIDBase_Seek    = 500,
    };

    s32 DONT_INLINE GetMissionTypeByCode(s32 code) ;
    s32 DONT_INLINE GetMissionCodeByType(s32 type) ;
    s32 DONT_INLINE GetMissionCountByType(s32 type) ;
    s32 DONT_INLINE GetMissionIDBaseByType(s32 type);
    char DONT_INLINE GetMissionIdentifierByType(s32 type);
    bool HasMissionIndicator(s32 type, const std::string& rString);
    s32 GetMissionIDByInfo(s32 type, s32 index);
    void GetMissionInfoByID(s32 id, s32* pDestType, s32* pDestIndex);
    s32 DONT_INLINE GetMissionTypeByID(s32 id) ;
    s32 DONT_INLINE GetMissionIndexByID(s32 id) ;
    uint GetMissionMagicByID(s32 id);
} // MissionUtil

#endif
