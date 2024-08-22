#ifndef GFL_FIXEDMEMORYSTREAM_H
#define GFL_FIXEDMEMORYSTREAM_H

#include "types.h"
#include "gflStream.h"
namespace gfl {
    class FixedMemoryStream : public Stream {
    private:
        inline bool RangeValid() {
            return mStreamPos < mSize;
        }
    public:
        ENUM_CLASS(SeekType,
            Begin = 0,
            Current = 1,
            End = 2
        );
    public:
        FixedMemoryStream(void* addr, size_t newSize);

        // Returns the number of bytes read.
        virtual size_t Read(void* dst, size_t count);
        // Returns the number of bytes written.
        virtual size_t Write(void* src, size_t count);
        // Returns if the file seeking operation was successful.
        virtual bool Seek(size_t pos, int seekType);
        DECL_WEAK virtual size_t GetStreamPos();
        virtual void Reset();
        DECL_WEAK virtual ~FixedMemoryStream();

    private:
        void* mData;
        size_t mSize;
        size_t mStreamPos;
    };
}
#endif