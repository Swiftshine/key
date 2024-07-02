#include <gfl/file.h>

const char gfl::file::File::EmptyFilename[] = {0, 0, 0, 0};

gfl::file::File::File() {

}

bool gfl::file::File::Open(const char* file) {

    return fs != NULL;
}

void gfl::file::File::Close() {
    fs = NULL;
}

void gfl::file::File::Reset() {
    fs = NULL;
    filename = EmptyFilename;
    dvd_fileinfo = NULL;
}

void gfl::file::File::Read(void* addr, u32 len, u32 filepos) {

}

void gfl::file::File::ReadAsync(void* addr, u32 len, u32 offs, u32 callback) {

}

void gfl::file::File::fn_8064229C() { }
void gfl::file::File::fn_806422CC() { }
void gfl::file::File::fn_80642304() { }
void gfl::file::File::fn_8064231C() { }

gfl::file::File::~File() {

}
