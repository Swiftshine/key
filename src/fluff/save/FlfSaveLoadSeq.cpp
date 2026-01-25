#include "gfl/gflGameRootTask.h"
#include "save/FlfSaveLoadSeq.h"
#include "game/Game.h"

FlfSaveLoadSeq* FlfSaveLoadSeq::GetInstance() {
    return sInstance;
}

FlfSaveLoadSeq* FlfSaveLoadSeq::Build() {
    return new (gfl::HeapID::LIB1) FlfSaveLoadSeq;
}

void FlfSaveLoadSeq::DestroyInstance() {
    delete sInstance;
}

FlfSaveLoadSeq::FlfSaveLoadSeq()
    : mOperation(Operation::None)
    , mLoadState(0)
    , m_C(false)
    , m_18(0)
    , m_1C(0)
    , m_21(false)
    , mSaveDataLoaded(false)
    , mNumSDChunks(0)
    , m_28(0)
    , mNumNANDChunks(0)
    , m_30(0)
    , mWaitTime1(0)
    , mWaitTime2(0)
    , mBuffer(nullptr)
    , mTask(this, Update, "SaveLoad")
    , mLoadSaveInfo()
    , mSaveSaveInfo()
    , m_74(new (gfl::HeapID::LIB1) FlfSaveLoadSeq_Substruct(&mNandManager))
    , mNandManager()
    , mBannerManager(&mNandManager)
{
    sInstance = this;
    Clear();
    mTask.SetFlags(0x50);
    mTask.m_14 |= 0xFFFFFFFF;
    gfl::GameRootTask::Instance()->MakeChild(&mTask);
}

FlfSaveLoadSeq::~FlfSaveLoadSeq() {
    sInstance = nullptr;
}

void FlfSaveLoadSeq::Clear() {
    void* buf = mBuffer;
    mOperation = Operation::None;
    mLoadState = 0;
    m_18 = 0;
    m_1C = 0;
    mSaveDataLoaded = false;
    mNumSDChunks = 0;
    m_28 = 0;
    mNumNANDChunks = 0;
    m_30 = 0;
    m_20 = false;
    m_21 = false;
    m_C = false;
    mWaitTime1 = 0;
    mWaitTime2 = 0;

    mLoadSaveInfo.mSaveData = nullptr;
    mLoadSaveInfo.mSaveDataSize = 0;
    mSaveSaveInfo.mSaveData = nullptr;
    mSaveSaveInfo.mSaveDataSize = 0;
    
    if (buf != nullptr) {
        gfl::Free(buf);
        mBuffer = nullptr;
    }
}

extern "C" {
    size_t fn_80634E2C();
    int fn_802B69B4();
}

void FlfSaveLoadSeq::CopyLoadSaveInfo(const LoadSaveInfo& rSaveInfo) {
    mLoadSaveInfo = rSaveInfo;
    mOperation = Operation::Load;
    mLoadState = 0;
    m_18 = 0;
    m_1C = 0;
    m_20 = false;
    m_21 = false;
    m_C = false;
    
    size_t num1 = FlfNandMng::GetNumChunks(rSaveInfo.mSaveDataSize);
    size_t num2 = FlfNandMng::GetNumChunks(sizeof(NANDBanner));
    size_t num3 = fn_80634E2C();
    mNumSDChunks = num1 + num2 + num3;
    m_28 = fn_802B69B4() + 2;
    mWaitTime1 = 3;
    mWaitTime2 = 0;
}

size_t FlfSaveLoadSeq::GetNumSDBytes() {
    return (((mNumSDChunks * SECTOR_SIZE) + BLOCK_SIZE) - 1) / BLOCK_SIZE;
}

size_t FlfSaveLoadSeq::GetNumNANDBytes() {
    return (((mNumNANDChunks * SECTOR_SIZE) + BLOCK_SIZE) - 1) / BLOCK_SIZE;
}

void FlfSaveLoadSeq::CopySaveSaveInfo(const SaveSaveInfo& rSaveInfo) {
    mSaveSaveInfo = rSaveInfo;
    mOperation = Operation::Save;
    mSaveState = 0;
    mWaitTime1 = 3;
    mWaitTime2 = 0;
    mNandManager.SetFlags(2, true);
}

void FlfSaveLoadSeq::Update() const {
    GET_UNCONST(FlfSaveLoadSeq);

    switch (mOperation) {
        case Operation::Load: {
            self->Load();
            break;
        }

        case Operation::Save: {
            self->Save();
            break;
        }
    }

    self->mBannerManager.fn_802A4370();
    self->m_74->fn_80634F5C();
    self->mNandManager.fn_80229470();
}

