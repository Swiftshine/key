#ifndef FLUFF_BGSTREADER_H
#define FLUFF_BGSTREADER_H

#include "types.h"

#include <list>
#include <vector>

namespace BGST {

class File;
class EntryInfo;
class Layer;

/// @note Size: `0x44`
class Reader {
public:
    ENUM_CLASS(State,
        PopEntryObject        = 0,
        GetMainImage    = 1,
        GetMaskImage    = 2
    );

    /// @note Size: `0x20`
    struct EntryObject {
        static bool Compare(EntryObject* pA, EntryObject* pB);
        
        Layer* mLayer;
        EntryInfo* mEntryInfo;
        void* mMainImage;
        size_t mMainImageSize;
        size_t mMainImageOffset; // referring to the file on disk
        void* mMaskImage;
        size_t mMaskImageSize;
        size_t mMaskImageOffset;
    };

    Reader(File* pBGSTFile);
    ~Reader();

    /* Class Methods */

    void Update();
    void GetMainImage();
    void GetMaskImage();
    void PushEntryObject(Layer* pLayer, EntryInfo* pEntryInfo);
    void EraseEntryObject(EntryInfo* pEntryInfo);
    void PopEntryObject();
    void Sort();

    DECL_WEAK void _CutFunction() DONT_INLINE_CLASS;

    /* Static Methods */

    static void FillVector(
        std::vector<EntryObject*>& rVec,
        std::list<EntryObject*>::iterator begin,
        std::list<EntryObject*>::iterator end
    );


    /* Class Members */

    /* 0x00 */ int mState;
    /* 0x04 */ File* mBGSTFile;
    /* 0x08 */ int m_8;
    /* 0x0C */ EntryObject mEntryObject;
    /* 0x2C */ std::list<EntryObject*> mObjectList;
    /* 0x38 */ std::vector<EntryObject*> mObjectVector;
};

}

#endif