#ifndef FLUFF_List_H
#define FLUFF_List_H

#include "types.h"
#include <bitset>
#include "gfl/gflScopedPointer.h"
#include "gfl/gflLinkedList.h"
#include "gfl/gflMemory.h"
#include "gfl/gflMemoryUtil.h"
#include "graphics/BGSTImage.h"
#include "graphics/BGSTColumn.h"
#include "graphics/BGSTEntry.h"

class StageGraphicResources;

namespace BGST {
    class List {
    private:
        static List* sInstance;
    public:
        static List* Instance() {
            return sInstance;
        }

        DECL_WEAK void CutFunction() { }

        List(StageGraphicResources* arg1, size_t count);
        ~List();
        BGST::Image* GetImageByIndex(u16 index);
        void SetBit(size_t index);
        s16 GetNextImageIndex();
        // returns true if both the main and shadow image indices were successfully set
        bool AssignImageIndices(BGST::Column* column);
        void AddEntry(BGST::Entry* entry);
        void RemoveEntry(BGST::Entry* entry);
        void RemoveColumn(BGST::Column* column);
        void ResetBit(size_t index);
    private:
        gfl::FreedScopedPointer<BGST::Image> mImages;
        size_t mCount; // signed instead?
        std::bitset<200> mBitset;
        gfl::LinkedList<BGST::Entry> mEntryList;
        StageGraphicResources* mResources;
    };
    
}


#endif
