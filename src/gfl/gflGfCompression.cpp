#include "gflGfCompression.h"

using namespace gfl;

inline size_t SwapEndianness32(size_t value) {
    size_t dst;

    *((u8*)&dst + 0) = *((u8*)&value + 3);
    *((u8*)&dst + 1) = *((u8*)&value + 2);
    *((u8*)&dst + 2) = *((u8*)&value + 1);
    *((u8*)&dst + 3) = *((u8*)&value + 0);

    return dst;
}

size_t GfCompressionWrapper::GetDecompressedSize() {
    return SwapEndianness32(mHeader->mDecompressedDataSize);
}

size_t GfCompressionWrapper::GetCompressedSize() {
    return SwapEndianness32(mHeader->mCompressedDataSize);
}

