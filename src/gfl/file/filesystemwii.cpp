#include <gfl/file/filesystemwii.h>
#include <revolution/DVD/dvd.h>

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
