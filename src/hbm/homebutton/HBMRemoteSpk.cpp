#include "HBMRemoteSpk.hpp"

/*******************************************************************************
 * headers
 */

#include <macros.h>
#include <types.h>

#if 0
#include <revolution/OS/OSAlarm.h>
#include <revolution/OS/OSInterrupt.h>
#include <revolution/OS/OSTime.h>
#include <revolution/ARC/arc.h>
#include <revolution/WENC/wenc.h>
#include <revolution/WPAD/WPAD.h>
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * local function declarations
 */

namespace homebutton
{
	static bool MakeVolumeData(const s16 *src, s16 *dst, int vol, u32 size);
} // namespace homebutton

/*******************************************************************************
 * variables
 */

namespace homebutton
{
	// .bss
	RemoteSpk *RemoteSpk::spInstance;
} // namespace homebutton

/*******************************************************************************
 * functions
 */

namespace homebutton {

void RemoteSpk::SetInstance(RemoteSpk *pThis)
{
	spInstance = pThis;
}

RemoteSpk *RemoteSpk::GetInstance(void)
{
	return spInstance;
}

void RemoteSpk::GetPCMFromSeID(int in_ID, s16 *&out_wave, int &out_length)
{
	ARCFileInfo af;
	ARCFastOpen(&handle, in_ID, &af);

	out_wave = static_cast<s16 *>(ARCGetStartAddrInMem(&af));
	out_length = ARCGetLength(&af);

	ARCClose(&af);
}

static bool MakeVolumeData(const s16 *src, s16 *dst, int vol, u32 size)
{
	u32 enc_size = size <= 40 ? size : 40;
	for (int i = 0; (u32)i < enc_size; i++)
		*dst++ = static_cast<s16>(*src++ * vol / 10);

	if (size > 40)
		return false;

	u32 zero_size = 40 - size;
	for (int i = 0; (u32)i < zero_size; i++)
		*dst++ = 0;

	return true;
}

void RemoteSpk::UpdateSpeaker(OSAlarm *, OSContext *)
{
	s16 pcmBuffer[40];
	u8 adpcmBuffer[20];

	if (!GetInstance())
		return;

	ChanInfo *pinfo = GetInstance()->info;
	for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++, pinfo++)
	{
		if (pinfo->in_pcm && WPADIsSpeakerEnabled(i))
		{
			BOOL intrStatus = OSDisableInterrupts(); /* int intr */

			if (WPADCanSendStreamData(i))
			{
				MakeVolumeData(pinfo->in_pcm, pcmBuffer, pinfo->vol,
				               static_cast<u32>(pinfo->length) / sizeof(s16));
				WENCGetEncodeData(&pinfo->wencinfo, pinfo->first ? 0 : 1,
				                  pcmBuffer, 40, adpcmBuffer);
				WPADSendStreamData(i, adpcmBuffer, 20);

				pinfo->first = false;
				pinfo->cannotSendCnt = 0;
				pinfo->in_pcm += 40;
				pinfo->length -= 40 * sizeof(s16);

				if (pinfo->length <= 0)
				{
					pinfo->seId = -1;
					pinfo->in_pcm = nullptr;
				}
			}
			else
			{
				pinfo->cannotSendCnt++;

				if (pinfo->cannotSendCnt > 60)
					pinfo->in_pcm = nullptr;
			}

			OSRestoreInterrupts(intrStatus);
		}
	}
}

void RemoteSpk::ClearPcm(void)
{
	for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++)
	{
		info[i].in_pcm = nullptr;
		info[i].seId = -1;
	}
}

RemoteSpk::RemoteSpk(void *spkSeBuf)
{
	SetInstance(this);

	if (spkSeBuf)
		available = ARCInitHandle(spkSeBuf, &handle);
	else
		available = false;

	OSCreateAlarm(&speakerAlarm);
	for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++)
	{
		OSCreateAlarm(&info[i].alarm);
		info[i].in_pcm = nullptr;
		info[i].seId = -1;
		info[i].first = true;
		info[i].playReady = true;
	}
}

RemoteSpk::~RemoteSpk(void)
{
	SetInstance(nullptr);
	available = false;

	OSCancelAlarm(&speakerAlarm);

	for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++)
		OSCancelAlarm(&info[i].alarm);
}

