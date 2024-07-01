#ifndef GFL_FILE_FILE_H
#define GFL_FILE_FILE_H

#include <types.h>
#include <gfl/string.h>
#include <gfl/file/filesystemwii.h>

namespace gfl {
class File {
public:
    File();
    bool Open(const char*);
    void Close();
    void Read(void* addr, u32 len, u32 filepos);
    void ReadAsync(void* addr, u32 len, u32 offs, u32 callback);
    void fn_8064229C();
    void fn_806422CC();
    void fn_80642304();
    void fn_8064231C();
    void Reset();
    ~File();
private:
    void*                       vtable;
    gfl::FileSystemWii*         fs;
    gfl::String::FixedString    filename;
    void*                       dvd_fileinfo;
    u8                          _214[0x34];
    u32                         entrynum;
};

}

// static_assert(sizeof(gfl::File) == 0x250, "gfl::File is the wrong size");
#endif