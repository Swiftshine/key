#ifndef RVL_SDK_HBM_SOUND_SYN_VOICE_H
#define RVL_SDK_HBM_SOUND_SYN_VOICE_H

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "syn.h"

#if 0
#include <revolution/AX/AX.h> // AXVPB
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * types
 */

// [SGLEA4]/GormitiDebug.elf:.debug_info::0x47e111
struct HBMSYNVOICE
{
	void		*next;			// size 0x04, offset 0x00
	AXVPB		*axvpb;			// size 0x04, offset 0x04
	HBMSYNSYNTH	*synth;			// size 0x04, offset 0x08
	u8			midiChannel;	// size 0x01, offset 0x0c
	u8			keyNum;			// size 0x01, offset 0x0d
	u8			keyVel;			// size 0x01, offset 0x0e
	u8			pan;			// size 0x01, offset 0x0f
	WTREGION	*region;		// size 0x04, offset 0x10
	WTART		*art;			// size 0x04, offset 0x14
	WTSAMPLE	*sample;		// size 0x04, offset 0x18
	WTADPCM		*adpcm;			// size 0x04, offset 0x1c
	u32			type;			// size 0x04, offset 0x20
	f32			srcRatio;		// size 0x04, offset 0x24
	s32			cents;			// size 0x04, offset 0x28
	s32			attn;			// size 0x04, offset 0x2c
	u32			veState;		// size 0x04, offset 0x30
	s32			veAttn;			// size 0x04, offset 0x34
	s32			veAttack;		// size 0x04, offset 0x38
	s32			veAttackDelta;	// size 0x04, offset 0x3c
	s32			veDecay;		// size 0x04, offset 0x40
	s32			veSustain;		// size 0x04, offset 0x44
	s32			veRelease;		// size 0x04, offset 0x48
}; // size 0x4c

/*******************************************************************************
 * functions
 */

#ifdef __cplusplus
	extern "C" {
#endif

void __HBMSYNClearVoiceReferences(void *p);
void __HBMSYNSetVoiceToRelease(HBMSYNVOICE *voice);
void __HBMSYNServiceVoice(int i);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_HBM_SOUND_SYN_VOICE_H
