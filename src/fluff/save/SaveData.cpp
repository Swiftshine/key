#include "save/SaveData.h"

#define SAVEDATA_SIZE       0xA9C0
#define SAVEDATA_VERSION    0x15
#define CRC_POLYNOMIAL      0xEDB88320

struct SaveDataInfo {
    SaveDataInfo()
        : mSaveDataSize(SAVEDATA_SIZE)
        , m_4(43)
        , m_8(61)
        , m_C(1)
    { }

    int mSaveDataSize;
    int m_4;
    int m_8;
    int m_C;
};

static SaveDataInfo sSaveDataInfo;

uint SaveData::CalculateChecksum(int numBytes) {
    uint checksum = 0xFFFFFFFF;
    u8* data = reinterpret_cast<u8*>(this);

    for (int i = 0; i < numBytes; i++) {
        checksum ^= data[i];

        for (int bit = 0; bit < 8; bit++) {
            if (checksum & 1) {
                checksum = (checksum >> 1) ^ CRC_POLYNOMIAL;
            } else {
                checksum >>= 1;
            }
        }
    }

    return checksum ^ 0xFFFFFFFF;
}

void SaveData::Init() {
    mRegionCode = Language::GetCurrentRegionCode();
    mChecksum = 0;
    mChecksum = CalculateChecksum(SAVEDATA_SIZE - 0xC);
}

#pragma push
#pragma global_optimizer off

bool SaveData::IsValid(int numBytes) {
    if (!IsSizeValid(numBytes)) {
        return false;
    }

    bool valid = mRegionCode == Language::GetCurrentRegionCode();
    if (!valid) {
        return false;
    }
    
    if (!IsChecksumValid()) {
        return false;
    }
    
    if (mVersion != SAVEDATA_VERSION) {
        return false;
    }

    return true;
}

#pragma pop

void SaveData::InitSaveSlots() {
    for (uint i = 0; i < 3; i++) {
        mSaveSlots[i].fn_801FFDB8(i);
    }

    mChecksum = 0;
    mChecksum = CalculateChecksum(SAVEDATA_SIZE - 0xC);
}

// https://decomp.me/scratch/qGYnj
bool SaveData::IsSizeValid(int size) {
    return sSaveDataInfo.mSaveDataSize == size;
}

bool SaveData::IsChecksumValid() {
    uint oldChecksum = mChecksum;
    mChecksum = 0;
    uint newChecksum = CalculateChecksum(SAVEDATA_SIZE - 0xC);
    mChecksum = oldChecksum;
    return oldChecksum == newChecksum;
}

// sinit scratch: https://decomp.me/scratch/JLgpH