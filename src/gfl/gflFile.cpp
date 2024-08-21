#include "gflFile.h"
#include "gflMemoryUtil.h"
#include "gflFileSystemWii.h"

using namespace gfl;

const char gfl::File::EmptyFilename[] = {0, 0, 0, 0};

bool gfl::File::Open(const char* filename) {
    File* file = FileSystemWii::Instance->Open(filename, 1);

    if (file) {
        file->Close();
        return true;
    }
    
    return false;
}

void gfl::File::Close() {
    fs->Close(this);
    fs = NULL;
}

void gfl::File::Reset() {
    fs = NULL;
    filename = EmptyFilename;
    *(u32*)((u8*)this + 0x20C) = 0;
}

void gfl::File::Read(void* addr, u32 len, u32 fileOffs) {
    fs->Read(this, addr, len, fileOffs);
}

void gfl::File::ReadAsync(void* addr, u32 len, u32 fileOffs, u32 callback) {
    fs->ReadAsync(this, addr, len, fileOffs, callback);
}

void gfl::File::vf14() { }
void gfl::File::vf18() { }
void gfl::File::vf1C() { }
void gfl::File::vf20() { }

gfl::File::~File() {

}
