#ifndef FLUFF_SIGNATUREUTIL_H
#define FLUFF_SIGNATUREUTIL_H

#include "types.h"
#include <string>

namespace SignatureUtil {
    uint GetSignature(const std::string& rStr);
    std::string GetSignature(uint src);
    void GetSignature(uint src, char* pDst1, char* pDst2, char* pDst3, char* pDst4);
}

// listed are the different signature types seen in structures related to game work
// A___ = Area [number]
// E___ = Environment [number]
// SN__ = Stage (Normal) [number]
// SB__ = Stage (Boss) [number]
// C___ = ?

#endif
