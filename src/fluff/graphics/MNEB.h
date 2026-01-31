#ifndef FLUFF_MNEB_H
#define FLUFF_MNEB_H

#include "gfl/gflResFileInfo.h"

class NURBSSet;
class NURBSObject;

// Data Definition?
// sdata

namespace MNEB {
    struct EntryBase {
        char mMagic[4];
    };

    struct CurveEntry {
        char mMagic[4];
        // blah blah
    };

    struct MNDDEntry {
        void* m_0;
        void* m_4;
        uint mCount;
        void* m_C;
    };


    class File {
    public:
        NURBSSet* Load(NURBSSet* pNURBSSet, const char* pFilepath);
        CurveEntry* GetNextEntry(CurveEntry* pEntry) const;
        /// @return The number of curves in the file.
        uint CopyHeader(void* pData);
        void SetObjectData(NURBSObject* pObj, CurveEntry* pEntry);
        MNDDEntry* fn_80029ED8(MNDDEntry* pEntry);

        bool CheckMagic(const char* pMagic, EntryBase* entry) {
            return (
                entry->mMagic[0] == pMagic[0] &&
                entry->mMagic[1] == pMagic[1] &&
                entry->mMagic[2] == pMagic[2] &&
                entry->mMagic[3] == pMagic[3]
            ) ? true : false;
        }

        /* Class Members */

        /* 0x00 */ uint mFlags;
        /* 0x04 */ bool m_4;
        /* 0x08 */ float m_8;
        /* 0x0C */ bool m_C;
        /* 0x10 */ void* mRawData;
    };
}

#endif
