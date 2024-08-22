#include "gflFileSystemWii.h"

using namespace gfl;

void FileSystemWii::InitInstance() {
    sInstance = new FileSystemWii;
}

void FileSystemWii::DestroyInstance() {
    delete sInstance;
    sInstance = nullptr;
}

File* FileSystemWii::GetFileByEntrynum(int entrynum) {
    return nullptr;
}

FileSystemWii::FileSystemWii() {
    Init();
}

void FileSystemWii::StartBPEThread() { }

void FileSystemWii::CancelBPEThead() {
    OSThread* thread = OSGetCurrentThread();
    if (thread != &BPEThread) {
        OSCancelThread(&BPEThread);
        // gfl::mem::free(CurrentBPEThread)
        CurrentBPEThread = nullptr;
    }
}

uint FileSystemWii::fn_80642618(File* file) {
    return *reinterpret_cast<u32*>((u8*)file + 0x244);
}

FileSystemWii::~FileSystemWii() {
    CancelBPEThead();
}


void FileSystemWii::Init() {
    DVDInit();
    StartBPEThread();
}
