#ifndef FLUFF_COLDATA_H
#define FLUFF_COLDATA_H

#include "null_def.h"
#include "types.h"
#include <utility>
#include <string>
#include "object/collision/Colbin.h"
#include "object/collision/KdTreeData.h"

class ColObjTrans;

#pragma pack(push, 1)
/// @note Size: `0x20`
class ColData : public KdTreeData {
public:
    inline ColData()
        : KdTreeData()
        , mNext(nullptr)
        , mOwner(nullptr)
        , m_10(0)
        , mFlags(1)
    { }

    inline ColData* GetNext() {
        return mNext;
    }

    inline void SetNext(ColData* next) {
        mNext = next;
    }

    /* Virtual Methods */
    /* 0x08 */ virtual ~ColData() override;
    /* 0x14 */ virtual void vf14();
	/* 0x18 */ virtual void vf18();
	/* 0x1C */ virtual void vf1C();
	/* 0x20 */ virtual void vf20();
	/* 0x24 */ virtual void vf24();
	/* 0x28 */ virtual void vf28();
	/* 0x2C */ virtual void vf2C();
	/* 0x30 */ virtual void CopyIdentity(ColData* pOther);
	/* 0x34 */ virtual void Copy(ColData* pOther);

    /* Class Members */

    /* 0x08 */ ColData* mNext;
    /* 0x0C */ ColObjTrans* mOwner;
    /* 0x10 */ uint m_10;
    /* 0x14 */ uint mNumEntries;
    /* 0x18 */ u64 mFlags;
};

#pragma pack(pop)
#endif
