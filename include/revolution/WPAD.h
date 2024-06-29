#ifndef RVL_SDK_WPAD_H
#define RVL_SDK_WPAD_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef void (*WPADCallback)(s32, s32);
typedef void *(*WPADAlloc)(u32);
typedef u8 (*WPADFree)(void *);

typedef enum {
    WPAD_CHAN_0,
    WPAD_CHAN_1,
    WPAD_CHAN_2,
    WPAD_CHAN_3,
    WPAD_MAX_CONTROLLERS
} WPADChan;

typedef enum {
    WPAD_RESULT_ERR_3 = -3,
    WPAD_RESULT_ERR_2,
    WPAD_RESULT_ERR_1,

    WPAD_RESULT_SUCCESS = 0,
} WPADResult;

typedef struct DPDObject {
    s16 x;
    s16 y;
    u16 size;
    u8 traceId;
} DPDObject;

typedef struct WPADStatus {
    u16 button;
    s16 accX;
    s16 accY;
    s16 accZ;
    DPDObject obj[4];
    u8 dev;
    s8 err;
} WPADStatus;

typedef struct WPADFSStatus {
    u16 button;
    s16 accX;
    s16 accY;
    s16 accZ;
    DPDObject obj[4];
    u8 dev;
    s8 err;
    s16 fsAccX;
    s16 fsAccY;
    s16 fsAccZ;
    s8 fsStickX;
    s8 fsStickY;
} WPADFSStatus;

typedef struct WPADCLStatus {
    u16 button;
    s16 accX;
    s16 accY;
    s16 accZ;
    DPDObject obj[4];
    u8 dev;
    s8 err;
    u16 clButton;
    s16 clLStickX;
    s16 clLStickY;
    s16 clRStickX;
    s16 clRStickY;
    u8 clTriggerL;
    u8 clTriggerR;
} WPADCLStatus;

typedef struct WPADInfo {
    BOOL dpd;
    BOOL speaker;
    BOOL attach;
    BOOL lowBat;
    BOOL nearempty;
    u8 battery;
    u8 led;
    u8 protocol;
    u8 firmware;
} WPADInfo;

void WPADRegisterAllocator(WPADAlloc, WPADFree);
u32 WPADGetWorkMemorySize(void);

u8 WPADGetSensorBarPosition(void);

s32 WPADProbe(s32 chan, u32 *type);

void WPADControlMotor(s32 chan, u32 onOff);

s32 WPADGetInfoAsync(s32, WPADInfo *, WPADCallback);

#ifdef __cplusplus
}
#endif
#endif