void FlfSaveLoadSeq::Load() {
    switch (mLoadState) {
        case 0: {
            fn_8022D430(3);
            mBannerManager.fn_802A4210();
            mLoadState = 1;
            break;
        }

        case 1: {
            switch (mBannerManager.GetUnk10()) {
                case 1: {
                    mNandManager.fn_80229170(mLoadSaveInfo.mSaveFileName.c_str(), mLoadSaveInfo.mSaveDataSize);
                    mLoadState = 2;
                    break;
                }
                
                case 2: {
                    m_C = true;
                    mBannerManager.fn_802A4300();
                    mLoadState = 4;
                    break;
                }

                case 3: {
                    fn_8022D440(0x10);
                    break;
                }
            }

            break;
        }

        case 2: {
            switch (mNandManager.GetUnk8()) {
                case 1: {
                    mLoadState = 16;
                    break;
                }
                
                case 2: {
                    fn_8022D430(8);
                    mLoadState = 3;
                    break;
                }

                case 4: {
                    fn_8022D440(0x10);
                    break;
                }

                case 3: {
                    m_C = true;
                    mBannerManager.fn_802A4300();
                    mLoadState = 4;
                    break;
                }
            }
            break;
        }

        case 3: {
            switch (m_1C) {
                case 3: {
                    fn_8022D400();
                    fn_8022D430(9);
                    mLoadState = 10;
                    break;
                }

                case 4: {
                    mNandManager.SetFlags(2, true);
                    fn_8022D430(5);
                    mBannerManager.fn_802A4300();
                    mLoadState = 4;
                    break;
                }
            }
            break;
        }

        case 4: {
            switch (mBannerManager.GetUnk10()) {
                case 1: {
                    // FlfSaveLoadSeq_Substruct::fn_80634EE8(m_74);
                    m_74->fn_80634EE8();
                    mLoadState = 6;
                    break;
                }

                case 3: {
                    fn_8022D440(0x10);
                    break;
                }
            }
            break;
        }

        case 6: {
            switch (m_74->GetUnk2C()) {
                case 1: {
                    mNandManager.fn_802291E4(mLoadSaveInfo.mSaveFileName.c_str());
                    mLoadState = 5;
                    break;
                }

                case 3: {
                    fn_8022D440(0x10);
                    break;
                }
            }
            break;
        }
        
        case 5: {
            switch (mNandManager.GetUnk8()) {
                case 1:
                case 3: {
                    if (m_C) {
                        mLoadState = 8;
                    } else {
                        mNandManager.SetFlags(2, false);
                        fn_8022D430(10);
                        mLoadState = 7;
                    }
                    break;
                }

                case 2: {
                    fn_8022D440(0x10);
                    break;
                }
            }
            
            break;
        }


        case 7: {
            if (m_1C == 1) {
                fn_8022D430(0);
                mLoadState = 8;
            }
            break;
        }

        case 8: {
            mNandManager.fn_8022924C(mNumSDChunks, m_28);
            mLoadState = 9;
            break;
        }

        case 9: {
            switch (mNandManager.GetUnk8()) {
                case 1: {
                    m_21 = true;
                    fn_8022D430(15);
                    mLoadState = 12;
                    break;
                }
                
                case 2: {
                    fn_8022D430(11);
                    mLoadState = 11;
                    break;
                }
                
                case 3: {
                    fn_8022D430(12);
                    mLoadState = 11;
                    break;
                }
            }
            break;
        }

        case 10: {
            switch (m_1C) {
                case 1: {
                    InitSaveData();
                    fn_8022D430(1);
                    mSaveDataLoaded = true;
                    mOperation = Operation::None;
                    break;
                }

                case 2: {
                    fn_8022D414();
                    break;
                }
            }
            break;
        }

        case 12: {
            switch (m_1C) {
                case 1: {
                    mNandManager.SetFlags(2, true);
                    fn_8022D430(6);
                    mWaitTime2 = 60;
                    mLoadState = 13;
                    break;
                }

                case 2: {
                    fn_8022D400();
                    fn_8022D430(9);
                    mLoadState = 10;
                    break;
                }
            }
            break;
        }

        case 11: {
            switch (m_1C) {
                case 3: {
                    fn_8022D400();
                    fn_8022D430(9);
                    mLoadState = 10;
                    break;
                }

                case 5: {
                    mNandManager.SetFlags(2, false);
                    fn_8022D430(2);
                    mOperation = Operation::Op_3;
                    break;
                }
            }

            break;
        }

        case 13: {
            if (mWaitTime2 > 0) {
                mWaitTime2--;
            } else {
                mLoadState = 14;
            }
            break;
        }

        case 14: {
            if (mWaitTime1 == 0) {
                fn_8022D440(0x10);
            } else {
                mWaitTime1--;
                InitSaveData();
                mNandManager.fn_802292B8(
                    mLoadSaveInfo.mSaveFileName.c_str(), 
                    mLoadSaveInfo.mSaveData,
                    mLoadSaveInfo.mSaveDataSize
                );
                mLoadState = 15;
            }
            break;
        }

        case 15: {
            switch (mNandManager.GetUnk8()) {
                case 1: {
                    mLoadState = 16;
                    break;
                }

                case 2: {
                    mLoadState = 14;
                    break;
                }

                case 3: {
                    fn_8022D440(0x10);
                    break;
                }
            }
            break;
        }

        case 16: {
            mNandManager.fn_80229340(mLoadSaveInfo.mSaveFileName.c_str(), mLoadSaveInfo.mSaveData, mLoadSaveInfo.mSaveDataSize);
            mLoadState = 17;
            break;
        }

        case 17: {
            switch (mNandManager.GetUnk8()) {
                case 1: {
                    if (IsSaveDataValid(mLoadSaveInfo.mSaveData, mLoadSaveInfo.mSaveDataSize)) {
                        mLoadState = 18;
                    } else {
                        mNandManager.SetFlags(2, false);
                        fn_8022D430(8);
                        mLoadState = 3;
                    }
                    break;
                }

                case 4:
                case 2: {
                    mNandManager.SetFlags(2, false);
                    fn_8022D430(8);
                    mLoadState = 3;
                    break;
                }

                case 3: {
                    fn_8022D440(0x10);
                    break;
                }
            }
            break;
        }

        case 18: {
            if (m_21) {
                mLoadState = 25;
            } else {
                mNumNANDChunks = 0;
                m_30 = 0;
                m_74->fn_80634F08(&mNumNANDChunks, &m_30);
                mLoadState = 19;
            }
            break;
        }

        case 19: {
            switch (m_74->GetUnk2C()) {
                case 1: {
                    mLoadState = 27;
                    break;
                }

                case 2: {
                    if (GetUnk18() == 0 || GetUnk18() == 3) {
                        fn_8022D430(4);
                    }

                    mLoadState = 20;
                    break;
                }

                case 3: {
                    fn_8022D440(16);
                    break;
                }
            }
            break;
        }

        case 20: {
            mNandManager.fn_8022924C(mNumNANDChunks, m_30);
            mLoadState = 21;
            break;
        }

        case 21: {
            switch (mNandManager.GetUnk8()) {
                case 1: {
                    mLoadState = 24;
                    break;
                }

                case 2: {
                    fn_8022D430(13);
                    mLoadState = 23;
                    break;
                }
                
                case 3: {
                    fn_8022D430(14);
                    mLoadState = 23;
                    break;
                }
            }
            break;
        }
        
        case 23: {
            switch (m_1C) {
                case 3: {
                    fn_8022D400();
                    fn_8022D430(9);
                    mLoadState = 22;
                    break;
                }

                case 5: {
                    mNandManager.SetFlags(2, false);
                    fn_8022D430(2);
                    mOperation = Operation::Op_3;
                    break;
                }
            }
            break;
        }
        
        case 22: {
            switch (m_1C) {
                case 1: {
                    InitSaveData();
                    fn_8022D430(1);
                    mSaveDataLoaded = true;
                    mOperation = Operation::None;
                    break;
                }

                case 2: {
                    fn_8022D414();
                    break;
                }
            }
            break;
        }

        case 24: {
            if (m_20) {
                mNandManager.SetFlags(2, true);
                mLoadState = 25;
            }

            break;
        }

        case 25: {
            m_74->fn_80634F3C();
            mLoadState = 26;
            break;
        }

        case 26: {
            switch (m_74->GetUnk2C()) {
                case 1: {
                    mLoadState = 27;
                    break;
                }

                case 3: {
                    fn_8022D440(16);
                    break;
                }
            }
            break;
        }

        case 27: {
            mBannerManager.fn_802A4288();
            mLoadState = 28;
            break;
        }

        case 28: {
            switch (mBannerManager.GetUnk10()) {
                case 1: {
                    mNandManager.SetFlags(2, false);
                    mSaveDataLoaded = false;
                    fn_8022D430(1);
                    mOperation = Operation::None;
                    break;
                }

                case 3: {
                    fn_8022D440(16);
                    break;
                }
            }
            break;
        }
    }
}

