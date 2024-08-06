#pragma endian big


struct Header {
    char magic[4]; // FDGT
    u32 ffltOffset;
    u32 _8;
};

struct FFLT {
    char magic[4]; // FFLT
    u32 _4;
    char archiveName[0x10];
};


//struct Entry {
//    char name[0x10];
//    u32 _10;
//    u32 _14;
//    u32 _18;
//};

Header header @ 0;
FFLT fflt @ header.ffltOffset;