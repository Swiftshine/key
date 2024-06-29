#ifndef RVL_SDK_OS_CACHE_H
#define RVL_SDK_OS_CACHE_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

void DCInvalidateRange(const void *buf, u32 len);
void DCStoreRange(const void *buf, u32 len);

#ifdef __cplusplus
}
#endif
#endif
