#ifndef RVL_SDK_DVD_H
#define RVL_SDK_DVD_H
#include <revolution/types.h>
#include <revolution/OS.h>
//#include <revolution/ESP.h>
#ifdef __cplusplus
extern "C" {
#endif

#define DVD_STATE_FATAL_ERROR -1
#define DVD_STATE_END 0
#define DVD_STATE_BUSY 1
#define DVD_STATE_WAITING 2
#define DVD_STATE_COVER_CLOSED 3 //deprecated for wii
#define DVD_STATE_NO_DISK 4
#define DVD_STATE_COVER_OPEN 5 //deprecated for wii
#define DVD_STATE_WRONG_DISK 6
#define DVD_STATE_MOTOR_STOPPED 7
#define DVD_STATE_PAUSING 8
#define DVD_STATE_IGNORED 9
#define DVD_STATE_CANCELED 10
#define DVD_STATE_RETRY 11
#define DVD_STATE_12 12

#define DVD_RESULT_GOOD 0
#define DVD_RESULT_FATAL_ERROR -1
#define DVD_RESULT_IGNORED -2
#define DVD_RESULT_CANCELED -3

typedef struct DVDDiskID;
typedef struct DVDCommandBlock;

typedef void (*DVDCBAsyncCallback)(s32, struct DVDCommandBlock *);

typedef struct DVDCommandBlock {
    struct DVDCommandBlock* next;
    struct DVDCommandBlock* prev;
    u32 command;
    s32 state;
    u32 offset;
    u32 length;
    void* addr;
    u32 currTransferSize;
    u32 transferredSize;
    struct DVDDiskID* id;
    DVDCBAsyncCallback callback;
    void* userData;
} DVDCommandBlock;


void DVDInit(void);
u32 DVDGetDriveStatus(void);

#ifdef __cplusplus
}
#endif
#endif