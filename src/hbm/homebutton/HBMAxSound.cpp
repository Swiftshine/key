#include "HBMAxSound.hpp"

/*******************************************************************************
 * headers
 */

#include <cmath> // std::log10

#include <macros.h>
#include <types.h>

#include "../sound/mix.h"
#include "../sound/seq.h"
#include "../sound/syn.h"

#if 0
#include <revolution/OS/OSAssert.h>
#include <revolution/OS/OSInterrupt.h>
#include <revolution/OS/OSMessage.h>
#include <revolution/AI/ai.h>
#include <revolution/ARC/ARC.h>
#include <revolution/AX/AX.h>
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * macros
 */

#define HBM_MEM_SIZE_SOUND	0x18700	/* name known from asserts */

/*******************************************************************************
 * types
 */

namespace
{
	// AudioSoundThreadProc message values
	enum AudioThreadMsg
	{
		AudioThreadMsg_RunAudioFrame	= 1,
		AudioThreadMsg_Exit				= 8,
	};

	// [SGLEA4]/GormitiDebug.elf:.debug_info::0x47e428
	typedef int UserCallback(int evt, int num);

	// [SGLEA4]/GormitiDebug.elf:.debug_info::0x47d9fa
	struct SeqPlayer
	{
		HBMSEQSEQUENCE	seq;		// size 0x2e1c, offset 0x0000
		bool			activeFlag;	// size 0x0001, offset 0x2e1c
		/* 3 bytes padding */
		SeqPlayer		*next;		// size 0x0004, offset 0x2e20
		SeqPlayer		*prev;		// size 0x0004, offset 0x2e24
		int				seqNum;		// size 0x0004, offset 0x2e28
	}; // size 0x2e2c

	// [SGLEA4]/GormitiDebug.elf:.debug_info::0x47e3e3
	struct SeqPlayerList
	{
		SeqPlayer	*head;	// size 0x04, offset 0x00
		SeqPlayer	*tail;	// size 0x04, offset 0x04
	}; // size 0x08
} // unnamed namespace

// [SGLEA4]/GormitiDebug.elf:.debug_info::0x47d891
struct HMBAxSoundWork // NOTE the misspelled tag name
{
	SeqPlayer		playersDefault[4];		// size 0x0b8b0, offset 0x00000
	SeqPlayer		playersFocus[3];		// size 0x08a84, offset 0x0b8b0
	SeqPlayerList	playerListDefault;		// size 0x00008, offset 0x14334
	SeqPlayerList	playerListFocus;		// size 0x00008, offset 0x1433c
	UserCallback	*userCallback;			// size 0x00004, offset 0x14344
	AXFrameCallback	*oldAxRegisterCallback;	// size 0x00004, offset 0x14348
	ARCHandle		soundArcHandle;			// size 0x0001c, offset 0x1434c
	OSThread		mThread;				// size 0x00318, offset 0x14368
	OSMessageQueue	mMsgQueue;				// size 0x00020, offset 0x14680
	OSMessage		mMessageArray[4];		// size 0x00010, offset 0x146a0
	u64				*mpThreadStack;			// size 0x00004, offset 0x146b0
	void			*wt;					// size 0x00004, offset 0x146b4
	void			*pcm;					// size 0x00004, offset 0x146b8
	/* 4 bytes padding */
}; // size 0x146c0

/*******************************************************************************
 * local function declarations
 */

namespace
{
	void *GetMidiDataFromArc(int num);
	SeqPlayerList *GetUsePlayerListFromSeqNum(int num);
	SeqPlayer *GetFreePlayer(int num);
	void AudioFrameCallback();
	void *AudioSoundThreadProc(void *arg);
	void StopSeq(SeqPlayer *player);
	void UpdateSeqPlayerList(SeqPlayerList *list);
} // unnamed namespace

/*******************************************************************************
 * variables
 */

