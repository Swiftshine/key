#ifndef FLUFF_List_H
#define FLUFF_List_H

#include "types.h"
#include <bitset>
#include "gfl/gflPointer.h"
#include "gfl/gflLinkedList.h"
#include "gfl/gflMemory.h"
#include "gfl/gflMemoryUtil.h"
#include "graphics/BGSTImage.h"
#include "graphics/BGSTEntryInfo.h"
#include "graphics/BGSTLayer.h"

class StageGraphicResources;

namespace BGST {
    class List {
    public:
        /* Static Variables */

        static List* sInstance;

        static inline List* Instance() {
            return sInstance;
        }
        
        /* Constructor + Destructor */

        List(StageGraphicResources* arg1, size_t count);
        ~List();

        /* Class Methods */

        inline void CutFunction();
        BGST::Image* GetImageByIndex(u16 index);
        void SetBit(size_t index);
        u16 GetNextImageIndex();
        // returns true if both the main and shadow image indices were successfully set
        bool AssignImageIndices(BGST::EntryInfo* pEntryInfo);
        void AddLayer(BGST::Layer* pLayer);
        void RemoveLayer(BGST::Layer* pEntryInfo);
        void RemoveEntryInfo(BGST::EntryInfo* pEntryInfo);
        void ResetBit(size_t index);
    
        /* Class Members */

        /* 0x00 */ gfl::FreedPointer<BGST::Image> mImages;
        /* 0x04 */ size_t mCount; // signed instead?
        /* 0x08 */ std::bitset<200> mBitset;
        /* 0x24 */ gfl::LinkedList<BGST::Layer> mLayerList;
        /* 0x30 */ StageGraphicResources* mResources;
    };
    
}


#endif
