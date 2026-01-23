#include "save/SaveData.h"

#define SAVEDATA_SIZE       0xA9C0
#define SAVEDATA_VERSION    0x15
#define CRC_POLYNOMIAL      0xEDB88320

struct SaveDataInfo {
    inline SaveDataInfo();
    size_t mSaveDataSize;
};

static SaveDataInfo sSaveDataInfo;

// none of the below fields are ever used
static int lbl_808E5AEC;
static int lbl_808E5AF0;
static int lbl_808E5AF4;

SaveDataInfo::SaveDataInfo()
    : mSaveDataSize(SAVEDATA_SIZE)
{
    lbl_808E5AEC = 43;
    lbl_808E5AF0 = 61;
    lbl_808E5AF4 = 1;
}

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
    mHeader.mRegionCode = Language::GetCurrentRegionCode();
    mHeader.mChecksum = 0;
    mHeader.mChecksum = CalculateChecksum(SAVEDATA_SIZE - 0xC);
}

#pragma push
#pragma global_optimizer off

BOOL SaveData::IsValid(int numBytes) {
    if (!IsSizeValid(numBytes)) {
        return FALSE;
    }

    bool valid = mHeader.mRegionCode == Language::GetCurrentRegionCode();
    if (!valid) {
        return FALSE;
    }
    
    if (!IsChecksumValid()) {
        return FALSE;
    }
    
    if (mHeader.mVersion != SAVEDATA_VERSION) {
        return FALSE;
    }

    return TRUE;
}

#pragma pop

void SaveData::InitSaveSlots() {
    for (uint i = 0; i < 3; i++) {
        mSaveSlots[i].fn_801FFDB8(i);
    }

    mHeader.mChecksum = 0;
    mHeader.mChecksum = CalculateChecksum(SAVEDATA_SIZE - 0xC);
}

bool SaveData::IsSizeValid(int size) {
    return size == sSaveDataInfo.mSaveDataSize;
}

bool SaveData::IsChecksumValid() {
    uint oldChecksum = mHeader.mChecksum;
    mHeader.mChecksum = 0;
    uint newChecksum = CalculateChecksum(SAVEDATA_SIZE - 0xC);
    mHeader.mChecksum = oldChecksum;
    return oldChecksum == newChecksum;
}