namespace
{
	// .rodata
	static const char WT_FILENAME[] = "wt\\HomeButtonSe.wt";
	static const char PCM_FILENAME[] = "wt\\HomeButtonSe.pcm";

	// .bss
	static HMBAxSoundWork *sWork;
} // unnamed namespace

/*******************************************************************************
 * functions
 */

namespace {

void *GetMidiDataFromArc(int num)
{
	// clang-format off
	static const char *SOUND_FILENAME[] =
	{
		"midi\\00_home_button.mid",
		"midi\\01_return_app.mid",
		"midi\\02_goto_menu.mid",
		"midi\\03_reset_app.mid",
		"midi\\04_focus.mid",
		"midi\\05_select.mid",
		"midi\\06_cancel.mid",
		"midi\\07_open_controller.mid",
		"midi\\08_close_controller.mid",
		"midi\\09_volume_plus.mid",
		"midi\\10_volume_minus.mid",
		"midi\\11_volume_plus_limit.mid",
		"midi\\12_volume_minus_limit.mid",
		"midi\\13_nothing_done.mid",
		"midi\\14_vibe_on.mid",
		"midi\\15_vibe_off.mid",
		"midi\\16_start_connect_window.mid",
		"midi\\17_connected1.mid",
		"midi\\18_connected2.mid",
		"midi\\19_connected3.mid",
		"midi\\20_connected4.mid",
		"midi\\21_end_connect_window.mid",
		"midi\\22_manual_open.mid",
		"midi\\23_manual_focus.mid",
		"midi\\24_manual_select.mid",
		"midi\\25_manual_scroll.mid",
		"midi\\26_manual_cancel.mid",
		"midi\\27_manual_return_app.mid"
	};
	// clang-format on

	ARCFileInfo info;
	BOOL result = ARCOpen(&sWork->soundArcHandle, SOUND_FILENAME[num], &info);
	if (!result)
		return nullptr;

	return ARCGetStartAddrInMem(&info);
}

SeqPlayerList *GetUsePlayerListFromSeqNum(int num)
{
	switch (num)
	{
	case 4:  /* "04_focus.mid" */
	case 23: /* "23_manual_focus.mid" */
	case 25: /* "25_manual_scroll.mid" */
		return &sWork->playerListFocus;

	default:
		return &sWork->playerListDefault;
	}
}

SeqPlayer *GetFreePlayer(int num)
{
	SeqPlayer *playersArray;
	int arraySize;
	switch (num)
	{
	case 4:  /* "04_focus.mid" */
	case 23: /* "23_manual_focus.mid" */
	case 25: /* "25_manual_scroll.mid" */
		playersArray = sWork->playersFocus;
		arraySize = ARRAY_LENGTH(sWork->playersFocus);
		break;

	default:
		playersArray = sWork->playersDefault;
		arraySize = ARRAY_LENGTH(sWork->playersDefault);
		break;
	}

	SeqPlayer *player = nullptr;
	for (int i = 0; i < arraySize; i++)
	{
		if (!playersArray[i].activeFlag)
		{
			player = &playersArray[i];
			player->activeFlag = true;
			break;
		}
	}

	if (!player)
	{
		SeqPlayerList *list = GetUsePlayerListFromSeqNum(num);
		OSAssert_Line(242, list != NULL);

		player = list->head;
		StopSeq(list->head);
		player->activeFlag = true;
	}

	return player;
}

void AudioFrameCallback()
{
	if (!sWork)
		return;

	int result ATTR_UNUSED = OSSendMessageAny(
		&sWork->mMsgQueue, AudioThreadMsg_RunAudioFrame, OS_MESSAGE_NO_FLAGS);

	if (sWork->oldAxRegisterCallback)
		(*sWork->oldAxRegisterCallback)();
}

void *AudioSoundThreadProc(void *)
{
	OSMessage message = 0;

	while (true)
	{
		OSReceiveMessage(&sWork->mMsgQueue, &message,
		                 OS_MESSAGE_FLAG_PERSISTENT);

		if (reinterpret_cast<u32>(message) == AudioThreadMsg_RunAudioFrame)
		{
			HBMSEQRunAudioFrame();
			HBMSYNRunAudioFrame();
			HBMMIXUpdateSettings();

			if (sWork)
			{
				UpdateSeqPlayerList(&sWork->playerListDefault);
				UpdateSeqPlayerList(&sWork->playerListFocus);
			}
		}
		else if (reinterpret_cast<u32>(message) == AudioThreadMsg_Exit)
		{
			break;
		}
	}

	return nullptr;
}

void StopSeq(SeqPlayer *player)
{
	SeqPlayerList *list = GetUsePlayerListFromSeqNum(player->seqNum);

	HBMSEQSetState(&player->seq, 0);
	HBMSEQRemoveSequence(&player->seq);

	player->activeFlag = false;

	// remove from linked list

	if (!player->prev)
		list->head = player->next;
	else
		player->prev->next = player->next;

	if (!player->next)
		list->tail = player->prev;
	else
		player->next->prev = player->prev;

	player->next = nullptr;
	player->prev = nullptr;
}

void UpdateSeqPlayerList(SeqPlayerList *list)
{
	SeqPlayer *current = list->head;
	for (SeqPlayer *next; current; current = next)
	{
		next = current->next;

		if (current->activeFlag && HBMSEQGetState(&current->seq) == 0
		    && !current->seq.synth.notes)
		{
			StopSeq(current);
		}
	}
}

} // unnamed namespace

