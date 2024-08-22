#include "gflFixedMemoryStream.h"
#include <cstring>

using namespace gfl;

FixedMemoryStream::FixedMemoryStream(void* addr, size_t newSize) {
    mData = addr;
    mSize = newSize;
    mStreamPos = 0;
}

FixedMemoryStream::~FixedMemoryStream(void) {

}

size_t FixedMemoryStream::Read(void* dst, size_t count) {
    size_t remain;
    void* offs;
    
    if (this->mStreamPos == this->mSize) {
        return 0;
    }
        
    offs = (void*)((u8*)this->mData + this->mStreamPos);
    remain = this->mSize - this->mStreamPos;
    count = (remain < count) ? remain : count;

    memcpy(dst, offs, count);
    this->mStreamPos += count;
    return count;
}


size_t FixedMemoryStream::Write(void* src, size_t count) {
    size_t remain;
    void* offs;
    
    if (this->mStreamPos >= this->mSize) {
        return 0;
    }
        
    offs = (void*)((u8*)this->mData + this->mStreamPos);
    remain = this->mSize - this->mStreamPos;
    count = (remain < count) ? remain : count;

    memcpy(offs, src, count);
    this->mStreamPos += count;
    return count;
}

bool FixedMemoryStream::Seek(size_t pos, int seekType) {
    signed long finalPos = 0;

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

size_t FixedMemoryStream::GetStreamPos() {
    return mStreamPos;
}

void FixedMemoryStream::Reset() {
    mData = NULL;
    mSize = 0;
    mStreamPos = 0;
}