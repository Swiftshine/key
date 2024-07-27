#include <gfl/File.h>
#include <gfl/mem/Mem.h>

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

void gfl::File::fn_8064229C() { }
void gfl::File::fn_806422CC() { }
void gfl::File::fn_80642304() { }
void gfl::File::fn_8064231C() { }

gfl::File::~File() {

}
