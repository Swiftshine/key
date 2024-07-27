#include <gfl/mem/FixedMemoryStream.h>
#include <decomp/thunks.h>
#include <gfl/mem/Mem.h>

using namespace gfl;

FixedMemoryStream::FixedMemoryStream(u8* addr, u32 newSize) {
    data = addr;
    size = newSize;
    streamPos = 0;
}

asm FixedMemoryStream::~FixedMemoryStream(void) {
    nofralloc
    b common_dtor
}

u32 FixedMemoryStream::Read(u8* dst, u32 count) {
    u32 remain;
    u8* offs;
    
    if (this->streamPos == this->size) {
        return 0;
    }
        
    offs = (u8*)this->data + this->streamPos;
    remain = this->size - this->streamPos;
    count = (remain < count) ? remain : count;

    memcpy(dst, offs, count);
    this->streamPos += count;
    return count;
}


u32 FixedMemoryStream::Write(u8* src, u32 count) {
    u32 remain;
    u8* offs;
    
    if (this->streamPos >= this->size) {
        return 0;
    }
        
    offs = (u8*)this->data + this->streamPos;
    remain = this->size - this->streamPos;
    count = (remain < count) ? remain : count;

    memcpy(offs, src, count);
    this->streamPos += count;
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
            finalPos = pos + this->streamPos;
            break;
        }

        case SeekType::End: {
            finalPos = (pos + this->size) - 1;
            break;
        }
    }

    if (finalPos < 0) {
        return false;
    }

    this->streamPos = finalPos;
    return true;
}

asm u32 FixedMemoryStream::GetStreamPos() {
    nofralloc
    b fn_807010E0
}

void FixedMemoryStream::Reset() {
    data = NULL;
    size = 0;
    streamPos = 0;
}

