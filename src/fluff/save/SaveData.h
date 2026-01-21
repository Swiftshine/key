#ifndef FLUFF_SAVEDATA_H
#define FLUFF_SAVEDATA_H

#include "language/Language.h"

/// @note Size: `0x3884`
class SaveSlot {
public:
    void fn_801FFDB8(uint id);

    STRUCT_FILL(0x3884);
};

/// @note Size: `0xA9D4`
class SaveData {
public:
    /* Static Variables */

    /* Class Methods */

    uint CalculateChecksum(int numBytes);
    void Init();
    bool IsValid(int numBytes);
    void InitSaveSlots();
    bool IsSizeValid(int size);
    bool IsChecksumValid();
    
    /* Class Members */

    /* 0x0000 */ uint mRegionCode;
    /* 0x0004 */ uint mVersion;
    /* 0x0008 */ uint mChecksum;
    /* 0x000C */ uint m_C;
    /* 0x0010 */ uint m_10;
    /* 0x001C */ SaveSlot mSaveSlots[3];
    /* 0xA9A0 */ uint m_A9A0;
    /* 0xA9A4 */ char mParameter[0x30]; // ?
};

#endif