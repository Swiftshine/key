#pragma endian big

struct Header {
    char magic[4]; // MNCH
    u32 entryOffset;
    u32 _8;
    u32 entryCount;
    u32 _10;
    u32 _14;
};

struct Entry {
    char magic[4]; // MNCN
    u32 entrySize;
    char name[0x20];
    u8 rest[entrySize - 0x28];
};

Header header @ 0;
Entry entries[header.entryCount] @ header.entryOffset;