#ifndef RVL_SDK_HBM_SOUND_SEQ_H
#define RVL_SDK_HBM_SOUND_SEQ_H

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "syn.h" // HBMSYNSYNTH

/*******************************************************************************
 * macros
 */

#define HBMSEQ_MAX_TRACKS	64

/*******************************************************************************
 * types
 */

#ifdef __cplusplus
	extern "C" {
#endif

typedef struct _HBMSEQSEQUENCE HBMSEQSEQUENCE;

// [SGLEA4]/GormitiDebug.elf:.debug_info::0x47e2db
typedef struct _HBMSEQTRACK
{
	HBMSEQSEQUENCE	*sequence;				// size 0x04, offset 0x00
	u8			*start;					// size 0x04, offset 0x04
	u8			*end;					// size 0x04, offset 0x08
	u8			*current;				// size 0x04, offset 0x0c
	u8				status;					// size 0x01, offset 0x10
	/* 3 bytes padding */
	f32				beatsPerSec;			// size 0x04, offset 0x14
	u32				defaultTicksPerFrame;	// size 0x04, offset 0x18
	u32				ticksPerFrame;			// size 0x04, offset 0x1c
	u32				delay;					// size 0x04, offset 0x20
	u32				state;					// size 0x04, offset 0x24
} HBMSEQTRACK; // size 0x28

// [SGLEA4]/GormitiDebug.elf:.debug_info::0x47da61
struct _HBMSEQSEQUENCE
{
	HBMSEQSEQUENCE	*next;						// size 0x0004, offset 0x0000
	u32				state;						// size 0x0004, offset 0x0004
	u16				nTracks;					// size 0x0002, offset 0x0008
	s16				timeFormat;					// size 0x0002, offset 0x000a
	u32				tracksRunning;				// size 0x0004, offset 0x000c
	u32				end;						// size 0x0004, offset 0x0010
	HBMSYNSYNTH		synth;						// size 0x2408, offset 0x0014
	HBMSEQTRACK		track[HBMSEQ_MAX_TRACKS];	// size 0x0a00, offset 0x241c
}; // size 0x2e1c

/*******************************************************************************
 * functions
 */

void HBMSEQInit(void);
void HBMSEQQuit(void);

void HBMSEQRunAudioFrame(void);
void HBMSEQAddSequence(HBMSEQSEQUENCE *sequence, u8 *midiStream,
                       u8 *wavetable, u8 *samples, u8 *zerobuffer);
void HBMSEQRemoveSequence(HBMSEQSEQUENCE *sequence);
void HBMSEQSetState(HBMSEQSEQUENCE *sequence, u32 state);
u32 HBMSEQGetState(HBMSEQSEQUENCE *sequence);
void HBMSEQSetVolume(HBMSEQSEQUENCE *sequence, s32 dB);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_HBM_SOUND_SEQ_H
