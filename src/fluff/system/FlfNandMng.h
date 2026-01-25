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

    static s32 sNandResult;
    static bool sNandCallbackCalled;

    static FlfNandMng* sInstance;
    static FlfNandMng* Instance() {
        return sInstance;
    }

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
    void Clear();

    void SetStateIfBusy(s32 result, int state);

    void SetFlags(uint flag, bool set) DONT_INLINE_CLASS;
    DECL_WEAK int GetUnk8() const;
    
    /* Helper Inlines */
    // s32 Delete() {
    //     s32 result = NANDDelete(mTempFilename.c_str());
    //     while (result == NAND_RESULT_BUSY) {
    //         result = NANDDelete(mTempFilename.c_str());
    //     }
    //     return result;
    // }

    inline const char* GetTempFilename() const {
        return mTempFilename.c_str();
    }
    /* Static Methods */
    static void HandleNandError(s32 result) DONT_INLINE_CLASS;
    static void NandError(s32 result) DONT_INLINE_CLASS;
    static size_t GetNumChunks(size_t size);
    static void NandCallback(s32 result, NANDCommandBlock* pBlock);
    
    /* Class Members */

    /* 0x000 */ int mState;
    /* 0x004 */ int mPhase;
    /* 0x008 */ int mResult;
    /* 0x00C */ u32 mCheckAnswer;
    /* 0x010 */ u32 mLength;
    /* 0x014 */ void* mData1;
    /* 0x018 */ size_t mData1Size;
    /* 0x01C */ void* mData2;
    /* 0x020 */ size_t mData2Size;
    /* 0x024 */ void* mData3;
    /* 0x028 */ size_t mData3Size;;
    /* 0x02C */ char mFilename[0x200];
    /* 0x22C */ size_t mFilesize;
    /* 0x230 */ u32 mNandBlockCount;
    /* 0x234 */ u32 mINodeCount;
    /* 0x238 */ std::string mTempFilename;
    /* 0x244 */ u8 mFlags;
};


class FlfNandInfo {
public:
    FlfNandInfo() DONT_INLINE_CLASS;
    ~FlfNandInfo();

    /* Class Methods */
    void Init(NANDFileInfo* pFileInfo, NANDCommandBlock* pCommandBlock, bool safe) DONT_INLINE_CLASS;
    void SetUserData(NANDFileInfo* pFileInfo, NANDCommandBlock* pCommandBlock, bool safe) DONT_INLINE_CLASS;
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
