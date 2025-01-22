#ifndef FLUFF_MAPDATA_H
#define FLUFF_MAPDATA_H

#include "types.h"
#include <string>
#include <nw4r/math.h>
#include "object/collision/Colbin.h"
#include "object/collision/ColData.h"
#include "object/Gimmick.h"
#include "gfl/gflArray.h"

// the representation of stage entity data
// used by the game for parsing and processing
class Mapdata {
public:
    struct MapdataParams {
        int mIntParams[3]; // @ 0x0
        float mFloatParams[3]; // @ 0xC
        std::string mStringParams[3]; // @ 0x18
    };

    struct MapdataCommonGimmick {
        static void fn_8004f604(GimmickBuildInfo* buildInfo);

        bool m_0;
        bool m_1;
        uint m_4;
        char m_8[32];
    };

    struct MapdataGimmick {
        void BuildFriend01();

        std::string mName; // @ 0x0
        nw4r::math::VEC3 mPosition; // @ 0xC
        MapdataParams mParams; // @ 0x18
    };

    struct MapdataPath {
        void SetupWoolBridges(Mapdata* owner);
        bool IsMsKeepOutLine();
        bool BuildReleaseHenshin2();
        bool BuildNeedle();
        bool BuildPathDraw();
        bool BuildMsKeepOutLine();

        std::string mName; // @ 0x0
        MapdataParams mParams; // @ 0xC
        uint mNumPoints; // @ 0x48
        gfl::Array<nw4r::math::VEC2> mPoints; // @ 0x4C
    };

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

        std::string mName; // @ 0x0
        MapdataParams mParams; // @ 0xC
        nw4r::math::VEC2 mBoundsMin; // @ 0x48
        nw4r::math::VEC2 mBoundsMax; // @ 0x50
    };

    struct MapdataCourseInfo {
        std::string mName; // @ 0x0
        MapdataParams mParams; // @ 0xC
        nw4r::math::VEC3 mPosition; // @ 0x48
    };
public:
    static Mapdata* Parse(const char* path, bool isInMission);
    static void Delete(Mapdata* mapdata);

    void RegisterStageResources();
    void ConstructObjects();
    void fn_804C6E04();

    inline uint GetNumCommonGimmicks() {
        return mNumCommonGimmicks;
    }

    inline Gimmick::GimmickBuildInfo* GetCommonGimmickBuildInfo(uint index) {
        return &mCommonGimmickBuildInfos[index];
    }
private:
    nw4r::math::VEC2 mBoundsMin;
    nw4r::math::VEC2 mBoundsMax;
    uint mNumWalls;
    ColDataSeg* mWalls;
    uint mNumLabeledWalls;
    ColDataSegLabel* mLabeledWalls;
    uint mNumCommonGimmicks;
    gfl::Array<Gimmick::GimmickBuildInfo> mCommonGimmickBuildInfos;
    MapdataCommonGimmick* mCommonGimmicks;
    uint mNumGimmicks;
    MapdataGimmick* mGimmicks;
    uint mNumPaths;
    MapdataPath* mPaths;
    uint mNumZones;
    MapdataZone* mZones;
    uint mNumCourseInfo;
    MapdataCourseInfo* mCourseInfos;
};

ASSERT_SIZE(Mapdata, 0x4C);

// the representation of stage entity data
// stored on disk
struct Mapbin {
    float m_0;
    nw4r::math::VEC2 mBoundsMin;
    nw4r::math::VEC2 mBoundsMax;
    u32 mNumWalls;
    u32 mWallOffset;
    u32 mNumLabeledWalls;
    u32 mLabeledWallOffset;
    u32 mNumCommonGimmicks;
    u32 mCommonGimmickOffset;
    u32 mNumGimmicks;
    u32 mGimmickOffset;
    u32 mNumPaths;
    u32 mPathOffset;
    u32 mNumZones;
    u32 mZoneOffset;
    u32 mNumCourseInfo;
    u32 mCourseInfoOffset;
    u32 mCommonGimmickNameOffset;
    u32 mColbinTypeOffset;
    u32 mLabeledWallLabels;
};


// class Mapdata {
// public:
//     class Mapbin {
//     public:
//         struct File {
//             nw4r::math::VEC2 mBoundsMin;
//             nw4r::math::VEC2 mBoundsMax;
//             u32 mNumWalls;
//             u32 mWallOffset;
//             u32 mNumLabeledWalls;
//             u32 mLabeledWallOffset;
//             u32 mNumCommonGimmicks;
//             u32 mCommonGimmickOffset;
//             u32 mNumGimmicks;
//             u32 mGimmickOffset;
//             u32 mNumPaths;
//             u32 mPathOffset;
//             u32 mNumZones;
//             u32 mZoneOffset;
//             u32 mNumCourseInfo;
//             u32 mCourseInfoOffset;
//             u32 mCommonGimmickNameOffset;
//             u32 mColbinTypeOffset;
//             u32 mLabeledWallLabels;
//         };

//         struct Header {
//             f32 m_0;
//             nw4r::math::VEC2 mBoundsMin;
//             nw4r::math::VEC2 mBoundsMax;
//             u32 mNumWalls;
//             u32 mWallOffset;
//             u32 mNumLabeledWalls;
//             u32 mLabeledWallOffset;
//             u32 mNumCommonGimmicks;
//             u32 mCommonGimmickOffset;
//             u32 mNumGimmicks;
//             u32 mGimmickOffset;
//             u32 mNumPaths;
//             u32 mPathOffset;
//             u32 mNumZones;
//             u32 mZoneOffset;
//             u32 mNumCourseInfo;
//             u32 mCourseInfoOffset;
//             u32 mCommonGimmickNameOffset;
//             u32 mColbinTypeOffset;
//             u32 mLabeledWallLabels;
//         };

//         typedef Colbin::Entry Wall;

//         struct LabeledWall : public Colbin::Entry {
//             u32 mLabelIndex;
//         };

//         struct MapdataParams {
//             int mIntParams[3];
//             f32 mFloatParams[3];
//             string64 mStringParams[3];
//         };

//         struct Gimmick {
//             char mName[0x30];
//             u8 m_30[0x10];
//             nw4r::math::VEC3 mPosition;
//             MapdataParams mParams;
//         };
        
//         struct CommonGimmickParams {
//             int mShortIntParams[2];
//             f32 mShortFloatParams[2];
//             char mShortStringParam[8];
//             int mIntParams[5];
//             float mFloatParams[5];
//             string64 mStringParams[5];
//         };

//         struct CommonGimmick {
//             u32 mNameIndex;
//             nw4r::math::VEC3 mPosition;
//             CommonGimmickParams mParams;
//         };


//         // variable length structure
//         struct Path {
//             string32 mName;
//             string32 mType;
//             MapdataParams mParams;
//             u32 mNumPoints;
//             // nw4r::math::VEC2 mPoints[mNumPoints];
//         };

//         struct Zone {
//             string32 mName;
//             string32 m_20;
//             MapdataParams mParams;
//             nw4r::math::VEC2 mBoundsMin;
//             nw4r::math::VEC2 mBoundsMax;  
//         };

//         struct RaceCourseInfo {
//             string32 mName;
//             string32 m_20;
//             MapdataParams mParams;
//             nw4r::math::VEC3 mPosition;
//         };

//     };

//     static Mapdata::Mapbin::File* Parse(const char* mapbinPath, bool isMission);

//     struct StageInfo {

//     };

// public:
//     STRUCT_FILL(0x1C);
//     int mStageCount;
//     StageInfo* mStageInfo;

//     // size unk
// };


#endif
