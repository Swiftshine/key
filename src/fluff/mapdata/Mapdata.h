#ifndef FLUFF_MAPDATA_H
#define FLUFF_MAPDATA_H

#include "types.h"
#include <string>
#include <nw4r/math.h>
#include "object/collision/Colbin.h"
#include "object/collision/ColData.h"
#include "object/Gimmick.h"
#include "gfl/gflArray.h"

/// @brief A representation of stage entity data used in game for parsing and processing.
/// @note Size: `0x4C`
class Mapdata {
public:

    /* Structures */

    /// @note Size: `0x3C`
    struct MapdataParams {
        /* 0x00 */ int mIntParams[3];
        /* 0x0C */ float mFloatParams[3];
        /* 0x18 */ std::string mStringParams[3];
    };

    /// @note Size: 0x28
    struct MapdataCommonGimmick {
        static bool fn_8004f604(Gimmick::GimmickBuildInfo* pBuildInfo);

        /* 0x0 */ bool m_0;
        /* 0x1 */ bool m_1;
        /* 0x4 */ uint m_4;
        /* 0x8 */ char m_8[32];
    };

    /// @note Size: `0x54`
    struct MapdataGimmick {
        void BuildFriend01();

        /* 0x00 */ std::string mName;
        /* 0x0C */ nw4r::math::VEC3 mPosition;
        /* 0x18 */ MapdataParams mParams;
    };

    /// @note Size: `0x50`
    struct MapdataPath {
        void SetupWoolBridges(Mapdata* pMapdata);
        bool IsMsKeepOutLine();
        bool BuildReleaseHenshin2();
        bool BuildNeedle();
        bool BuildPathDraw();
        bool BuildMsKeepOutLine();

        /* 0x00 */ std::string mName;
        /* 0x0C */ MapdataParams mParams;
        /* 0x48 */ uint mNumPoints;
        /* 0x4C */ gfl::Array<nw4r::math::VEC2> mPoints;
    };

    /// @note Size: `0x58`
    struct MapdataZone {
        bool BuildLadder();
        bool BuildMokoMoko();
        bool BuildWater();
        bool BuildPlayerAreaSwitch();
        bool BuildBackDoorWindow();
        bool BuildBackDoorCancel();
        bool BuildSideBackDoor();
        bool BuildBlizzard();
        bool BuildChangeWind();
        bool BuildChangeWind2();
        bool BuildPlStateChg();
        bool BuildBallRelease();
        bool BuildBackDoorZMask();

        /* 0x00 */ std::string mName;
        /* 0x0C */ MapdataParams mParams;
        /* 0x48 */ nw4r::math::VEC2 mBoundsMin;
        /* 0x50 */ nw4r::math::VEC2 mBoundsMax;
    };

    /// @note Size: `0x54`
    struct MapdataCourseInfo {
        /* 0x00 */ std::string mName;
        /* 0x0C */ MapdataParams mParams;
        /* 0x48 */ nw4r::math::VEC3 mPosition;
    };

    /* Class Methods */

    void RegisterStageResources();
    void ConstructObjects();
    void ConstructMoleBlocks();

    inline Gimmick::GimmickBuildInfo* GetCommonGimmickBuildInfo(uint index) {
        return &mCommonGimmickBuildInfos[index];
    }

    /* Static Methods */

    static Mapdata* Parse(const char* pFilepath, bool isInMission);
    static void Delete(Mapdata* pMapdata);

    /* Class Members */

    /* 0x00 */ nw4r::math::VEC2 mBoundsMin;
    /* 0x08 */ nw4r::math::VEC2 mBoundsMax;
    /* 0x10 */ uint mNumWalls;
    /* 0x14 */ ColDataSeg* mWalls;
    /* 0x18 */ uint mNumLabeledWalls;
    /* 0x1C */ ColDataSegLabel* mLabeledWalls;
    /* 0x20 */ uint mNumCommonGimmicks;
    /* 0x24 */ gfl::Array<Gimmick::GimmickBuildInfo> mCommonGimmickBuildInfos;
    /* 0x28 */ MapdataCommonGimmick* mCommonGimmicks;
    /* 0x2C */ uint mNumGimmicks;
    /* 0x30 */ MapdataGimmick* mGimmicks;
    /* 0x34 */ uint mNumPaths;
    /* 0x38 */ MapdataPath* mPaths;
    /* 0x3C */ uint mNumZones;
    /* 0x40 */ MapdataZone* mZones;
    /* 0x44 */ uint mNumCourseInfo;
    /* 0x48 */ MapdataCourseInfo* mCourseInfos;
};

ASSERT_SIZE(Mapdata, 0x4C);

/// @brief A representation of stage entity data stored on disk.
/// @note Size: `0x58`
struct Mapbin {
    /* 0x00 */ float m_0;
    /* 0x04 */ nw4r::math::VEC2 mBoundsMin;
    /* 0x0C */ nw4r::math::VEC2 mBoundsMax;
    /* 0x14 */ u32 mNumWalls;
    /* 0x18 */ u32 mWallOffset;
    /* 0x1C */ u32 mNumLabeledWalls;
    /* 0x20 */ u32 mLabeledWallOffset;
    /* 0x24 */ u32 mNumCommonGimmicks;
    /* 0x28 */ u32 mCommonGimmickOffset;
    /* 0x2C */ u32 mNumGimmicks;
    /* 0x30 */ u32 mGimmickOffset;
    /* 0x34 */ u32 mNumPaths;
    /* 0x38 */ u32 mPathOffset;
    /* 0x3C */ u32 mNumZones;
    /* 0x40 */ u32 mZoneOffset;
    /* 0x44 */ u32 mNumCourseInfo;
    /* 0x48 */ u32 mCourseInfoOffset;
    /* 0x4C */ u32 mCommonGimmickNameOffset;
    /* 0x50 */ u32 mColbinTypeOffset;
    /* 0x54 */ u32 mLabeledWallLabels;
};

ASSERT_SIZE(Mapbin, 0x58);

// TODO: place the rest of the Mapbin documentation here

#endif
