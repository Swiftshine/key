#include <revolution/os.h>
#include "system/FlfNandMng.h"
#include "gfl/gflHomeMenu.h"
#include "gfl/gflMemory.h"
#include "gfl/gflMemoryUtil.h"
#include "gfl/gflMisc.h"
#include "game/Game.h"

FlfNandInfo NandInfo = FlfNandInfo();
NANDFileInfo NandFileInfo;
NANDCommandBlock CommandBlock;

s32 FlfNandMng::sNandResult;
bool FlfNandMng::sNandCallbackCalled;
FlfNandMng* FlfNandMng::sInstance;

// some NAND function
extern "C" s32 fn_806AD4A0(NANDFileInfo*);

DECL_WEAK DONT_INLINE void CutFunction() { }
DECL_WEAK DONT_INLINE void CutFunction2(int) { }

void FlfNandMng::NandError(s32 result) {    
    if (result != NAND_RESULT_OK) {
        CutFunction(); // probably some logging
        GFL_HALT();
    }
}

FlfNandInfo::FlfNandInfo()
    : mIsSafeMode(false)
    , mResult(FlfNandMng::Result::Reset)
    , mFileInfo(nullptr)
    , mCommandBlock(nullptr)
{
    memset(&CommandBlock, 0, sizeof(NANDCommandBlock));
}

void FlfNandInfo::Init(NANDFileInfo* pFileInfo, NANDCommandBlock* pCommandBlock, bool safe) {
    Update();
    NANDSetUserData(pCommandBlock, this);
    mFileInfo = pFileInfo;
    mCommandBlock = pCommandBlock;
    mIsSafeMode = safe;
    mResult = FlfNandMng::Result::Ok;
}

void FlfNandInfo::SetUserData(NANDFileInfo* pFileInfo, NANDCommandBlock* pCommandBlock, bool arg3) {
    NANDSetUserData(pCommandBlock, this);
    mResult = FlfNandMng::Result::NoExist;
}

void FlfNandInfo::ClearUserData() {
    NANDSetUserData(mCommandBlock, nullptr);
    mResult = FlfNandMng::Result::Invalid;
}

FlfNandInfo::~FlfNandInfo() {
    Update();
}

void FlfNandInfo::Invalidate() {
    mResult = FlfNandMng::Result::Invalid;
}

void FlfNandInfo::Update() {
    while (mCommandBlock != nullptr && NANDGetUserData(mCommandBlock) != nullptr) {
        OSSleepTicks(OS_USEC_TO_TICKS(1000LL));
    }

    if (mResult != FlfNandMng::Result::Invalid) {
        return;
    }

    if (mIsSafeMode) {
        s32 result = NANDSimpleSafeClose(mFileInfo);
        while (result == NAND_RESULT_BUSY) {
            result = NANDSimpleSafeClose(mFileInfo);
        }

        if (result != NAND_RESULT_OK) {
            FlfNandMng::HandleNandError(result);
        }
    } else {
        s32 result = NANDClose(mFileInfo);
        while (result == NAND_RESULT_BUSY) {
            result = NANDClose(mFileInfo);
        }

        if (result != NAND_RESULT_OK) {
            FlfNandMng::HandleNandError(result);
        }
    }

    Reset();
}

void FlfNandInfo::Reset() {
    mResult = FlfNandMng::Result::Reset;
    mIsSafeMode = false;
    mFileInfo = nullptr;
    if (mCommandBlock != nullptr) {
        NANDSetUserData(mCommandBlock, nullptr);
    }
    mCommandBlock = nullptr;
}

void FlfNandMng::NandCallback(s32 result, NANDCommandBlock* pBlock) {
    sNandCallbackCalled = true;
    sNandResult = result;
    FlfNandInfo* info = reinterpret_cast<FlfNandInfo*>(NANDGetUserData(pBlock));

    if (info == nullptr) {
        return;
    }

    NANDSetUserData(pBlock, nullptr);

    if (info->mResult == Result::Ok) {
        if (sNandResult == NAND_RESULT_OK) {
            info->Invalidate();
        } else {
            info->Reset();
        }
    } else if (info->mResult == Result::NoExist) {
        if (sNandResult == NAND_RESULT_OK) {
            info->Reset();
        } else {
            info->ClearUserData();
        }
    }
}

