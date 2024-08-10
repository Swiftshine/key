#ifndef GFL_FIXED_MEMORY_STREAM_H
#define GFL_FIXED_MEMORY_STREAM_H


#include <gfl/gfl_types.h>
#include <gfl/mem/Stream.h>

namespace gfl {
    class FixedMemoryStream : public Stream {
    private:
        inline bool RangeValid() {
            return this->mStreamPos < this->mSize;
        }
    public:
        SCOPED_ENUM(SeekType,
            Begin = 0,
            Current = 1,
            End = 2
        );
    public:
        FixedMemoryStream(u8* addr, u32 newSize);


        // Returns the number of bytes read.
        virtual u32  Read(u8* dst, u32 count);
        // Returns the number of bytes written.
        virtual u32  Write(u8* src, u32 count);
        // Returns if the file seeking operation was successful.
        virtual bool Seek(int pos, int seekType);
        virtual u32  GetStreamPos();
        virtual void Reset();
        virtual ~FixedMemoryStream();
    private:
        u8*   mpData;
        u32   mSize;
        u32   mStreamPos;
    };

    ASSERT_SIZE(FixedMemoryStream, 0x10)
}


#endif