void FlfSaveLoadSeq::Save() {
    switch (mSaveState) {
        case 0: {
            if (mWaitTime1 == 0) {
                fn_8022D440(16);
            } else {
                mWaitTime1--;
                mNandManager.fn_802292B8(mLoadSaveInfo.mSaveFileName.c_str(), mSaveSaveInfo.mSaveData, mSaveSaveInfo.mSaveDataSize);
                fn_8022D430(7);
                mSaveState = 1;
            }
            break;
        }

        case 1: {
            switch (mNandManager.GetUnk8()) {
                case 1: {
                    mSaveState = 2;
                    break;
                }
                
                case 2: {
                    mSaveState = 0;
                    break;
                }

                case 3: {
                    fn_8022D440(16);
                    break;
                }
            }
            break;
        }

        case 2: {
            if (mBuffer != nullptr) {
                mBuffer.Destroy();
            }
            mBuffer.Create(gfl::Alloc(Game::Mem2Heap, mSaveSaveInfo.mSaveDataSize, 0x20));
            void* buf = mBuffer;
            mNandManager.fn_80229340(mLoadSaveInfo.mSaveFileName.c_str(), buf, mSaveSaveInfo.mSaveDataSize);
            mSaveState = 3;
            break;
        }

        case 3: {
            switch (mNandManager.GetUnk8()) {
                case 1: {
                    size_t numBytes = mSaveSaveInfo.mSaveDataSize;
                    SaveData* sd = reinterpret_cast<SaveData*>(mBuffer.Get());
                    
                    if (memcmp(sd, mSaveSaveInfo.mSaveData, numBytes) == 0 && IsSaveDataValid(sd, numBytes)) {
                        if (mBuffer != nullptr) {
                            mBuffer.Destroy();
                        }
                        mSaveState = 4;
                    } else {
                        mSaveState = 0;
                    }

                    if (mBuffer != nullptr) {
                        mBuffer.Destroy();
                    }
                    break;
                }

                case 4:
                case 2: {
                    mSaveState = 0;
                    if (mBuffer != nullptr) {
                        mBuffer.Destroy();
                    }
                    break;
                }

                case 3: {
                    if (mBuffer != nullptr) {
                        mBuffer.Destroy();
                    }
                    fn_8022D440(16);
                    break;
                }
            }
            break;
        }

        case 4: {
            mBannerManager.fn_802A4288();
            mSaveState = 5;
            break;
        }

        case 5: {
            switch (mBannerManager.GetUnk10()) {
                case 1: {
                    fn_8022D430(1);
                    mOperation = Operation::None;
                    mNandManager.SetFlags(2, false);
                    break;
                }

                case 3: {
                    fn_8022D440(16);
                    break;
                }
            }
            break;
        }
    }
}

