#ifndef FLUFF_BGSTLIST_H
#define FLUFF_BGSTLIST_H

#include "types.h"
#include <bitset>
#include "gfl/gflLinkedList.h"
#include "gfl/gflMemory.h"
#include "graphics/BGSTImage.h"
#include "graphics/BGSTColumn.h"
#include "graphics/BGSTEntry.h"

class BgImageData;

class BGSTList {
private:
    static BGSTList* sInstance;
public:
    static BGSTList* Instance() {
        return sInstance;
    }

    DECL_WEAK void CutFunction() { }

    BGSTList(void* arg1, size_t count);
    ~BGSTList();
    BGST::Image* GetImageByIndex(s16 index);
    void SetBit(size_t index);
    s16 GetNextImageIndex();
    // returns true if both the main and shadow image indices were successfully set
    bool AssignImageIndices(BGST::Column* column);
    void AddEntry(BGST::Entry* entry);
    void RemoveEntry(BGST::Entry* entry);
    void RemoveColumn(BGST::Column* column);
    void ResetBit(size_t index);
private:
    BGST::Image* mImages;
    size_t mCount; // signed instead?
    std::bitset<200> mBitset;
    gfl::LinkedList<BGST::Entry> mEntryList;
    void* m_30;
};


#endif
