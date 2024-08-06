#pragma endian big
using f32 = float;

struct Header {
    char magic[4]; // BGST
    u32 _4;
    u32 _8;
    u32 _C;
    u32 _10;
    u32 _14;
    u32 _18;
    u32 _1C;
    u8 _20;
    u8 _21;
    u8 _23;
    u8 _24;
    u32 _28;
    u32 offset1;
    u32 offset2;
    f32 yOffset;
    u8 rest[0xC];
};

struct Struct1 {
    u32 _0;
    u16 index;
    u16 pad;
    s16 val1;
    s16 val2;
    s16 val3;
    s16 val4;
};

Header header @ 0;