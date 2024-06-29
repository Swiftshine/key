#ifndef RVL_SDK_SC_SCAPI_H
#define RVL_SDK_SC_SCAPI_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum { 
    SC_ASPECT_STD, 
    SC_ASPECT_WIDE 
} SCAspectRatio;

u8 SCGetAspectRatio(void);

#ifdef __cplusplus
}
#endif
#endif
