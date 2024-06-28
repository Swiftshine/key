#include <gfl/file.h>

gfl::File::File() {

}

bool gfl::File::Open(const char* file) {

    return fs != NULL;
}

void gfl::File::Close() {
    fs = NULL;
}

void gfl::File::Reset() {
    fs = NULL;
    filename = "";
    dvd_fileinfo = NULL;
}

void gfl::File::Read(void* addr, u32 len, u32 filepos) {

}

void gfl::File::ReadAsync(void* addr, u32 len, u32 offs, u32 callback) {

}

void gfl::File::fn_8064229C() { }
void gfl::File::fn_806422CC() { }
void gfl::File::fn_80642304() { }
void gfl::File::fn_8064231C() { }

gfl::File::~File() {

}