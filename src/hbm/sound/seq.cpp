#include "seq.h"

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "syn.h"

#if 0
#include <revolution/OS/OSAssert.h>
#include <revolution/OS/OSInterrupt.h>
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * macros
 */

#define MIDI_TRACK_HEADER_MAGIC					'MThd'
#define MIDI_TRACK_MAGIC						'MTrk'

#define MIDI_MESSAGE_CHANNEL_MODE_MESSAGE		0xB0
#define MIDI_MESSAGE_SYSEX_BEGIN				0xF0
#define MIDI_MESSAGE_SYSEX_END					0xF7
#define MIDI_MESSAGE_META_EVENT					0xFF

#define MIDI_CHANNEL_MODE_MESSAGE_ALL_NOTES_OFF	0x7B

#define MIDI_META_EVENT_END_OF_TRACK			0x2F
#define MIDI_META_EVENT_SET_TEMPO				0x51

/*******************************************************************************
 * local function declarations
 */

static void __HBMSEQPushSequenceList(HBMSEQSEQUENCE *sequence);
static void __HBMSEQRemoveSequenceFromList(HBMSEQSEQUENCE *sequence);
static u32 __HBMSEQGetIntTrack(HBMSEQTRACK *track);
static void __HBMSEQHandleSysExEvent(HBMSEQTRACK *track);
static void __HBMSEQSetTicksPerFrame(HBMSEQTRACK *track, f32 bps);
static void __HBMSEQTempoMetaEvent(HBMSEQTRACK *track);
static void __HBMSEQTrackEnd(HBMSEQTRACK *track);
static void __HBMSEQHandleMetaEvent(HBMSEQTRACK *track);
static void __HBMSEQHandleSynthEvent(HBMSYNSYNTH *synth, HBMSEQTRACK *track);
static void __HBMSEQRunEvent(HBMSYNSYNTH *synth, HBMSEQTRACK *track);
static void __HBMSEQInitTracks(HBMSEQSEQUENCE *sequence, u8 *read, int tracks);
static void __HBMSEQReadHeader(HBMSEQSEQUENCE *sequence, u8 *midiHeader);

/*******************************************************************************
 * variables
 */

