#ifndef FLUFF_MSGMNG_H
#define FLUFF_MSGMNG_H

#include <vector>
#include <string>
#include "types.h"

/// @note Given that there are no nonstatic methods that are actually used,
/// most of the functionality of this class may have been cut.
class FlfMsgMng {
public:
    static FlfMsgMng* sInstance;

    FlfMsgMng();
    virtual ~FlfMsgMng();

    /* Static Methods */

    static void InitInstance();
    static void DestroyInstance();
    static void ReleaseAll() DONT_INLINE_CLASS;
    /// @brief Splits a formatted identifier list into a vector of individual identifiers.
    /// @param pIdentifierList The formatted identifier list. E.g. "ident1;ident2;ident3;"
    /// @param rDest The destination vector.
    static void SplitIdentifiers(const char* pIdentifierList, std::vector<std::string>& rDst);

    /* Class Members */

    std::vector<pvd8_t*> m_4;
};

#endif