FlfNandMng::FlfNandMng()
    : mTempFilename()
{
    NandInfo.Update();
    sInstance = this;
    mResult = Result::Invalid;
    mState = 0;
    mPhase = 0;
    sNandResult = NAND_RESULT_OK;
    sNandCallbackCalled = false;
    mCheckAnswer = 0;
    mLength = 0;
    mData1Size = 0;
    mData1 = nullptr;
    mData3 = nullptr;
    mData3Size = 0;
    mData2Size = 0x4000;
    gfl::Heap* heap = gfl::Memory::TryGetHeapByID(gfl::HeapID::LIB1);
    mData2 = gfl::Alloc(heap, mData2Size, 0x20);
    memset(mFilename, 0, sizeof(mFilename));
    mFilesize = 0;
    mNandBlockCount = 0;
    mINodeCount = 0;
    mFlags = 0;
}

FlfNandMng::~FlfNandMng() {
    gfl::Free(mData2);
    mData2 = nullptr;

    if (mData1 != nullptr) {
        gfl::Free(mData1);
        mData1 = nullptr;
    }

    sInstance = nullptr;
}

void FlfNandMng::fn_80229170(const char* pFilename, size_t filesize) {
    NandInfo.Update();
    gfl::Strcpy(mFilename, sizeof(mFilename), pFilename);
    mFilesize = filesize;
    mPhase = 1;
    mState = 1;
    mResult = Result::Reset;
}

void FlfNandMng::fn_802291E4(const char* pFilename) {
    NandInfo.Update();
    gfl::Strcpy(mFilename, sizeof(mFilename), pFilename);
    mPhase = 2;
    mState = 7;
    mResult = Result::Reset;
}

void FlfNandMng::fn_8022924C(size_t numChunks, int arg2) {
    NandInfo.Update();
    mNandBlockCount = numChunks;
    mINodeCount = arg2;
    mPhase = 3;
    mState = 9;
    mResult = Result::Reset;
}

void FlfNandMng::fn_802292B8(const char* pFilename, void* pData, size_t dataSize) {
    NandInfo.Update();
    gfl::Strcpy(mFilename, sizeof(mFilename), pFilename);
    mData3 = pData;
    mData3Size = dataSize;
    mPhase = 4;
    mState = 11;
    mResult = Result::Reset;
}

void FlfNandMng::fn_80229340(const char* pFilename, void* pData, size_t dataSize) {
        NandInfo.Update();
    gfl::Strcpy(mFilename, sizeof(mFilename), pFilename);
    mData3 = pData;
    mData3Size = dataSize;
    mPhase = 5;
    mState = 11;
    mResult = Result::Reset;
}

size_t FlfNandMng::GetNumBlocks(size_t size) {
    return size + 0x3FFF >> 0xE;
}


void FlfNandMng::SetFlags(uint flag, bool set) {
    if (set) {
        mFlags |= 1 << flag;
    } else {
        mFlags &= ~(1 << flag);
    }

    Game::fn_8064740C(mFlags == 0);
    gfl::HomeMenu::GetInstance()->SetUnk4(mFlags & ~1);
}

void FlfNandMng::fn_80229470() {
    switch (mPhase) {
        case 1: {
            fn_80229524();
            break;
        }

        case 2: {
            fn_80229788();
            break;
        }

        case 3: {
            fn_8022987C();
            break;
        }

        case 4: 
        case 5: {
            fn_80229978();
            break;
        }
    }
}

void FlfNandMng::HandleNandError(s32 result) {
    CutFunction();

    switch (result) {
        case NAND_RESULT_OK:
        case NAND_RESULT_CORRUPT: {
            GFL_HALT();
            break;
        }

        case NAND_RESULT_AUTHENTICATION:
        case NAND_RESULT_ECC_CRIT:
        case NAND_RESULT_MAXBLOCKS:
        case NAND_RESULT_MAXFILES: {
            GFL_HALT();
            break;
        }

        default: {
            GFL_HALT();
            break;
        }
    }
}

