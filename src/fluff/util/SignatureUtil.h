#ifndef FLUFF_SIGNATUREUTIL_H
#define FLUFF_SIGNATUREUTIL_H

#include "types.h"
#include <string>

namespace SignatureUtil {
    u32 GetSignature(const std::string& rStr);
    std::string GetSignature(u32 src);
    void GetSignature(u32 src, char* pDst1, char* pDst2, char* pDst3, char* pDst4);
}

// listed are the different signature types seen in structures related to game work
// A___ = Area [number]
// E___ = Environment [number]
// SN__ = Stage (Normal) [number]
// SB__ = Stage (Boss) [number]
// C___ = ?

#endif
