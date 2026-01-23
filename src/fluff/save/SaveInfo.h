#ifndef FLUFF_SAVEINFO_H
#define FLUFF_SAVEINFO_H

#include <string>
#include "save/SaveData.h"

struct SaveSaveInfo {
    /* 0x00 */ SaveData* mSaveData;
    /* 0x04 */ size_t mSaveDataSize;
};

struct LoadSaveInfo {
    LoadSaveInfo()
        : mSaveFileName()
    { }

    /* 0x00 */ std::string mSaveFileName;
    /* 0x0C */ SaveData* mSaveData;
    /* 0x10 */ size_t mSaveDataSize;
};

#endif
