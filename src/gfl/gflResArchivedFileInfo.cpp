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
    if (0 != GetFlags() & ResInfo::eFlags_GfArch) {
        return mArchive;
    }

    return nullptr;
}

ResArchivedFileInfo::~ResArchivedFileInfo() {
    u16 refCount = mRefCount;

    if (refCount != 0 && --refCount == 0) {
        if (mData != nullptr) {
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

    if (GetFlags() & ResInfo::eFlags_GfArch == 0) {
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

GfArch* ResFileInfo::GetGfArch() const {
    return mArchive;
}
