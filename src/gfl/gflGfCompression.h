#ifndef GFL_GFCOMPRESSION_H
#define GFL_GFCOMPRESSION_H

#include "gflGfArch.h"


namespace gfl {

class GfCompressionWrapper {
public:
    DECL_WEAK GfCompressionWrapper(void* pData);
    DECL_WEAK ~GfCompressionWrapper();

    size_t GetDecompressedSize();
    size_t GetCompressedSize();
private:
    GfArch::CompressionHeader* mHeader;
};

}


#endif
