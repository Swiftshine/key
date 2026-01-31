#ifndef FLUFF_MNEB_H
#define FLUFF_MNEB_H

#include "gfl/gflResFileInfo.h"
#include "graphics/NURBSSet.h"

namespace MNEB {
    struct CurveEntry {
        char mMagic[4];
        // blah blah
    };

    class File {
    public:
        NURBSSet* Load(NURBSSet* pNURBSSet, const char* pFilepath);
        CurveEntry* GetNextEntry(CurveEntry* pEntry) const;
        /// @return The number of curves in the file.
        uint CopyHeader(void* pData);
        void SetObjectData(NURBSObject* pObj, CurveEntry* pEntry);
        CurveEntry* fn_80029ED8(CurveEntry* pEntry);

        /* Class Members */

        /* 0x00 */ uint mFlags;
        /* 0x04 */ bool m_4;
        /* 0x08 */ float m_8;
        /* 0x0C */ bool m_C;
        /* 0x10 */ void* mRawData;
    };
}

#endif
