#ifndef RVL_SDK_HBM_SOUND_SYN_PITCH_H
#define RVL_SDK_HBM_SOUND_SYN_PITCH_H

/*******************************************************************************
 * headers
 */

#include <revolution/types.h> // f32

#include "synvoice.h" // HBMSYNVOICE

/*******************************************************************************
 * functions
 */

#ifdef __cplusplus
	extern "C" {
#endif

f32 __HBMSYNGetRelativePitch(HBMSYNVOICE *voice);
void __HBMSYNSetupPitch(HBMSYNVOICE *voice);
void __HBMSYNSetupSrc(HBMSYNVOICE *voice);
void __HBMSYNUpdateSrc(HBMSYNVOICE *voice);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_HBM_SOUND_SYN_PITCH_H