void FlfNandMng::fn_80229524() {
    switch (mState) {
        case 1: {
            mState = 2;
            sNandCallbackCalled = false;
            NandInfo.Init(&NandFileInfo, &CommandBlock, false);

            s32 result = NANDOpenAsync(mFilename, &NandFileInfo, 1, NandCallback, &CommandBlock);

            if (result == NAND_RESULT_BUSY) {
                NandInfo.Reset();
            }

            SetStateIfBusy(result, 1);
            break;
        }

        case 2: {
            if (sNandCallbackCalled) {
                switch (sNandResult) {
                    case NAND_RESULT_OK: {
                        mState = 3;
                        break;
                    }

                    case NAND_RESULT_NOEXISTS: {
                        mResult = Result::NoExist;
                        Clear();
                        break;
                    }

                    default: {
                        HandleNandError(sNandResult);
                        break;
                    }
                }
            }
            break;
        }

        case 3: {
            mState = 4;
            sNandCallbackCalled = false;
            s32 result = NANDGetLengthAsync(&NandFileInfo, &mLength, NandCallback, &CommandBlock);
            SetStateIfBusy(result, 3);
            break;
        }

        case 4: {
            if (sNandCallbackCalled) {
                if (sNandResult == NAND_RESULT_OK) {
                    mState = 5;
                } else {
                    HandleNandError(sNandResult);
                }
            }
            break;
        }

        case 5: {
            mState = 6;
            sNandCallbackCalled = false;
            NandInfo.SetUserData(&NandFileInfo, &CommandBlock, false);
            s32 result = NANDCloseAsync(&NandFileInfo, NandCallback, &CommandBlock);

            if (result == NAND_RESULT_BUSY) {
                NandInfo.ClearUserData();
            }

            SetStateIfBusy(result, 5);
            break;
        }

        case 6: {
            if (sNandCallbackCalled) {
                switch (sNandResult) {
                    case NAND_RESULT_OK: {
                        if (mLength == mFilesize) {
                            mResult = Result::Ok;
                        } else {
                            mResult = Result::Invalid;
                        }
                        Clear();
                        break;
                    }

                    case NAND_RESULT_CORRUPT: {
                        mResult = Result::Corrupt;
                        Clear();
                        break;   
                    }

                    default: {
                        HandleNandError(sNandResult);
                        break;
                    }
                }
            }
            break;
        }
    }
}

void FlfNandMng::fn_80229788() {
    switch (mState) {
        case 7: {
            mState = 8;
            sNandCallbackCalled = false;
            s32 result = NANDDeleteAsync(mFilename, NandCallback, &CommandBlock);
            SetStateIfBusy(result, 7);
            break;
        }

        case 8: {
            if (sNandCallbackCalled) {
                switch (sNandResult) {
                    case NAND_RESULT_OK: {
                        mResult = Result::Ok;
                        Clear();
                        break;
                    }

                    case NAND_RESULT_CORRUPT: {
                        mResult = Result::Invalid;
                        Clear();
                        break;
                    }

                    case NAND_RESULT_NOEXISTS: {
                        mResult = Result::NoExist;
                        Clear();
                        break;
                    }

                    case NAND_RESULT_BUSY: {
                        mState = 7;
                        break;
                    }

                    default: {
                        HandleNandError(sNandResult);
                    }
                }
            }
            break;
        }
    }
}

void FlfNandMng::fn_8022987C() {
    switch (mState) {
        case 9: {
            mState = 10;
            sNandCallbackCalled = false;
            s32 result = NANDCheckAsync(mNandBlockCount, mINodeCount, &mCheckAnswer, NandCallback, &CommandBlock);
            SetStateIfBusy(result, 9);
            break;
        }

        case 10: {
            if (sNandCallbackCalled) {
                if (sNandResult == NAND_RESULT_OK) {
                    u32 ans = mCheckAnswer;
                    if (ans == 0) {
                        mResult = Result::Ok;
                    } else if ((ans & NAND_CHECK_TOO_MANY_USER_BLOCKS) != 0 || (ans & NAND_CHECK_TOO_MANY_APP_BLOCKS) != 0) {
                        mResult = Result::Invalid;
                    } else if ((ans & NAND_CHECK_TOO_MANY_USER_FILES) != 0 || (ans & NAND_CHECK_TOO_MANY_APP_FILES) != 0) {
                        mResult = Result::NoExist;
                    }

                    Clear();
                } else {
                    HandleNandError(sNandResult);
                }
            }
            break;
        }
    }
}

