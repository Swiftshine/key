#ifndef RVL_SDK_HBM_SOUND_SYN_CTRL_H
#define RVL_SDK_HBM_SOUND_SYN_CTRL_H

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "syn.h"

/*******************************************************************************
 * external variables
 */

#ifdef __cplusplus
	extern "C" {
#endif

extern f32 __HBMSYNn128[];

/*******************************************************************************
 * functions
 */

void __HBMSYNSetController(HBMSYNSYNTH *synth, u8 midiChannel, u8 function,
                           u8 value);
void __HBMSYNResetAllControllers(HBMSYNSYNTH *synth);
void __HBMSYNRunInputBufferEvents(HBMSYNSYNTH *synth);
BOOL __HBMSYNGetWavetableData(HBMSYNVOICE *voice);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_HBM_SOUND_SYN_CTRL_H
