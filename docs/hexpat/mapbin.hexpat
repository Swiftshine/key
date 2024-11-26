#pragma endian big
using f32 = float;
struct Vec2f {
    f32 x;
    f32 y;
};

struct Vec3f {
    f32 x;
    f32 y;
    f32 z;
};

using int = s32;

struct string32 {
    char string[32];
};

struct string64 {
    char string[64];
};

struct string80 {
    char string[80];
};

struct Header {
        f32 m_0;
        Vec2f mBoundsMin;
        Vec2f mBoundsMax;
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
        u32 mLabeledWallLabelOffset;
    };

    struct Wall {
        Vec2f mStart;
        Vec2f mEnd;
        Vec2f m_10;
        u32 mEntryIndex;
        u32 mCollisionTypeIndex;
    };

    struct LabeledWall {
        Vec2f mStart;
        Vec2f mEnd;
        Vec2f m_10;
        u32 mEntryIndex;
        u32 mCollisionTypeIndex;
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
        Vec3f mPosition;
        MapdataParams mParams;
    };
    
    struct CommonGimmickParams {
        int mIntParams1[2];
        f32 mFloatParams1[2];
        char mStringParams1[8];
        int mIntParams2[5];
        float mFloatParams2[5];
        string64 mStringParams[5];
    };

    struct CommonGimmick {
        u32 mNameIndex;
        Vec3f mPosition;
        CommonGimmickParams mParams;
    };

    // variable length structure
    struct Path {
        string32 mName;
        string32 mType;
        MapdataParams mParams;
        u32 mNumPoints;
        Vec2f mPoints[mNumPoints];
    };

    struct Zone {
        string32 mName;
        string32 m_20;
        MapdataParams mParams;
        Vec2f mBoundsMin;
        Vec2f mBoundsMax;  
    };

    struct CourseInfo {
        string32 mName;
        string32 m_20;
        MapdataParams mParams;
        Vec3f mPosition;
    };
    
    
Header header @ 0;
Wall walls[header.mNumWalls] @ header.mWallOffset;
LabeledWall labeledWalls[header.mNumLabeledWalls] @ header.mLabeledWallOffset;
CommonGimmick commonGimmicks[header.mNumCommonGimmicks] @ header.mCommonGimmickOffset;
Gimmick gimmicks[header.mNumGimmicks] @ header.mGimmickOffset;
Path paths[header.mNumPaths] @ header.mPathOffset;
Zone zones[header.mNumZones] @ header.mZoneOffset;
CourseInfo courseInfos[header.mNumCourseInfo] @ header.mCourseInfoOffset;

struct ColbinFooter {
    u32 numCollisionTypes;
};


struct CommonGimmickHeader {
    u32 count;
    string32 strings[count];
};


struct DataSegLabelHeader {
    u32 count;
    string32 strings[count];
};



CommonGimmickHeader commonGimmickHeader @ header.mCommonGimmickNameOffset;
DataSegLabelHeader dataSegLabelHeader @ header.mColbinTypeOffset;