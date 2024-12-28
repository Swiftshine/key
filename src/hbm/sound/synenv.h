#ifndef RVL_SDK_HBM_SOUND_SYN_ENV_H
#define RVL_SDK_HBM_SOUND_SYN_ENV_H

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "syn.h" // HBMSYNVOICE

/*******************************************************************************
 * types
 */

#ifdef __cplusplus
	extern "C" {
#endif

// deduced
enum VolumeEnvelopeStages
{
	VolEnvState_Attack,
	VolEnvState_Decay,
	VolEnvState_Sustain,
	VolEnvState_Release,

	VolEnvState_End
};

/*******************************************************************************
 * functions
 */

s32 __HBMSYNGetEnvelopeTime(s32 scale, s32 mod, u8 key);
void __HBMSYNSetupVolumeEnvelope(HBMSYNVOICE *voice);
void __HBMSYNRunVolumeEnvelope(HBMSYNVOICE *voice);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_HBM_SOUND_SYN_ENV_H
