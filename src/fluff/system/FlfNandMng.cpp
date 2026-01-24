#include <revolution/os.h>
#include "system/FlfNandMng.h"
#include "gfl/gflHomeMenu.h"
#include "gfl/gflMemory.h"
#include "gfl/gflMemoryUtil.h"
#include "gfl/gflMisc.h"

DECL_WEAK DONT_INLINE void CutFunction() { }

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
    memset(&FlfNandMng::sCommandBlock, 0, sizeof(NANDCommandBlock));
}

void FlfNandInfo::Init(NANDFileInfo* pFileInfo, NANDCommandBlock* pCommandBlock, bool safe) {
    Update();
    NANDSetUserData(pCommandBlock, this);
    mFileInfo = pFileInfo;
    mCommandBlock = pCommandBlock;
    mIsSafeMode = safe;
    mResult = FlfNandMng::Result::Ok;
}

void FlfNandInfo::SetUserData(NANDFileInfo* pFileInfo, NANDCommandBlock* pCommandBlock) {
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
    lbl_808E51D4 = true;
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
    : m_238()
{
    FlfNandInfo::Instance().Update();
    sInstance = this;
    mResult = Result::Invalid;
    mState = 0;
    m_4 = 0;
    sNandResult = NAND_RESULT_OK;
    lbl_808E51D4 = false;
    m_C = 0;
    m_10 = 0;
    mData1Size = 0;
    mData1 = nullptr;
    mData3 = nullptr;
    mData3Size = 0;
    mData2Size = 0x4000;
    gfl::Heap* heap = gfl::Memory::TryGetHeapByID(gfl::HeapID::LIB1);
    mData2 = gfl::Alloc(heap, mData2Size, 0x20);
    memset(mFilename, 0, sizeof(mFilename));
    mFilesize = 0;
    mNumChunks = 0;
    m_234 = 0;
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
    FlfNandInfo::Instance().Update();
    gfl::Strcpy(mFilename, sizeof(mFilename), pFilename);
    mFilesize = filesize;
    m_4 = 1;
    mState = 1;
    mResult = Result::Reset;
}

void FlfNandMng::fn_802291E4(const char* pFilename) {
    FlfNandInfo::Instance().Update();
    gfl::Strcpy(mFilename, sizeof(mFilename), pFilename);
    m_4 = 2;
    mState = 7;
    mResult = Result::Reset;
}

void FlfNandMng::fn_8022924C(size_t numChunks, int arg2) {
    FlfNandInfo::Instance().Update();
    mNumChunks = numChunks;
    m_234 = arg2;
    m_4 = 3;
    mState = 9;
    mResult = Result::Reset;
}

void FlfNandMng::fn_802292B8(const char* pFilename, void* pData, size_t dataSize) {
    FlfNandInfo::Instance().Update();
    gfl::Strcpy(mFilename, sizeof(mFilename), pFilename);
    mData3 = pData;
    mData3Size = dataSize;
    m_4 = 4;
    mState = 11;
    mResult = Result::Reset;
}

void FlfNandMng::fn_80229340(const char* pFilename, void* pData, size_t dataSize) {
        FlfNandInfo::Instance().Update();
    gfl::Strcpy(mFilename, sizeof(mFilename), pFilename);
    mData3 = pData;
    mData3Size = dataSize;
    m_4 = 5;
    mState = 11;
    mResult = Result::Reset;
}

size_t FlfNandMng::GetNumChunks(size_t size) {
    return size + 0x3FFF >> 0xE;
}

extern "C" void fn_8064740C(bool);

void FlfNandMng::SetFlags(uint flag, bool set) {
    if (set) {
        mFlags |= 1 << flag;
    } else {
        mFlags &= ~(1 << flag);
    }

    fn_8064740C(mFlags == 0);
    gfl::HomeMenu::GetInstance()->SetUnk4(mFlags & ~1);
}

void FlfNandMng::fn_80229470() {
    switch (m_4) {
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
            lbl_808E51D4 = false;
            FlfNandInfo::Instance().Init(&sNandFileInfo, &sCommandBlock, false);

            s32 result = NANDOpenAsync(mFilename, &sNandFileInfo, 1, NandCallback, &sCommandBlock);

            if (result == NAND_RESULT_BUSY) {
                FlfNandInfo::Instance().Reset();
            }

            fn_8022A48C(result, 1);
            break;
        }

        case 2: {
            if (lbl_808E51D4) {
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
            lbl_808E51D4 = false;
            // s32 result = 
            break;
        }
    }
}