#include <gfl/file/filesystemwii.h>

gfl::FileSystemWii::FileSystemWii() {
    Init();
}

gfl::FileSystemWii::~FileSystemWii() {
    CancelBPEDecompressionThead();
}