void RemoteSpk::Start(void)
{
	if (!available)
		return;

	OSCreateAlarm(&speakerAlarm);
	OSSetPeriodicAlarm(&speakerAlarm, OSGetTime(),
	                   OSNanosecondsToTicks(6666667), &UpdateSpeaker);

	for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++)
	{
		OSCreateAlarm(&info[i].alarm);

		info[i].in_pcm = nullptr;
		info[i].seId = -1;
		info[i].first = true;
		info[i].playReady = true;
	}
}

void RemoteSpk::Stop(void)
{
	OSCancelAlarm(&speakerAlarm);

	for (int i = 0; i < WPAD_MAX_CONTROLLERS; i++)
		OSCancelAlarm(&info[i].alarm);
}

void RemoteSpk::DelaySpeakerOnCallback(OSAlarm *alarm, OSContext *)
{
	WPADChannel chan = OSGetAlarmUserDataAny(WPADChannel, alarm);
	WPADResult result ATTR_UNUSED =
		WPADControlSpeaker(chan, WPAD_SPEAKER_ENABLE, &SpeakerOnCallback);
}

void RemoteSpk::SpeakerOnCallback(WPADChannel chan, WPADResult result)
{
	RemoteSpk *pRmtSpk = GetInstance();
	if (!pRmtSpk)
		return;

	switch (result)
	{
	case WPAD_ESUCCESS:
		pRmtSpk->info[chan].first = true;
		result =
			WPADControlSpeaker(chan, WPAD_SPEAKER_PLAY, &SpeakerPlayCallback);
		break;

	case WPAD_ERR_3:
		pRmtSpk->info[chan].playReady = false;
		break;

	case WPAD_ECOMM:
		OSSetAlarmUserDataAny(&pRmtSpk->info[chan].alarm, chan);
		OSCancelAlarm(&pRmtSpk->info[chan].alarm);
		OSSetAlarm(&pRmtSpk->info[chan].alarm, OSMillisecondsToTicks(50),
		           &DelaySpeakerOnCallback);
		break;
	}
}

void RemoteSpk::DelaySpeakerPlayCallback(OSAlarm *alarm, OSContext *)
{
	WPADChannel chan = OSGetAlarmUserDataAny(WPADChannel, alarm);
	WPADResult result ATTR_UNUSED =
		WPADControlSpeaker(chan, WPAD_SPEAKER_PLAY, &SpeakerPlayCallback);
}

void RemoteSpk::SpeakerPlayCallback(WPADChannel chan, WPADResult result)
{
	RemoteSpk *pRmtSpk = GetInstance();
	if (!pRmtSpk)
		return;

	switch (result)
	{
	case WPAD_ESUCCESS:
		pRmtSpk->info[chan].playReady = true;
		break;

	case WPAD_ERR_3:
		pRmtSpk->info[chan].playReady = false;
		break;

	case WPAD_ENODEV:
		pRmtSpk->info[chan].playReady = false;
		break;

	case WPAD_ECOMM:
		OSSetAlarmUserDataAny(&pRmtSpk->info[chan].alarm, chan);
		OSCancelAlarm(&pRmtSpk->info[chan].alarm);
		OSSetAlarm(&pRmtSpk->info[chan].alarm, OSMillisecondsToTicks(50),
		           &DelaySpeakerPlayCallback);
		break;
	}
}

void RemoteSpk::Connect(WPADChannel chan)
{
	if (!available)
		return;

	// int?
	int result ATTR_UNUSED =
		WPADControlSpeaker(chan, WPAD_SPEAKER_ENABLE, &SpeakerOnCallback);

	u32 *p = reinterpret_cast<u32 *>(info[chan].wencinfo.data);
	for (int i = 8; i > 0; i--, p++)
		*p = 0;

	info[chan].first = true;
	info[chan].playReady = false;
}

void RemoteSpk::Play(WPADChannel chan, int seID, s8 vol)
{
	if (!available)
		return;

	s16 *pcm;
	int length;
	GetPCMFromSeID(seID, pcm, length);

	info[chan].cannotSendCnt = 0;
	info[chan].seId = seID;
	info[chan].length = length;
	info[chan].vol = vol;
	info[chan].in_pcm = pcm;
}

bool RemoteSpk::isPlaying(WPADChannel chan) const
{
	return info[chan].in_pcm != nullptr;
}

bool RemoteSpk::isPlayingId(WPADChannel chan, int seId) const
{
	if (isPlaying(chan) && info[chan].seId == seId)
		return true;
	else
		return false;
}

bool RemoteSpk::isPlayReady(WPADChannel chan) const
{
	return info[chan].playReady != false;
}

} // namespace homebutton
