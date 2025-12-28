#include "gflFile.h"
#include "gflMemoryUtil.h"
#include "gflFileSystemWii.h"

using namespace gfl;

const char gfl::File::EmptyFilename[] = {0, 0, 0, 0};

bool gfl::File::Open(const char* filename) {
    File* file = FileSystemWii::Instance()->Open(filename, 1);

    if (file) {
        file->Close();
        return true;
    }
    
    return false;
}

void gfl::File::Close() {
    mFilesystem->Close(this);
    mFilesystem = nullptr;
}

void gfl::File::Reset() {
    mFilesystem = nullptr;
    mFilename = EmptyFilename;
    *(uint*)((u8*)this + 0x20C) = 0;
}

void gfl::File::Read(void* addr, uint len, uint fileOffs) {
    mFilesystem->Read(this, addr, len, fileOffs);
}

void gfl::File::ReadAsync(void* addr, size_t len, size_t fileOffs, u32 callback) {
    mFilesystem->ReadAsync(this, addr, len, fileOffs, callback);
}

void gfl::File::vf14() { }
void gfl::File::vf18() { }
int gfl::File::GetFileStatus() { }
void gfl::File::vf20() { }

gfl::File::~File() {

}
