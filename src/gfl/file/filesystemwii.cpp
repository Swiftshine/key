#include <gfl/file/filesystemwii.h>
#include <revolution/DVD/dvd.h>
#include <revolution/OS/OS.h>

void gfl::file::FileSystemWii::MakeInstance() {
    gfl::file::FileSystemWii::Instance = new gfl::file::FileSystemWii;
}

void gfl::file::FileSystemWii::ClearInstance() {
    if (gfl::file::FileSystemWii::Instance) {
        delete gfl::file::FileSystemWii::Instance;
    }

    gfl::file::FileSystemWii::Instance = NULL;
}

gfl::file::File* gfl::file::FileSystemWii::GetFileByEntrynum(int entrynum) {
    return NULL;
}

gfl::file::FileSystemWii::FileSystemWii() {
    Init();
}


void gfl::file::FileSystemWii::StartBPEThread() { }

void gfl::file::FileSystemWii::CancelBPEThead() {
    OSThread* thread = OSGetCurrentThread();
    if (thread != &BPEThread) {
        OSCancelThread(&BPEThread);
        // gfl::mem::free(CurrentBPEThread)
        CurrentBPEThread = NULL;
    }
}


gfl::file::FileSystemWii::~FileSystemWii() {
    CancelBPEThead();
}

void gfl::file::FileSystemWii::Init() {
    DVDInit();
    StartBPEThread();
}
