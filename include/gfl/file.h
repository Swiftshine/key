#ifndef GFL_FILE_H
#define GFL_FILE_H

#include <types.h>

namespace gfl {

class File {
public:
    File();
    ~File();
private:
    void*   filesystem;
    char    filename[0x200];
    u32     name_length;
    u32     _20C;
    void*   dvd_fileinfo;
    u8      _214[0x34];
    u32     entrynum;
};

static_assert(sizeof(gfl::File) == 0x250, "gfl::File is the wrong size");

}
#endif