// .data
// clang-format off
static u8 __HBMSEQMidiEventLength[128] =
{
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,

	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

	2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,

	0, 0, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
// clang-format on

// .bss
static HBMSEQSEQUENCE *__HBMSEQSequenceList;
static BOOL __init;

/*******************************************************************************
 * functions
 */

static void __HBMSEQPushSequenceList(HBMSEQSEQUENCE *sequence)
{
	BOOL intrStatus = OSDisableInterrupts(); /* int old */

	if (__HBMSEQSequenceList)
		sequence->next = __HBMSEQSequenceList;
	else
		sequence->next = nullptr;

	__HBMSEQSequenceList = sequence;

	OSRestoreInterrupts(intrStatus);
}

static void __HBMSEQRemoveSequenceFromList(HBMSEQSEQUENCE *sequence)
{
	BOOL intrStatus = OSDisableInterrupts(); /* int old */
	HBMSEQSEQUENCE *thisSequence = __HBMSEQSequenceList;

	__HBMSEQSequenceList = nullptr;

	while (thisSequence)
	{
		HBMSEQSEQUENCE *next = thisSequence->next;

		if (thisSequence != sequence)
			__HBMSEQPushSequenceList(thisSequence);

		thisSequence = next;
	}

	OSRestoreInterrupts(intrStatus);
}

static u32 __HBMSEQGetIntTrack(HBMSEQTRACK *track)
{
	u32 value;

	OSAssert_Line(106, track);

	value = *track->current & 0x7f;

	while (*track->current & 0x80)
	{
		track->current++;

		value = (value << 7) + (*track->current & 0x7f);
	}

	track->current++;
	return value;
}

static void __HBMSEQHandleSysExEvent(HBMSEQTRACK *track)
{
	u32 length;

	OSAssert_Line(129, track);

	length = __HBMSEQGetIntTrack(track);
	track->current += length;
}

static void __HBMSEQSetTicksPerFrame(HBMSEQTRACK *track, f32 bps)
{
	HBMSEQSEQUENCE *sequence;

	OSAssert_Line(143, track);

	sequence = track->sequence;

	track->beatsPerSec = bps;
	track->ticksPerFrame =
		96.0f / (32000.0f / bps / sequence->timeFormat) * 65536.0f;
}

static void __HBMSEQTempoMetaEvent(HBMSEQTRACK *track)
{
	u32 data;
	f32 beatsPerSec;

	// back at it again
	data = *track->current; track->current++;
	data = (data << 8) + *track->current; track->current++;
	data = (data << 8) + *track->current; track->current++;

	beatsPerSec = 1000000.0f / data;

	__HBMSEQSetTicksPerFrame(track, beatsPerSec);
}

static void __HBMSEQTrackEnd(HBMSEQTRACK *track)
{
	HBMSEQSEQUENCE *sequence;

	OSAssert_Line(185, track);

	sequence = track->sequence;
	sequence->tracksRunning--;
	track->state = 0;

	if (!sequence->tracksRunning)
		sequence->end = 1;
}

static void __HBMSEQHandleMetaEvent(HBMSEQTRACK *track)
{
	u8 type;
	u32 length;

	OSAssert_Line(204, track);

	type = *track->current; track->current++;
	switch (type)
	{
	case MIDI_META_EVENT_END_OF_TRACK:
		__HBMSEQTrackEnd(track);
		break;

	case MIDI_META_EVENT_SET_TEMPO:
		length = __HBMSEQGetIntTrack(track); // assignment unnecessary?
		__HBMSEQTempoMetaEvent(track);
		break;

	default:
		length = __HBMSEQGetIntTrack(track);
		track->current += length;
		break;
	}
}

static void __HBMSEQHandleSynthEvent(HBMSYNSYNTH *synth, HBMSEQTRACK *track)
{
	u8 ch[3];
	u32 bytes;

	bytes = __HBMSEQMidiEventLength[track->status - 128];
	ch[0] = track->status;

	switch (bytes)
	{
	case 0:
		break;

	case 1:
		ch[1] = *track->current; track->current++;
		break;

	case 2:
		ch[1] = *track->current; track->current++;
		ch[2] = *track->current; track->current++;
		break;
	}

	HBMSYNMidiInput(synth, ch);
}

static void __HBMSEQRunEvent(HBMSYNSYNTH *synth, HBMSEQTRACK *track)
{
	u8 event;

	OSAssert_Line(280, synth);
	OSAssert_Line(281, track);

	event = *track->current;
	if (event >= 0x80)
	{
		track->status = event;
		track->current++;
	}

	switch (track->status)
	{
	case MIDI_MESSAGE_SYSEX_BEGIN:
	case MIDI_MESSAGE_SYSEX_END:
		__HBMSEQHandleSysExEvent(track);
		break;

	case MIDI_MESSAGE_META_EVENT:
		__HBMSEQHandleMetaEvent(track);
		break;

	default:
		__HBMSEQHandleSynthEvent(synth, track);
		break;
	}

	if (track->current >= track->end)
		__HBMSEQTrackEnd(track);
}

static void __HBMSEQInitTracks(HBMSEQSEQUENCE *sequence, u8 *read,
                               int tracks)
{
	int i = 0;
	u8 *p = read;

	for (; tracks; tracks--, (void)i++)
	{
		u32 chunk;
		u32 bytes;

	next_chunk:
		chunk = *(u32 *)p; p += sizeof(u32);
		bytes = *(u32 *)p; p += sizeof(u32);

		if (chunk == MIDI_TRACK_MAGIC)
		{
			HBMSEQTRACK *track = sequence->track + i;

			track->sequence = sequence;
			track->start = p;
			track->end = p + bytes;
			track->current = p;
			track->defaultTicksPerFrame =
				96.0f / (16000.0f / sequence->timeFormat) * 65536.0f;
			track->state = 0;

			p += bytes;
			continue;
		}
		else
		{
			p += bytes;
			goto next_chunk;
		}

	}
}

static void __HBMSEQReadHeader(HBMSEQSEQUENCE *sequence, u8 *midiStream)
{
	u8 *read = midiStream;
	u32 bytes;
	u32 fileType;

	OSAssertMessage_Line(383, *(u32 *)read == MIDI_TRACK_HEADER_MAGIC,
	                     "!!!midiStream is not a valid MIDI file\n!!!");
	read += sizeof(u32);

	bytes = *(u32 *)read; read += sizeof(u32);
	fileType = *(u16 *)read; read += sizeof(u16);
	sequence->nTracks = *(u16 *)read; read += sizeof(u16);
	sequence->timeFormat = *(s16 *)read; read += sizeof(s16);

	OSAssertMessage_Line(398, sequence->timeFormat >= 0,
	                     "!!!HBMSEQ does not support SMPTE time!!!\n");

	// the fields for fileType, sequence->nTracks, and sequence->timeFormat
	bytes -= sizeof(u16) + sizeof(u16) + sizeof(s16);
	read += bytes;

	switch (fileType)
	{
	case 0:
		sequence->nTracks = 1;
		__HBMSEQInitTracks(sequence, read, 1);
		break;

	case 1:
		OSAssertMessage_Line(420, sequence->nTracks < HBMSEQ_MAX_TRACKS,
		                     "exceeded HBMSEQ_MAX_TRACKS, please increase "
		                     "HBMSEQ_MAX_TRACKS\n");

		__HBMSEQInitTracks(sequence, read, sequence->nTracks);
		break;

	default:
		OSAssertMessage_Line(428, FALSE, "!!!Invalid MIDI file type\n!!!");
	}

	sequence->tracksRunning = sequence->nTracks;
}

void HBMSEQInit(void)
{
	if (!__init)
	{
		__HBMSEQSequenceList = nullptr;
		__init = TRUE;
	}
}

void HBMSEQQuit(void)
{
	__HBMSEQSequenceList = nullptr;
	__init = FALSE;
}

void HBMSEQRunAudioFrame(void)
{
	HBMSEQSEQUENCE *sequence = __HBMSEQSequenceList;

	if (!__init)
		return;

	for (; sequence; sequence = sequence->next)
	{
		if (sequence->state == 1 || sequence->state == 2)
		{
			for (u32 i = 0; i < sequence->nTracks; i++)
			{
				HBMSEQTRACK *track = &sequence->track[i];

				if (track->state == 1 || track->state == 2)
				{
					u32 ticks = track->ticksPerFrame;

					if (track->delay > ticks)
					{
						track->delay -= ticks;
						continue;
					}

					while (ticks >= track->delay)
					{
						ticks -= track->delay;

						__HBMSEQRunEvent(&sequence->synth, track);

						if (track->state == 0)
							break;

						track->delay = __HBMSEQGetIntTrack(track) << 16;
					}

					track->delay -= ticks;
				}
			}
		}

		if (sequence->end)
		{
			if (sequence->state == 2)
			{
				HBMSEQSetState(sequence, 0);
				HBMSEQSetState(sequence, 2);
			}
			else
			{
				HBMSEQSetState(sequence, 0);
			}
		}
	}
}

void HBMSEQAddSequence(HBMSEQSEQUENCE *sequence, u8 *midiStream,
                       u8 *wavetable, u8 *samples, u8 *zerobuffer)
{
	OSAssert_Line(551, sequence);
	OSAssert_Line(552, midiStream);
	OSAssert_Line(553, wavetable);
	OSAssert_Line(554, samples);

	HBMSYNInitSynth(&sequence->synth, wavetable, samples, zerobuffer);
	sequence->state = 0;
	__HBMSEQReadHeader(sequence, midiStream);
	__HBMSEQPushSequenceList(sequence);
}

void HBMSEQRemoveSequence(HBMSEQSEQUENCE *sequence)
{
	OSAssert_Line(581, sequence);

	__HBMSEQRemoveSequenceFromList(sequence);
	HBMSYNQuitSynth(&sequence->synth);
}

void HBMSEQSetState(HBMSEQSEQUENCE *sequence, u32 state)
{
	int i;

	OSAssert_Line(598, sequence);

	switch (state)
	{
	case 1:
	case 2:
		if (sequence->state == 0)
		{
			BOOL intrStatus = OSDisableInterrupts(); /* int old */

			for (i = 0; i < sequence->nTracks; i++)
			{
				HBMSEQTRACK *track = &sequence->track[i];

				track->current = track->start;
				track->ticksPerFrame = track->defaultTicksPerFrame;
				track->delay = __HBMSEQGetIntTrack(track) << 16;
				track->state = 1;
			}
			sequence->tracksRunning = sequence->nTracks;

			OSRestoreInterrupts(intrStatus);
		}

		sequence->end = 0;
		break;

	case 0:
	case 3:
		for (i = 0; i < NUM_MIDI_CHANNELS; i++)
		{
			BOOL intrStatus = OSDisableInterrupts(); /* int old */

			u8 ch[3];
			ch[0] = MIDI_MESSAGE_CHANNEL_MODE_MESSAGE | i;
			ch[1] = MIDI_CHANNEL_MODE_MESSAGE_ALL_NOTES_OFF;
			ch[2] = 0; // v = 0 -> all notes off

			HBMSYNMidiInput(&sequence->synth, ch);

			OSRestoreInterrupts(intrStatus);
		}

		break;
	}

	sequence->state = state;
}

u32 HBMSEQGetState(HBMSEQSEQUENCE *sequence)
{
	OSAssert_Line(666, sequence);

	return sequence->state;
}

void HBMSEQSetVolume(HBMSEQSEQUENCE *sequence, s32 dB)
{
	OSAssert_Line(677, sequence);

	HBMSYNSetMasterVolume(&sequence->synth, dB);
}
