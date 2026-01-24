#ifndef FLUFF_NANDMNG_H
#define FLUFF_NANDMNG_H

#include "types.h"
#include <string>
#include <revolution/NAND.h>

// unofficial names

/// @note Size: `0x248`
class FlfNandMng {
public:
    /* Structures */

    ENUM_CLASS(Result,
        Reset       = 0,
        Ok          = 1,
        Invalid     = 2,
        NoExist     = 3,
        Corrupt     = 4
    );
    
    /* Static Variables */
    static FlfNandMng* sInstance;
    static FlfNandMng* Instance() {
        return sInstance;
    }
    static NANDCommandBlock sCommandBlock;
    static bool lbl_808E51D4;
    static s32 sNandResult;

    FlfNandMng();
    ~FlfNandMng();

    /* Class Methods */
    void fn_80229170(const char* pFilename, size_t filesize);
    void fn_802291E4(const char* pFilename);
    void fn_8022924C(size_t numChunks, int);
    void fn_802292B8(const char* pFilename, void* pData, size_t dataSize);
    void fn_80229340(const char* pFilename, void* pData, size_t dataSize);
    void fn_80229470();

    void fn_80229524();
    void fn_80229788();
    void fn_8022987C();
    void fn_80229978();

    void SetFlags(uint flag, bool set);
    DECL_WEAK int GetUnk8() const;
    
    /* Static Methods */
    static void HandleNandError(s32 result);
    static void NandError(s32 result);
    static size_t GetNumChunks(size_t size);
    static void NandCallback(s32 result, void* arg);
    
    /* Class Members */

    /* 0x000 */ int mState;
    /* 0x004 */ int m_4;
    /* 0x008 */ int mResult;
    /* 0x00C */ int m_C;
    /* 0x010 */ int m_10;
    /* 0x014 */ void* mData1;
    /* 0x018 */ size_t mData1Size;
    /* 0x01C */ void* mData2;
    /* 0x020 */ size_t mData2Size;
    /* 0x024 */ void* mData3;
    /* 0x028 */ size_t mData3Size;;
    /* 0x02C */ char mFilename[0x200];
    /* 0x22C */ size_t mFilesize;
    /* 0x230 */ size_t mNumChunks;
    /* 0x234 */ int m_234;
    /* 0x238 */ std::string m_238;
    /* 0x244 */ u8 mFlags;
};


class FlfNandInfo {
public:
    static FlfNandInfo sInstance;
    static inline FlfNandInfo& Instance() {
        return sInstance;
    }

    FlfNandInfo();
    ~FlfNandInfo();

    /* Class Methods */
    void Init(NANDFileInfo* pFileInfo, NANDCommandBlock* pCommandBlock, bool safe);
    void SetUserData(NANDFileInfo* pFileInfo, NANDCommandBlock* pCommandBlock);
    void ClearUserData() DONT_INLINE_CLASS;
    void Invalidate() DONT_INLINE_CLASS;
    void Update();
    void Reset() DONT_INLINE_CLASS;

    /* Class Members */
    
    bool mIsSafeMode;
    int mResult;
    NANDFileInfo* mFileInfo;
    NANDCommandBlock* mCommandBlock;
};

#endif