namespace homebutton {

void PlaySeq(int num)
{
	void *midi = GetMidiDataFromArc(num);
	if (!midi)
		return;

	SeqPlayer *player = GetFreePlayer(num);
	HBMSEQAddSequence(&player->seq, static_cast<u8 *>(midi),
	                  static_cast<u8 *>(sWork->wt),
	                  static_cast<u8 *>(sWork->pcm), 0);
	HBMSEQSetState(&player->seq, 1);
	player->seqNum = num;

	SeqPlayerList *list = GetUsePlayerListFromSeqNum(num);
	if (!list->tail)
	{
		list->head = player;
		list->tail = player;

		player->next = nullptr;
		player->prev = nullptr;
	}
	else
	{
		list->tail->next = player;

		player->prev = list->tail;
		player->next = nullptr;

		list->tail = player;
	}
}

void InitAxSound(const void *soundData, void *mem, u32 memSize)
{
	OSAssert_Line(437, memSize >= HBM_MEM_SIZE_SOUND);
	if (memSize < HBM_MEM_SIZE_SOUND)
		return;

	if (!AICheckInit())
	{
		AIInit(nullptr);
		AXInit();
	}

	HBMMIXInit();
	HBMSYNInit();
	HBMSEQInit();

	HMBAxSoundWork *work = static_cast<HMBAxSoundWork *>(mem);

	for (int i = 0; i < (int)ARRAY_LENGTH(work->playersDefault); i++)
	{
		work->playersDefault[i].activeFlag = false;
		work->playersDefault[i].next = nullptr;
		work->playersDefault[i].prev = nullptr;
	}

	for (int i = 0; i < (int)ARRAY_LENGTH(work->playersFocus); i++)
	{
		work->playersFocus[i].activeFlag = false;
		work->playersFocus[i].next = nullptr;
		work->playersFocus[i].prev = nullptr;
	}

	work->wt = nullptr;
	work->pcm = nullptr;
	work->mpThreadStack = reinterpret_cast<u64 *>(
		reinterpret_cast<u32>(mem) + (HBM_MEM_SIZE_SOUND - 0x4000));
	work->playerListDefault.head = nullptr;
	work->playerListDefault.tail = nullptr;
	work->playerListFocus.head = nullptr;
	work->playerListFocus.tail = nullptr;
	work->oldAxRegisterCallback = nullptr;

	BOOL result =
		ARCInitHandle(const_cast<void *>(soundData), &work->soundArcHandle);
	if (!result)
		return;

	ARCFileInfo wtInfo;
	result = ARCOpen(&work->soundArcHandle, WT_FILENAME, &wtInfo);
	if (!result)
		return;

	work->wt = ARCGetStartAddrInMem(&wtInfo);

	ARCFileInfo pcmInfo;
	result = ARCOpen(&work->soundArcHandle, PCM_FILENAME, &pcmInfo);
	if (!result)
		return;

	work->pcm = ARCGetStartAddrInMem(&pcmInfo);

	OSInitMessageQueue(&work->mMsgQueue, work->mMessageArray,
	                   ARRAY_LENGTH(work->mMessageArray));

	// would rather the math be (void *)((u32)p + x), but that messes up release
	result = OSCreateThread(&work->mThread, AudioSoundThreadProc, nullptr,
	                        reinterpret_cast<u8 *>(work->mpThreadStack)
	                            + memSize - (HBM_MEM_SIZE_SOUND - 0x4000),
	                        memSize - (HBM_MEM_SIZE_SOUND - 0x4000), 4,
	                        OS_THREAD_NO_FLAGS);
	if (!result)
		return;

	sWork = work;
	OSResumeThread(&work->mThread);

	BOOL intrStatus = OSDisableInterrupts(); /* int old */

	work->oldAxRegisterCallback = AXRegisterCallback(&AudioFrameCallback);

	OSRestoreInterrupts(intrStatus);
}

void ShutdownAxSound()
{
	if (!sWork)
		return;

	StopAllSeq();
	AXRegisterCallback(sWork->oldAxRegisterCallback);

	int result = OSJamMessageAny(&sWork->mMsgQueue, AudioThreadMsg_Exit,
	                             OS_MESSAGE_FLAG_PERSISTENT);
	OSAssert_Line(540, result);

	OSJoinThread(&sWork->mThread, nullptr);
	HBMSEQQuit();
	HBMSYNQuit();
	HBMMIXQuit();
	sWork = nullptr;
}

void AxSoundMain()
{
	if (!sWork)
		return;

	// stripped stuff? no idea
	(void)0;
}

void StopAllSeq()
{
	if (!sWork)
		return;

	for (int i = 0; i < (int)ARRAY_LENGTH(sWork->playersDefault); i++)
	{
		SeqPlayer &player = sWork->playersDefault[i];

		if (player.activeFlag)
			StopSeq(&player);
	}

	OSAssert_Line(591, sWork->playerListDefault.head == NULL);
	OSAssert_Line(592, sWork->playerListDefault.tail == NULL);

	for (int i = 0; i < (int)ARRAY_LENGTH(sWork->playersFocus); i++)
	{
		SeqPlayer &player = sWork->playersFocus[i];

		if (player.activeFlag)
			StopSeq(&player);
	}

	OSAssert_Line(603, sWork->playerListFocus.head == NULL);
	OSAssert_Line(604, sWork->playerListFocus.tail == NULL);
}

void SetVolumeAllSeq(f32 gain)
{
	if (!sWork)
		return;

	s32 db = gain <= 0.0f ? -904
	                      : static_cast<s32>(std::log10(gain) * 20.0f * 10.0f);

	// clamp
	if (db > 60)
		db = 60;

	if (db < -904)
		db = -904;

	for (int i = 0; i < (int)ARRAY_LENGTH(sWork->playersDefault); i++)
	{
		SeqPlayer &player = sWork->playersDefault[i];

		if (player.activeFlag)
			HBMSEQSetVolume(&player.seq, db);
	}

	for (int i = 0; i < (int)ARRAY_LENGTH(sWork->playersFocus); i++)
	{
		SeqPlayer &player = sWork->playersFocus[i];

		if (player.activeFlag)
			HBMSEQSetVolume(&player.seq, db);
	}
}

void SetSoundMode(HBMMIXSoundMode mode)
{
	HBMMIXSetSoundMode(mode);
}

} // namespace homebutton
