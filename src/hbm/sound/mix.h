#ifndef RVL_SDK_HBM_SOUND_MIX_H
#define RVL_SDK_HBM_SOUND_MIX_H

/*******************************************************************************
 * headers
 */

#include <types.h>

#if 0
#include <revolution/AX/AXVPB.h>
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * types
 */

typedef u32 HBMMIXSoundMode;
enum HBMMIXSoundMode_et
{
	HBMMIX_SOUND_MODE_MONO,
	HBMMIX_SOUND_MODE_STEREO,
	HBMMIX_SOUND_MODE_DPL2,
};

typedef u32 HBMMIXKey;
#define	HBMMIX_KEY_NULL		-1

typedef int HBMMIXIndex;
#define	HBMMIX_INDEX_NULL	-1

/*******************************************************************************
 * functions
 */

#ifdef __cplusplus
	extern "C" {
#endif

void HBMMIXInit(void);
void HBMMIXQuit(void);

void HBMMIXSetSoundMode(HBMMIXSoundMode mode);

void HBMMIXInitChannel(AXVPB *axvpb, int input, int auxA, int pan, int fader);
void HBMMIXReleaseChannel(AXVPB *axvpb);

void HBMMIXSetInput(AXVPB *p, int dB);
void HBMMIXSetAuxA(AXVPB *p, int dB);
void HBMMIXSetPan(AXVPB *p, int pan);
void HBMMIXSetFader(AXVPB *p, int dB);
void HBMMIXUpdateSettings(void);

HBMMIXIndex HBMAllocIndex(HBMMIXKey key);
HBMMIXIndex HBMGetIndex(HBMMIXKey key);
void HBMFreeIndex(HBMMIXIndex index);
void HBMFreeIndexByKey(HBMMIXKey key);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_HBM_SOUND_MIX_H