const char tmp[] = "/tmp/";

// https://decomp.me/scratch/6ncKJ
void FlfNandMng::fn_80229978() {
    switch (mState) {
        case 11: {
            mState = 12;
            sNandCallbackCalled = false;
            s32 result = NAND_RESULT_OK;

            if (mPhase == 4) {
                NandInfo.Init(&NandFileInfo, &CommandBlock, true);
                result = NANDPrivateSafeOpenAsync(mFilename, &NandFileInfo, 3, mData2, mData2Size, NandCallback, &CommandBlock);
            } else if (mPhase == 5) {
                NandInfo.Init(&NandFileInfo, &CommandBlock, false);
                result = NANDOpenAsync(mFilename, &NandFileInfo, 1, NandCallback, &CommandBlock);
            }

            if (result == NAND_RESULT_BUSY) {
                NandInfo.Reset();
            }

            SetStateIfBusy(result, 11);
            break;
        }

        case 12: {
            if (sNandCallbackCalled) {
                switch (sNandResult) {
                    case NAND_RESULT_OK: {
                        if (mPhase == 4) {
                            mState = 23;
                        } else if (mPhase == 5) {
                            mState = 25;
                        }

                        break;
                    }

                    case NAND_RESULT_BUSY: {
                        mState = 11;
                        break;
                    }

                    case NAND_RESULT_NOEXISTS: {
                        if (mPhase == 4) {
                            mState = 13;
                        } else if (mPhase == 5) {
                            mResult = Result::Corrupt;
                            Clear();
                        }  else {
                            GFL_HALT();
                        }
                        break;
                    }

                    case NAND_RESULT_CORRUPT: {
                        CutFunction2(sNandResult);
                        mResult = Result::NoExist;
                        Clear();
                        break;
                    }

                    case NAND_RESULT_ECC_CRIT:
                    case NAND_RESULT_AUTHENTICATION: {
                        if (mPhase == 4) {
                            s32 result = fn_806AD4A0(&NandFileInfo);
                            while (result == NAND_RESULT_BUSY) {
                                result = fn_806AD4A0(&NandFileInfo);
                            }

                            result = NANDDelete(mFilename);
                            while (result == NAND_RESULT_BUSY) {
                                result = NANDDelete(mFilename);
                            }
                            mState = 11;
                        } else {
                            HandleNandError(sNandResult);
                        }

                        break;
                    }

                    default: {
                        HandleNandError(sNandResult);
                        break;
                    }
                }
            }
            break;
        }

        case 13: {
            mState = 14;
            sNandCallbackCalled = false;
            mTempFilename = tmp;
            mTempFilename += mFilename;
            s32 result = NANDCreateAsync(mTempFilename.c_str(), 0x34, 0, &NandCallback, &CommandBlock);
            SetStateIfBusy(result, 13);
            break;
        }

        case 14: {
            if (sNandCallbackCalled) {
                switch (sNandResult) {
                    case NAND_RESULT_OK:
                    case NAND_RESULT_EXISTS: {
                        mState = 15;
                        break;
                    }
                    
                    case NAND_RESULT_CORRUPT: {
                        CutFunction2(sNandResult);
                        mResult = Result::NoExist;
                        Clear();
                        break;
                    }

                    default: {
                        HandleNandError(sNandResult);
                        break;
                    }
                }
            }
            break;
        }

        case 15: {
            mState = 16;
            sNandCallbackCalled = false;
            NandInfo.Init(&NandFileInfo, &CommandBlock, false);
            s32 result = NANDOpenAsync(mTempFilename.c_str(), &NandFileInfo, 3, NandCallback, &CommandBlock);
            if (result == NAND_RESULT_BUSY) {
                NandInfo.Reset();
            }
            SetStateIfBusy(result, 15);
            break;
        }

        case 16: {
            if (sNandCallbackCalled) {
                switch (sNandResult) {
                    case NAND_RESULT_OK: {
                        mState = 17;
                        break;
                    }

                    case NAND_RESULT_BUSY: {
                        mState = 15;
                        break;
                    }

                    case NAND_RESULT_NOEXISTS: {
                        mState = 13;
                        break;
                    }

                    case NAND_RESULT_CORRUPT: {
                        CutFunction2(sNandResult);
                        mResult = Result::NoExist;
                        Clear();
                        break;
                    }

                    default: {
                        HandleNandError(sNandResult);
                        break;
                    }
                }
            }
            break;
        }

        case 17: {
            mState = 18;
            sNandCallbackCalled = false;
            if (mData1 != nullptr) {
                gfl::Free(mData1);
                mData1 = nullptr;
            }

            mData1 = gfl::Alloc(Game::Mem1Heap, mData3Size, 0x20);
            mData1Size = mData3Size;
            memcpy(mData1, mData3, mData3Size);
            SetFlags(1, true);
            s32 result = NANDWriteAsync(&NandFileInfo, mData1, mData1Size, NandCallback, &CommandBlock);
            SetStateIfBusy(result, 17);
            break;
        }

        case 18: {
            if (sNandCallbackCalled) {
                SetFlags(1, false);
                switch (sNandResult) {
                    default: {
                        if (sNandResult >= NAND_RESULT_OK) {
                            mState = 19;
                        } else {
                            HandleNandError(sNandResult);
                        }
                        break;
                    }
                    
                    case NAND_RESULT_CORRUPT: {
                        CutFunction2(sNandResult);
                        mResult = Result::NoExist;
                        Clear();
                        break;
                    }

                    case NAND_RESULT_AUTHENTICATION:
                    case NAND_RESULT_ECC_CRIT: {
                        s32 result = NANDDelete(mTempFilename.c_str());
                        while (result == NAND_RESULT_BUSY) {
                            result = NANDDelete(mTempFilename.c_str());
                        }
                        mState = 13;
                        break;
                    }
                }
            }
            break;
        }

        case 19: {
            mState = 20;
            sNandCallbackCalled = false;
            NandInfo.SetUserData(&NandFileInfo, &CommandBlock, false);
            s32 result = NANDCloseAsync(&NandFileInfo, NandCallback, &CommandBlock);
            if (result == NAND_RESULT_BUSY) {
                NandInfo.ClearUserData();
            }

            SetStateIfBusy(result, 19);
            break;
        }

        case 20: {
            if (sNandCallbackCalled) {
                switch (sNandResult) {
                    case NAND_RESULT_OK: {
                        mState = 21;
                        break;
                    }

                    case NAND_RESULT_BUSY: {
                        mState = 19;
                        break;
                    }

                    case NAND_RESULT_CORRUPT: {
                        CutFunction2(sNandResult);
                        mResult = Result::NoExist;
                        Clear();
                        break;
                    }

                    default: {
                        HandleNandError(sNandResult);
                        break;
                    }
                }
            }
            break;
        }

        case 21: {
            sNandCallbackCalled = false;
            char homeDir[64];
            NANDGetHomeDir(homeDir);
            mState = 22;
            s32 result = NANDMoveAsync(mTempFilename.c_str(), homeDir, NandCallback, &CommandBlock);
            SetStateIfBusy(result, 21);
            break;
        }

        case 22: {
            if (sNandCallbackCalled) {
                switch (sNandResult) {
                    case NAND_RESULT_OK: {
                        mResult = Result::Ok;
                        Clear();
                        break;
                    }

                    case NAND_RESULT_CORRUPT: {
                        CutFunction2(sNandResult);
                        mResult = Result::NoExist;
                        Clear();
                        break;
                    }

                    default: {
                        HandleNandError(sNandResult);
                        break;
                    }
                }
            }
            break;
        }

        case 23: {
            mState = 24;
            sNandCallbackCalled = false;
            if (mData1 != nullptr) {
                gfl::Free(mData1);
                mData1 = nullptr;
            }

            mData1 = gfl::Alloc(Game::Mem1Heap, mData3Size, 0x20);
            mData1Size = mData3Size;
            memcpy(mData1, mData3, mData3Size);
            SetFlags(1, true);
            s32 result = NANDWriteAsync(&NandFileInfo, mData1, mData1Size, NandCallback, &CommandBlock);
            SetStateIfBusy(result, 23);
            break;
        }

        case 24: {
            if (sNandCallbackCalled) {
                SetFlags(1, false);
                switch (sNandResult) {
                    default: {
                        if (sNandResult >= NAND_RESULT_OK) {
                            mState = 27;
                        } else {
                            HandleNandError(sNandResult);
                        }
                        break;
                    }
                    case NAND_RESULT_CORRUPT: {
                        CutFunction2(sNandResult);
                        mResult = Result::NoExist;
                        Clear();
                        break;
                    }

                    case NAND_RESULT_AUTHENTICATION:
                    case NAND_RESULT_ECC_CRIT: {
                        if (mPhase == 4) {
                            s32 result = fn_806AD4A0(&NandFileInfo);
                            
                            while (result == NAND_RESULT_BUSY) {
                                result = fn_806AD4A0(&NandFileInfo);
                            }

                            NandInfo.Reset();
                            mState = 11;
                        } else {
                            HandleNandError(sNandResult);
                        }

                        break;
                    }
                }
            }
            break;
        }

        case 25: {
            mState = 26;
            sNandCallbackCalled = false;
            mData1Size = ROUND_UP(mData3Size, 0x20);
            mData1 = gfl::Alloc(Game::Mem1Heap, mData1Size, 0x20);
            SetFlags(0, true);
            s32 result = NANDReadAsync(&NandFileInfo, mData1, mData1Size, NandCallback, &CommandBlock);
            SetStateIfBusy(result, 25);
            break;
        }

        case 26: {
            if (sNandCallbackCalled) {
                SetFlags(0, false);
                s32 result;
                
                switch (sNandResult) {
                    default: {
                        if (sNandResult >= NAND_RESULT_OK) {
                            memcpy(mData3, mData1, mData3Size);
                            mState = 27;
                        } else {
                            HandleNandError(sNandResult);
                        }
                        break;
                    }
                    case NAND_RESULT_CORRUPT: {
                        CutFunction2(sNandResult);
                        mResult = Result::NoExist;
                        Clear();
                        break;
                    }

                    case NAND_RESULT_AUTHENTICATION:
                    case NAND_RESULT_ECC_CRIT: {
                        CutFunction();
                        NandInfo.Reset();
                        result = NANDClose(&NandFileInfo);
                        while (result == NAND_RESULT_BUSY) {
                            result = NANDClose(&NandFileInfo);
                        }

                        switch (result) {
                            case NAND_RESULT_OK: {
                                mResult = Result::Invalid;
                                Clear();
                                break;
                            }
                            
                            case NAND_RESULT_CORRUPT: {
                                mResult = Result::NoExist;
                                Clear();
                                break;
                            }

                            default: {
                                NandError(result);
                                break;
                            }
                        }
                    }
                }
            }
            break;
        }

        case 27: {
            mState = 28;
            sNandCallbackCalled = false;
            s32 result = NAND_RESULT_OK;

            if (mPhase == 4) {
                NandInfo.SetUserData(&NandFileInfo, &CommandBlock, true);
                result = NANDSafeCloseAsync(&NandFileInfo, NandCallback, &CommandBlock);
            } else if (mPhase == 5) {
                NandInfo.SetUserData(&NandFileInfo, &CommandBlock, false);
                result = NANDCloseAsync(&NandFileInfo, NandCallback, &CommandBlock);
            } else {
                GFL_HALT();
            }

            if (result == NAND_RESULT_BUSY) {
                NandInfo.ClearUserData();
            }

            SetStateIfBusy(result, 27);
            break;
        }

        case 28: {
            if (sNandCallbackCalled) {
                switch (sNandResult) {
                    case NAND_RESULT_OK: {
                        mResult = Result::Ok;
                        Clear();
                        break;
                    }

                    case NAND_RESULT_BUSY: {
                        mState = 27;
                        break;
                    }

                    case NAND_RESULT_CORRUPT: {
                        CutFunction2(sNandResult);
                        mResult = Result::NoExist;
                        Clear();
                        break;
                    }

                    default: {
                        HandleNandError(sNandResult);
                    }
                }
            }
            break;
        }
    }
}


void FlfNandMng::Clear() {
    if (mData1 != nullptr) {
        gfl::Free(mData1);
        mData1 = nullptr;
    }

    mTempFilename.clear();
    mPhase = 0;
    mState = 0;
}

void FlfNandMng::SetStateIfBusy(s32 result, int state) {
    if (result == NAND_RESULT_BUSY) {
        mState = state;
    } else if (result != NAND_RESULT_OK) {
        NandError(result);
    }
}
