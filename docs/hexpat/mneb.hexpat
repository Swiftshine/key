#pragma endian big

#include <std/string.pat>

struct Header {
    char magic[4]; // MNCH
    u32 entryOffset;
    u32 _8;
    u32 entryCount;
    u32 _10;
    u32 _14;
};

struct S16Quad {
    s16 first;
    s16 second;
    s16 third;
    s16 fourth;
};

struct SomeData1 {
    u32 count;
    S16Quad quads[count];    
};

struct SomeData2 {
    u32 count;
    float values[count];
};

struct SomeData3 {
    u32 endOffs;
    u8 data[endOffs - $];
};

struct SomeData4 {
    u32 count;
    u32 values[count];
};

struct Subheader {
    u32 blockSize;
    u32 _4;
    s32 _8;
    u32 offs1;
    u32 offs2;
    u32 offs3;
    float _1C[8];
};

struct Entry {
    char magic[4]; // MNCN
    u32 entrySize;
    char name[0x20];
    u8 buf1[0x68];
    Subheader subheader;
    SomeData1 sd1;
    SomeData2 sd2;
    SomeData3 sd3;
    SomeData4 sd4;
};

Header header @ 0;
Entry entries[header.entryCount] @ header.entryOffset;
