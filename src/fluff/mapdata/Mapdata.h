#ifndef FLUFF_MAPDATA_H
#define FLUFF_MAPDATA_H

#include "types.h"
#include "gfl/gflVec2.h"
#include "gfl/gflVec3.h"
#include "object/collision/Colbin.h"


class Mapdata {
public:
    class Mapbin {
    public:
        struct Header {
            f32 m_0;
            gfl::Vec2 mBoundsMin;
            gfl::Vec2 mBoundsMax;
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

        typedef Colbin::Entry Wall;

        struct LabeledWall : public Colbin::Entry {
            u32 mLabelIndex;
        };

        struct MapdataParams {
            int mIntParams[3];
            f32 mFloatParams[3];
            string64 mStringParams[3];
        };

        struct Gimmick {
            char mName[0x30];
            u8 m_30[0x10];
            gfl::Vec3 mPosition;
            MapdataParams mParams;
        };
        
        struct CommonGimmickParams {
            int mIntParams1[3];
            f32 mFloatParams1[3];
            int mIntParams2[4];
            float mFloatParams2[3];
            float mFloatParams3[3];
            string32 mStringParam1;
            u8 mTheRest[0x120];
        };

        struct CommonGimmick {
            u32 mNameIndex;
            gfl::Vec3 mPosition;
            CommonGimmickParams mParams;
        };

        // variable length structure
        struct Path {
            string32 mName;
            string32 mType;
            MapdataParams mParams;
            u32 mNumPoints;
            // gfl::Vec2 mPoints[mNumPoints];
        };

        struct Zone {
            string32 mName;
            string32 m_20;
            MapdataParams mParams;
            gfl::Vec2 mBoundsMin;
            gfl::Vec2 mBoundsMax;  
        };

        struct RaceCourseInfo {
            string32 mName;
            string32 m_20;
            MapdataParams mParams;
            gfl::Vec3 mPosition;
        };
    };

    static Mapdata* Parse(const char* mapbinPath, bool isMission);


public:
    
};


#endif
