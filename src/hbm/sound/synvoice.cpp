#include "synvoice.h"

/*******************************************************************************
 * headers
 */

#include <types.h> // nullptr

#include "mix.h"
#include "syn.h"
#include "synenv.h"
#include "synmix.h" // __HBMSYNUpdateMix
#include "synpitch.h" // __HBMSYNUpdateSrc

#if 0
#include <revolution/OS/OSAssert.h>
#include <revolution/AX.h>
#endif

/*******************************************************************************
 * functions
 */

void __HBMSYNClearVoiceReferences(void *p)
{
	AXVPB *axvpb;
	HBMSYNSYNTH *synth;
	HBMSYNVOICE *voice;
	int index;

	OSAssert_Line(27, p);

	axvpb = (AXVPB *)p;
	synth = (HBMSYNSYNTH *)axvpb->userContext;

	index = HBMGetIndex(axvpb->index);
	HBMFreeIndex(index);

	voice = __HBMSYNVoice + index;
	HBMMIXReleaseChannel(axvpb);

	if (synth->voice[voice->midiChannel][voice->keyNum] == voice)
		synth->voice[voice->midiChannel][voice->keyNum] = nullptr;

	voice->synth = nullptr;
	synth->notes--;
}

void __HBMSYNSetVoiceToRelease(HBMSYNVOICE *voice)
{
	OSAssert_Line(53, voice);

	voice->veState = VolEnvState_Release;
}

void __HBMSYNServiceVoice(int i)
{
	HBMSYNVOICE *voice = __HBMSYNVoice + i;
	HBMSYNSYNTH *synth = voice->synth;

	if (!synth)
		return;

	if (voice->type == 0 && voice->axvpb->pb.state == 0)
	{
		if (synth->voice[voice->midiChannel][voice->keyNum] == voice)
			synth->voice[voice->midiChannel][voice->keyNum] = nullptr;

		voice->veState = VolEnvState_End;
	}

	__HBMSYNRunVolumeEnvelope(voice);

	if (voice->veState == VolEnvState_End)
	{
		voice->synth = nullptr;

		HBMMIXReleaseChannel(voice->axvpb);
		HBMFreeIndexByKey(voice->axvpb->index);
		AXFreeVoice(voice->axvpb);

		synth->notes--;
	}
	else
	{
		__HBMSYNUpdateMix(voice);
		__HBMSYNUpdateSrc(voice);
	}
}
