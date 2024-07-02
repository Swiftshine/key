#include <gfl/file/filesystemwii.h>
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


gfl::FileSystemWii::~FileSystemWii() {
    CancelBPEThead();
}

void gfl::FileSystemWii::Init() {
    DVDInit();
    StartBPEThread();
}
