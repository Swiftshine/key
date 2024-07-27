#pragma endian little

struct FileHeader {
    char magic[4];      // "GFAC" - GoodFeel ArChive?
    u32  version;       // 0x0300 in this game - version 3.0
    bool compressed;    // always true
    u8   pad1[3];
    u32  fileInfoOffset;
    u32  fileInfoSize;
    u32  compressionHeaderOffset;
    u32  filesize;      // includes compression header(?)
    u8   pad2[4];
};

struct FileEntry {
    u32 hash;
    u32 nameOffs;
    u32 decompressedFilesize;
    u32 compressedOffs;
};
        
struct Filename {
    char filename[];
};

struct FileInfo {
    u32 filecount;
    FileEntry entries[filecount];
    Filename filenames[filecount];
};

struct CompressionHeader {
    char magic[4];      // "GFCP" - GoodFeel ComPression?
    u32 _4;
    s32 compressionType;
    u32 decompressedSize;
    u32 compressedSize;
};

FileHeader fHeader @ 0;
    
FileInfo fInfo @ fHeader.fileInfoOffset;

CompressionHeader compressionHeader @ fHeader.compressionHeaderOffset;
