#ifndef FLUFF_SAVEDATA_H
#define FLUFF_SAVEDATA_H

#include "language/Language.h"

/// @note Size: `0x3884`
class SaveSlot {
public:
    void fn_801FFDB8(uint id);

    STRUCT_FILL(0x3884);
};

struct SaveData_Header {
    uint mRegionCode;
    uint mVersion;
    uint mChecksum;
    uint m_C;
    uint m_10;
};

/// @note Size: `0xA9D4`
class SaveData {
public:
    /* Static Variables */

    /* Class Methods */

    uint CalculateChecksum(int numBytes);
    void Init();
    BOOL IsValid(int numBytes);
    void InitSaveSlots();
    bool IsSizeValid(int size);
    bool IsChecksumValid();
    
    /* Class Members */

    /* 0x0000 */ SaveData_Header mHeader;
    /* 0x0014 */ SaveSlot mSaveSlots[3];
    /* 0xA9A0 */ uint m_A9A0;
    /* 0xA9A4 */ char mParameter[0x30]; // ?
};

#endif
