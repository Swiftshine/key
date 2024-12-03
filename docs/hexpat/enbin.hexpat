#pragma endian big

using f32 = float;

struct Vec2f { f32 x; f32 y; };
struct Vec3f { f32 x; f32 y; f32 z;};

struct Header {
    char magic[4]; // GFES
    u32 _4;
    u32 _8;
    u32 enemyHeaderOffset;
    u32 lineHeaderOffset;
};

struct Line {
    u32 numPoints;
    Vec2f points[numPoints];
};

struct EnemyParams {
    float mFloatParams[3];
    s32 mIntParams[3];
    
};

struct Enemy {
    char name[0x20];
    char behavior[0x20];
    char pathName[0x20];
    char beadType[0x10];
    char beadColor[0x10];
    char direction[0x8];
    char _88[0x8];
    char orientation[0x10];
    Vec3f position1;
    Vec3f position2;
    Vec3f position3;
    EnemyParams mParams[7];
    u32 _16C;
    u32 _170;
};

struct EnemyHeader {
    u32 numEnemies;
    Enemy enemies[numEnemies];
};

struct Footer {
    u32 numFooterEntries;  
};


struct LineEntry {
    u32 lineOffset;
    Line line @ lineOffset;
};

struct LineHeader {
    u32 numLineEntries;
    LineEntry entries[numLineEntries];
};

struct FooterEntry {
    u32 _0;
    u32 _4;
    Vec2f _8;
    Vec2f _10;
};

Header header @ 0;
EnemyHeader enHeader @ header.enemyHeaderOffset;
// LineHeader lHeader @ header.lineHeaderOffset;