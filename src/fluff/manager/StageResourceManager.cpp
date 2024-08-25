#include <cstring>
#include "manager/StageResourceManager.h"
#include "stage/StageResourceList.h"
#include "gfl/gflMemoryUtil.h"

StageResourceManager::StageResourceManager()
    : mResourceList(nullptr)
    , mBGResFileInfo(nullptr)
    , mBGData(nullptr)
    , mCommonResFileInfo(nullptr)
    , mCommonValid(false)
    , m_11(false)
    , m_18(false)
    , m_1C(-1)
    , m_20(-1)
    , m_24(1)
    , mMapdataResFileInfo(nullptr)
{
    // StageResourceList* ptr = new (10) StageResourceList;

    // if (nullptr == ptr) {
    //     delete mResourceList;
    //     mResourceList = nullptr;
    // } else {
    //     mResourceList = ptr;
    // }

    // ptr = nullptr;

    GFL_ALLOC_WORK(mResourceList, StageResourceList);
    // gfl::WorkAlloc<StageResourceList>(mResourceList);

    memset(&mCurrentSections, 0, 0x78);
}

StageResourceManager::~StageResourceManager() {
    
}