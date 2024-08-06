#pragma endian big

using f32 = float;
struct Vec2f { f32 x; f32 y; };
struct Vec3f { f32 x; f32 y; f32 z;};

struct string64 { char string[64]; };

struct ColType {
    char string[0x20];
};

struct string32 { char string[32]; };

struct GimmickParameters {
    s32 ints[3]; 
    float floats[3];
    string64 strings[3];
};

struct Header {
    f32 _0;
    Vec2f boundsStart;
    Vec2f boundsEnd;
    u32 wallCount;
    u32 wallOffset;
    u32 dataSegLabelCount;
    u32 dataSegLabelOffset;
    u32 commonGimmickCount;
    u32 commonGimmickOffset;
    u32 gimmickCount;
    u32 gimmicksOffset;
    u32 pathCount;
    u32 pathOffset;
    u32 zoneCount;
    u32 zoneOffset;
    u32 courseInfoCount;
    u32 courseInfoOffset;
    // GenGmk -> GenericGimmick
    u32 commonGimmickHeaderOffset;
    u32 colbinFooterOffset;
    u32 dataSegLabelHeaderOffset;
};

struct CommonGimmick {
    u32 nameIndex;
    Vec3f position;
    s32 ints1[3];
    float floats1[3];
    s32 ints2[4];
    float floats2[3];
    float floats3[3];
    string32 string1;
    u8 rest[0x120];
};

struct ColbinEntry {
    Vec2f point1;
    Vec2f point2;
    Vec2f _10;
    u32 index;
    u32 collisionTypeIndex;
};

struct DataSegLabel {
    ColbinEntry colbin;
    u32 nameIndex;
};

struct Path { // variable length.
    char name[0x20];
    char type[0x20];
    GimmickParameters params;
    u32 numPoints;
    Vec2f points[numPoints];
};

struct CourseInfo {
    char name[0x20];
    char _20[0x20];
    GimmickParameters params;
    Vec3f position;
};


struct GimmickEntry {
    char name[0x30];
    u8 _30[0x10];
    Vec3f position;  
    GimmickParameters param;
    /* padding if applicable*/
};


struct Zone {
    char name[0x20];
    char _20[0x20];
    GimmickParameters params;
    // a box?
    Vec2f boundsStart;
    Vec2f boundsEnd;
    
};
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
Header header @ 0x00;

ColbinEntry walls[header.wallCount] @ header.wallOffset;
DataSegLabel dataSegLabels[header.dataSegLabelCount] @ header.dataSegLabelOffset;
CommonGimmick commonGimmicks[header.commonGimmickCount] @ header.commonGimmickOffset;

Path paths[header.pathCount] @ header.pathOffset;
GimmickEntry gimmicks[header.gimmickCount] @ header.gimmicksOffset;
ColbinFooter footer @ header.colbinFooterOffset;
ColType collisionTypes[footer.numCollisionTypes] @ header.colbinFooterOffset + 4;
Zone zones[header.zoneCount] @ header.zoneOffset;

CommonGimmickHeader commonGimmickHeader @ header.commonGimmickHeaderOffset;
DataSegLabelHeader dataSegLabelHeader @ header.dataSegLabelHeaderOffset;

CourseInfo courseInfo[header.courseInfoCount] @ header.courseInfoOffset;