#include "gflResFileInfo.h"
#include "gflResArchivedFileInfo.h"
#include "gflGfArch.h"
#include <revolution/DVD.h>
using namespace gfl;

GfArch* ResArchivedFileInfo::TryGetGfArch() {
    if (nullptr != mOwner) {
        return mOwner->TryGetGfArch();
    }

    return nullptr;
}

GfArch* ResFileInfo::TryGetGfArch() {
    if (0 != GetFlags() & Flags::GfArch) {
        return mArchive;
    }

    return nullptr;
}

ResArchivedFileInfo::~ResArchivedFileInfo() {
    u16 level = mLevel;

    if ((0 != level) && (level--, mLevel = level, 0 == level)) {
        if (nullptr != mData) {
            mOwner->Destroy();
            mOwner = nullptr;
            mData = nullptr;
        }
    }
}

size_t ResArchivedFileInfo::GetDataSize() {
    return mDataSize;
}

void* ResArchivedFileInfo::GetData() {
    return mData;
}

size_t ResFileInfo::GetFilesize() {
    DVDFileInfo fileinfo;

    if (0 == GetFlags() & Flags::GfArch) {
        if (DVDFastOpen(mEntrynum, &fileinfo)) {
            DVDClose(&fileinfo);
        } else {
            fileinfo.size = 0;
        }
    } else if (nullptr == mArchive) {
        fileinfo.size = 0;
    } else {
        fileinfo.size = mArchive->GetDataSize();
    }

    return fileinfo.size;
}

GfArch* ResFileInfo::GetGfArch() {
    return mArchive;
}
