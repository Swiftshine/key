#include "gfl/gflMisc.h"
#include "system/FlfNandMng.h"

DECL_WEAK DONT_INLINE void CutFunction() { }

DECL_WEAK DONT_INLINE void FlfNandCommandBlock::SetUserData(void* pUserData) {
    this->userData = pUserData;
}

void FlfNandMng::NandError(NANDResult result) {    
    if (result != NAND_RESULT_OK) {
        CutFunction(); // probably some logging
        GFL_HALT();
    }
}

FlfNandInfo::FlfNandInfo()
    : mIsOpen(false)
    , mResult(FlfNandMng::Result::None)
    , mFileInfo(nullptr)
    , mCommandBlock(nullptr)
{
    memset(&FlfNandMng::sCommandBlock, 0, sizeof(NANDCommandBlock));
}

void FlfNandInfo::Init(NANDFileInfo* pFileInfo, FlfNandCommandBlock* pCommandBlock, bool open) {
    Update();
    pCommandBlock->SetUserData(this);
    mFileInfo = pFileInfo;
    mCommandBlock = pCommandBlock;
    mIsOpen = open;
    mResult = FlfNandMng::Result::Ok;
}

void FlfNandInfo::SetUserData(NANDFileInfo* pFileInfo, FlfNandCommandBlock* pCommandBlock) {
    pCommandBlock->SetUserData(this);
    mResult = FlfNandMng::Result::NoExist;
}

void FlfNandInfo::ClearUserData() {
    mCommandBlock->SetUserData(nullptr);
    mResult = FlfNandMng::Result::Invalid;
}

FlfNandInfo::~FlfNandInfo() {
    Update();
}

void FlfNandInfo::Invalidate() {
    mResult = FlfNandMng::Result::Invalid;
}