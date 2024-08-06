#pragma endian big

using f32 = float;

struct Vec2f { f32 x; f32 y; };
struct Vec3f { f32 x; f32 y; f32 z;};

struct Header {
    char magic[4]; // GFES
    u32 _4;
    u32 _8;
    u32 _C;
    u32 footerOffset;
    u32 numEntries;
};
struct EnemyEntry {
    char name[0x20];
    char behavior[0x20];
    char pathName[0x20];
    char beadType[0x10];
    char beadColor[0x10];
    char direction[0x10];
    char orientation[0x10];
    Vec3f position1;
    Vec3f position2;
    Vec3f position3;
    Vec3f _C4;
    u32 _D0;
    u32 _D4;
    s32 _D8;
    Vec3f _DC;
    u32 _E8;
    u32 _EC;
    u32 _F0;
    u32 _F4;
    u32 _F8;
    u32 _FC;
    u32 _100;
    u32 _104;
    s32 _108;
    u32 _10C;
    u32 _110;
    u32 _114;
    u32 _118;
    u32 _11C;
    u32 _120;
    u32 _124;
    u32 _128;
    u32 _12C;
    u32 _130;
    u32 _134;
    u32 _138;
    u32 _13C;
    u32 _140;
    u32 _144;
    u32 _148;
    u32 _14C;
    u32 _150;
    u32 _154;
    u32 _158;
    u32 _15C;
    u32 _160;
    u32 _164;
    u32 _168;
    u32 _16C;
    u32 _170;
};

struct Footer {
    u32 numFooterEntries;  
};

struct FooterEntry {
    u32 _0;
    u32 _4;
    Vec2f _8;
    Vec2f _10;
};
Header header @ 0;
EnemyEntry entries[header.numEntries] @ 0x18;
Footer footer @ header.footerOffset;
FooterEntry footerEntries[footer.numFooterEntries] @ header.footerOffset + 4;