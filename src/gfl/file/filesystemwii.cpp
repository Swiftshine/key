#include <gfl/file.h>
#include <revolution/DVD/dvd.h>
#include <revolution/OS/OS.h>

void gfl::FileSystemWii::MakeInstance() {
    gfl::FileSystemWii::Instance = new gfl::FileSystemWii;
}

void gfl::FileSystemWii::ClearInstance() {
    if (gfl::FileSystemWii::Instance) {
        delete gfl::FileSystemWii::Instance;
    }

    gfl::FileSystemWii::Instance = NULL;
}

gfl::File* gfl::FileSystemWii::GetFileByEntrynum(int entrynum) {
    return NULL;
}

gfl::FileSystemWii::FileSystemWii() {
    Init();
}


void gfl::FileSystemWii::StartBPEThread() { }

void gfl::FileSystemWii::CancelBPEThead() {
    OSThread* thread = OSGetCurrentThread();
    if (thread != &BPEThread) {
        OSCancelThread(&BPEThread);
        // gfl::mem::free(CurrentBPEThread)
        CurrentBPEThread = NULL;
    }
}

u32 gfl::FileSystemWii::fn_80642618(File* file) {
    return *reinterpret_cast<u32*>((u8*)file + 0x244);
}

gfl::FileSystemWii::~FileSystemWii() {
    CancelBPEThead();
}

void gfl::FileSystemWii::Init() {
    DVDInit();
    StartBPEThread();
}
