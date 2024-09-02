#ifndef GFL_GFCOMPRESSION_H
#define GFL_GFCOMPRESSION_H

#include "gflGfArch.h"


namespace gfl {
namespace GfCompression {
    size_t GetDecompressedSize(GfArch::CompressionHeader** header);
    size_t GetCompressedSize(GfArch::CompressionHeader** header);  
}
}


#endif