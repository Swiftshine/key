#include <gfl/mem/FixedMemoryStream.h>
#include <decomp/thunks.h>
#include <gfl/mem/Mem.h>

using namespace gfl;

FixedMemoryStream::FixedMemoryStream(u8* addr, u32 newSize) {
    mpData = addr;
    mSize = newSize;
    mStreamPos = 0;
}

asm FixedMemoryStream::~FixedMemoryStream(void) {
    nofralloc
    b common_dtor
}

u32 FixedMemoryStream::Read(u8* dst, u32 count) {
    u32 remain;
    u8* offs;
    
    if (this->mStreamPos == this->mSize) {
        return 0;
    }
        
    offs = (u8*)this->mpData + this->mStreamPos;
    remain = this->mSize - this->mStreamPos;
    count = (remain < count) ? remain : count;

    memcpy(dst, offs, count);
    this->mStreamPos += count;
    return count;
}


u32 FixedMemoryStream::Write(u8* src, u32 count) {
    u32 remain;
    u8* offs;
    
    if (this->mStreamPos >= this->mSize) {
        return 0;
    }
        
    offs = (u8*)this->mpData + this->mStreamPos;
    remain = this->mSize - this->mStreamPos;
    count = (remain < count) ? remain : count;

    memcpy(offs, src, count);
    this->mStreamPos += count;
    return count;
}

bool FixedMemoryStream::Seek(int pos, int seekType) {
    s32 finalPos = 0;

    switch (seekType) {
        case SeekType::Begin: {
            finalPos = pos;
            break;
        }

        case SeekType::Current: {
            finalPos = pos + this->mStreamPos;
            break;
        }

        case SeekType::End: {
            finalPos = (pos + this->mSize) - 1;
            break;
        }
    }

    if (finalPos < 0) {
        return false;
    }

    this->mStreamPos = finalPos;
    return true;
}

asm u32 FixedMemoryStream::GetStreamPos() {
    nofralloc
    b fn_807010E0
}

void FixedMemoryStream::Reset() {
    mpData = NULL;
    mSize = 0;
    mStreamPos = 0;
}
