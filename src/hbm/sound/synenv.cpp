#include "synenv.h"

/*******************************************************************************
 * headers
 */

#include <math.h> // powf
#include <limits.h> // LONG_MIN

#include <types.h>

#include "syn.h"
#include "synctrl.h" // __HBMSYNn128
#include "synmix.h" // __HBMSYNAttackAttnTable
#include "synvoice.h" // HBMSYNVOICE

#if 0
#include <revolution/OS/OSAssert.h>
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * functions
 */

s32 __HBMSYNGetEnvelopeTime(s32 scale, s32 mod, u8 key)
{
	// idk what these numbers are for

	if (scale == LONG_MIN)
		return 0;

	if (mod == LONG_MIN)
		return powf(2.0f, scale / (65536.0f * 1200.0f)) * 1000.0f;

	return powf(2.0f, (mod * __HBMSYNn128[key] + scale) / (65535.0f * 1200.0f))
	     * 1000.0f;
}

void __HBMSYNSetupVolumeEnvelope(HBMSYNVOICE *voice)
{
	OSAssert_Line(38, voice);

	if (voice->art->eg1Attack == LONG_MIN)
	{
		voice->veState = VolEnvState_Decay;
		voice->veAttn = 0;

		if (voice->art->eg1Decay == LONG_MIN)
		{
			voice->veState = VolEnvState_Sustain;
			voice->veAttn = voice->art->eg1Sustain;
		}
	}
	else
	{
		s32 frames = __HBMSYNGetEnvelopeTime(voice->art->eg1Attack,
		                                     voice->art->eg1Vel2Attack,
		                                     voice->keyVel) / 3;

		if (frames)
		{
			// why are they in the upper half?
			voice->veAttack = 0;
			voice->veAttackDelta = (100 << 16) / frames;
			voice->veAttn = -(960 << 16);
			voice->veState = VolEnvState_Attack;
		}
		else
		{
			voice->veAttack = 0;
			voice->veAttackDelta = (100 << 16);
			voice->veAttn = -(960 << 16);
			voice->veState = VolEnvState_Attack;
		}
	}

	// attack or decay
	if (voice->veState < VolEnvState_Sustain)
	{
		s32 frames = __HBMSYNGetEnvelopeTime(voice->art->eg1Decay,
		                                     voice->art->eg1Key2Decay,
		                                     voice->keyNum) / 3;

		if (frames)
			voice->veDecay = -(960 << 16) / frames;
		else
			voice->veDecay = -(960 << 16);
	}

	voice->veSustain = voice->art->eg1Sustain;
	voice->veRelease = voice->art->eg1Release;
}

void __HBMSYNRunVolumeEnvelope(HBMSYNVOICE *voice)
{
	OSAssert_Line(101, voice);

	switch (voice->veState)
	{
	case VolEnvState_Attack:
		voice->veAttack += voice->veAttackDelta;

		if (voice->veAttack >= (99 << 16))
			voice->veAttn = 0;
		else
			voice->veAttn = __HBMSYNAttackAttnTable[voice->veAttack >> 16];

		if (voice->veAttn == (0 << 16))
			voice->veState = VolEnvState_Decay;

		break;

	case VolEnvState_Decay:
		voice->veAttn += voice->veDecay;

		if (voice->veAttn <= voice->veSustain)
		{
			voice->veAttn = voice->veSustain;
			voice->veState = VolEnvState_Sustain;
		}

		if (voice->veAttn <= -(720 << 16))
		{
			voice->veState = VolEnvState_End;
			voice->synth->voice[voice->midiChannel][voice->keyNum] = nullptr;
		}

		break;

	case VolEnvState_Sustain:
		// TODO: is this handled elsewhere?
		break;

	case VolEnvState_Release:
		if (voice->veAttn <= -(720 << 16))
			voice->veState = VolEnvState_End;
		else
			voice->veAttn += voice->veRelease;

		break;
	}
}

