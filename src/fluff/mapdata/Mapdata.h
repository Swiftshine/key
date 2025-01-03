#ifndef FLUFF_MAPDATA_H
#define FLUFF_MAPDATA_H

#include "types.h"


#include <nw4r/math.h>
#include "object/collision/Colbin.h"


class Mapdata {
public:
    class Mapbin {
    public:
        struct File {
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

        struct Header {
            f32 m_0;
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
            nw4r::math::VEC3 mPosition;
            MapdataParams mParams;
        };
        
        struct CommonGimmickParams {
            int mShortIntParams[2];
            f32 mShortFloatParams[2];
            char mShortStringParam[8];
            int mIntParams[5];
            float mFloatParams[5];
            string64 mStringParams[5];
        };

        struct CommonGimmick {
            u32 mNameIndex;
            nw4r::math::VEC3 mPosition;
            CommonGimmickParams mParams;
        };


        // variable length structure
        struct Path {
            string32 mName;
            string32 mType;
            MapdataParams mParams;
            u32 mNumPoints;
            // nw4r::math::VEC2 mPoints[mNumPoints];
        };

        struct Zone {
            string32 mName;
            string32 m_20;
            MapdataParams mParams;
            nw4r::math::VEC2 mBoundsMin;
            nw4r::math::VEC2 mBoundsMax;  
        };

        struct RaceCourseInfo {
            string32 mName;
            string32 m_20;
            MapdataParams mParams;
            nw4r::math::VEC3 mPosition;
        };

    };

    static Mapdata::Mapbin::File* Parse(const char* mapbinPath, bool isMission);

    struct StageInfo {

    };

public:
    STRUCT_FILL(0x1C);
    int mStageCount;
    StageInfo* mStageInfo;

    // size unk
};


#endif
