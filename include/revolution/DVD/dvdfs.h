#ifndef RVL_SDK_DVD_FS_H
#define RVL_SDK_DVD_FS_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct DVDFileInfo;

typedef void (*DVDAsyncCallback)(s32, struct DVDFileInfo *);

extern BOOL __DVDLongFileNameFlag;

typedef struct DVDFileInfo {
    DVDCommandBlock cb;
    u32 startAddr;
    u32 length;
    DVDAsyncCallback callback;
} DVDFileInfo;

BOOL DVDOpen(const char *fileName, DVDFileInfo *fileInfo);

s32 DVDReadAsyncPrio(DVDFileInfo *fileInfo, void *addr, s32 length, s32 offset, DVDAsyncCallback callback, s32 prio);

#ifdef __cplusplus
}
#endif
#endif
