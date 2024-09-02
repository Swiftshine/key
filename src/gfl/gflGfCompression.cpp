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

size_t GfCompression::GetDecompressedSize(GfArch::CompressionHeader** header) {
    return SwapEndianness32((*header)->mDecompressedDataSize);
}

size_t GfCompression::GetCompressedSize(GfArch::CompressionHeader** header) {
    return SwapEndianness32((*header)->mCompressedDataSize);
}