void FlfSaveLoadSeq::fn_8022D400() {
    m_10 = mLoadState;
    m_14 = m_18;
}

void FlfSaveLoadSeq::fn_8022D414() {
    mLoadState = m_10;
    m_18 = m_14;
    m_1C = 0;
}

void FlfSaveLoadSeq::fn_8022D430(int arg1) {
    m_18 = arg1;
    m_1C = 0;
}

void FlfSaveLoadSeq::fn_8022D440(int arg1) {
    fn_8022D430(arg1);
    mOperation = Operation::Op_4;
}

bool FlfSaveLoadSeq::IsSaveDataValid(SaveData* pSaveData, size_t numBytes) {
    return pSaveData->IsValid(numBytes);
}

// https://decomp.me/scratch/vJxMy
// (closest: https://decomp.me/scratch/ozRPG)
// void FlfSaveLoadSeq::InitSaveData() {
//     SaveData_Header h;
//     SaveData_Header* p;
//     SaveData* sd = mLoadSaveInfo.mSaveData;
//     sd->mHeader.mRegionCode = Language::GetCurrentRegionCode();
//     sd->mHeader.mVersion = SAVEDATA_VERSION;
//     sd->mHeader.mChecksum = DEFAULT_CHECKSUM;
//     sd->mHeader.m_C = h.m_C;
//     sd->mHeader.m_10 = h.m_10;
//     sd->Init();
//     memset(sd->mSaveSlots, 0, sizeof(SaveSlot) * 3);
//     sd->InitSaveSlots();
// }

bool FlfSaveLoadSeq::IsSaveDataLoaded() const {
    return mSaveDataLoaded;
}

/* Code-merged methods */

int FlfSaveLoadSeq::GetUnk18() const {
    return m_18;
}
