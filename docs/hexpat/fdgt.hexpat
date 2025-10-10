#pragma endian big


struct Header {
    char magic[4]; // FDGT
    u32 ffltOffset;
    u32 _8;
};


struct FFLTEntry {
    u32 firstNum;
    u32 secondNum;
};


struct FFLT {
    char magic[4]; // FFLT
    u32 blockSize;
    char archiveName[0x10];
    u32 entryCount;
    u32 _1C;
    u32 _20; 
    FFLTEntry entries1[entryCount];
    FFLTEntry entries2[entryCount];
};

//struct Entry {
//    char name[0x10];
//    u32 _10;
//    u32 _14;
//    u32 _18;
//};

Header header @ 0;
FFLT fflt @ header.ffltOffset;