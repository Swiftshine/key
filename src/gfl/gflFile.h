#ifndef GFL_FILE_H
#define GFL_FILE_H

#include "types.h"
#include "gflFixedString.h"


namespace gfl {
    class FileSystemWii;

    class File {
    public:
        static const char EmptyFilename[];
    public:
        File();

        static gfl::File* Open(const char*, int);
        static bool Open(const char*);

        virtual void Close();
        virtual void Read(void* addr, uint len, uint filepos);
        virtual void ReadAsync(void* addr, size_t len, size_t offs, u32 callback);
        virtual void vf14();
        virtual void vf18();
        virtual int GetFileStatus();
        virtual void vf20();
        virtual void Reset();
        virtual ~File();
    private:
        FileSystemWii* mFilesystem;
        FixedString mFilename;
        uint m_20C;
        void* mDvdFileInfo;
        uint m_214;
        uint m_218;
        uint m_21C;
        uint m_220;
        uint m_224;
        uint m_228;
        uint m_22C;
        uint m_230;
        uint m_234;
        uint m_238;
        uint m_23C;
        uint m_240;
        uint m_244;
        uint m_248;
        int mEntrynum;
    };
}

#endif
