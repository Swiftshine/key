#ifndef FLUFF_NANDMNG_H
#define FLUFF_NANDMNG_H

#include "types.h"
#include <string>

// unofficial name

/// @note Size: `0x248`
class FlfNandMng {
public:
    FlfNandMng();
    ~FlfNandMng();

    /* Class Methods */

    void fn_80229470();
    void SetFlags(uint flag, bool set);
    void fn_80229170(const char* pFilename, size_t filesize);
    void fn_802291E4(const char* pFilename);
    void fn_8022924C(size_t, int);
    DECL_WEAK int GetUnk8() const;
    void fn_802292B8(const char* pFilename, void* pData, size_t dataSize);
    void fn_80229340(const char* pFilename, void* pData, size_t dataSize);
    
    /* Static Methods */

    static size_t GetNumChunks(size_t size);

    /* Class Members */

    /* 0x000 */ int m_0;
    /* 0x004 */ int mState;
    /* 0x008 */ int m_8;
    /* 0x00C */ int m_C;
    /* 0x010 */ int m_10;
    /* 0x014 */ void* m_14;
    /* 0x018 */ int m_18;
    /* 0x01C */ void* mData1;
    /* 0x020 */ size_t mData1Size;
    /* 0x024 */ void* mData2;
    /* 0x028 */ size_t mData2Size;;
    /* 0x02C */ char mFilename[0x200];
    /* 0x22C */ int m_22C;
    /* 0x230 */ int m_230;
    /* 0x234 */ int m_234;
    /* 0x238 */ std::string m_238;
    /* 0x244 */ u8 mFlags;
};

#endif
