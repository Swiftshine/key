#ifndef RVL_SDK_KPAD_H
#define RVL_SDK_KPAD_H
#include <revolution/types.h>
#include <revolution/MTX.h>
#include <revolution/WPAD.h>
#ifdef __cplusplus
extern "C" {
#endif


typedef struct Vec2 {
    f32 x;
    f32 y;
} Vec2; 

typedef union KPADEXStatus {
  struct {
    Vec2 stick;
    Vec acc;
    f32 acc_value;
    f32 acc_speed;
  } fs;
  struct {
    u32 hold;
    u32 trig;
    u32 release;
    Vec2 lstick;
    Vec2 rstick;
    f32 ltrigger;
    f32 rtrigger;
  } cl;
} KPADEXStatus;

typedef struct KPADStatus {
    u32 hold;
    u32 trig;
    u32 release;
    Vec acc;
    f32 acc_value;
    f32 acc_speed;
    Vec2 pos;
    Vec2 vec;
    f32 speed;
    Vec2 horizon;
    Vec2 hori_vec;
    f32 hori_speed;
    f32 dist;
    f32 dist_vec;
    f32 dist_speed;
    Vec2 acc_vertical;
    u8 dev_type;
    s8 wpad_err;
    s8 dpd_valid_fg;
    u8 data_format;
    KPADEXStatus ex_status;
} KPADStatus;

typedef struct KPADUnifiedWpadStatus {
  union {
    WPADStatus core;
    WPADFSStatus fs;
    WPADCLStatus cl;
  } u;
  u8 fmt;
  u8 padding;
} KPADUnifiedWpadStatus;

void KPADInit();


void KPADSetPosParam(s32 chan, f32 radius, f32 sensitivity);
void KPADSetSensorHeight(s32, f32);
s32 KPADRead(s32 chan, KPADStatus status[], u32 size);
void KPADGetUnifiedWpadStatus(s32 chan, KPADUnifiedWpadStatus status[], u32 size);

#ifdef __cplusplus
}
#endif
#endif
