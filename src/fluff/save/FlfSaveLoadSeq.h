#ifndef FLUFF_SAVELOADSEQ_H
#define FLUFF_SAVELOADSEQ_H

#include "gfl/gflTask.h"
#include "misc/ScopedPointers.h"
#include "save/SaveInfo.h"
#include "system/FlfBannerMng.h"

#define SECTOR_SIZE 0x4000  // 16 KiB
#define BLOCK_SIZE  0x20000 // 128 KiB

u32 SAVEDATA_VERSION = 0x15;
u32 DEFAULT_CHECKSUM = 0;

struct FlfSaveLoadSeq_Substruct {
    FlfSaveLoadSeq_Substruct(FlfNandMng* pNandMng);
    ~FlfSaveLoadSeq_Substruct();

    void fn_80634EE8();
    void fn_80634F08(size_t*, int*);
    void fn_80634F3C();
    void fn_80634F5C();
    int GetUnk2C();

    STRUCT_FILL(0x34);
};

/// @note Size: `0x2E4`
class FlfSaveLoadSeq {
public:
    /* Structures */
    
    ENUM_CLASS(Operation,
        None = 0,
        Load = 1,
        Save = 2,
        Op_3 = 3,
        Op_4 = 4,
    );

    /* Static Variables */

    static FlfSaveLoadSeq* sInstance;

    FlfSaveLoadSeq();
    ~FlfSaveLoadSeq();
    
    /* Class Methods */

    void Clear();
    void CopyLoadSaveInfo(const LoadSaveInfo& rSaveInfo);
    size_t GetNumSDBytes();
    size_t GetNumNANDBytes();
    void CopySaveSaveInfo(const SaveSaveInfo& rSaveInfo);
    void Update() const;
    void Load();
    void Save();
    void fn_8022D400();
    void fn_8022D414();
    void fn_8022D430(int) DONT_INLINE_CLASS;
    void fn_8022D440(int arg1);
    bool IsSaveDataValid(SaveData* pSaveData, size_t numBytes);
    void InitSaveData();
    bool IsSaveDataLoaded() const;
    
    DECL_WEAK int GetUnk18() const;

    /* Static Methods */

    static FlfSaveLoadSeq* GetInstance();
    static FlfSaveLoadSeq* Build();
    static void DestroyInstance();

    /* Class Members */

    /* 0x000 */ int mOperation; // nand? SD storage?
    /* 0x004 */ int mLoadState;
    /* 0x008 */ int mSaveState;
    /* 0x00C */ bool m_C;
    /* 0x010 */ int m_10;
    /* 0x014 */ int m_14;
    /* 0x018 */ int m_18;
    /* 0x01C */ int m_1C;
    /* 0x020 */ bool m_20;
    /* 0x021 */ bool m_21;
    /* 0x022 */ bool mSaveDataLoaded;
    /* 0x024 */ size_t mNumSDChunks;
    /* 0x028 */ int m_28;
    /* 0x02C */ size_t mNumNANDChunks;
    /* 0x030 */ int m_30;
    /* 0x034 */ int mWaitTime1;
    /* 0x038 */ int mWaitTime2; // in frames?
    /* 0x03C */ gfl::FreedPointer<void> mBuffer;
    /* 0x040 */ gfl::Task mTask;
    /* 0x058 */ LoadSaveInfo mLoadSaveInfo;
    /* 0x06C */ SaveSaveInfo mSaveSaveInfo;
    /* 0x074 */ gfl::Pointer<FlfSaveLoadSeq_Substruct> m_74;
    /* 0x078 */ FlfNandMng mNandManager;
    /* 0x2C0 */ FlfBannerMng mBannerManager;
};

#endif
