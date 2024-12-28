#include "synsample.h"

/*******************************************************************************
 * headers
 */

#include <types.h>

#include "syn.h"
#include "synvoice.h"

#if 0
#include <revolution/OS/OSAssert.h>
#include <revolution/AX/AX.h>
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * local function declarations
 */

static u32 __HBMSYNGetNibbleAddress(u32 count);
static void __HBMSYNSetupAdpcm(HBMSYNVOICE *voice);
static void __HBMSYNSetupPcm16(HBMSYNVOICE *voice);
static void __HBMSYNSetupPcm8(HBMSYNVOICE *voice);

/*******************************************************************************
 * functions
 */

static u32 __HBMSYNGetNibbleAddress(const u32 count)
{
	const u32 samples = count; // probably?
	u32 frames = samples / 14;
	u32 samplesLeft = samples % 14;

	return 2 + frames * 16 + samplesLeft;
}

static void __HBMSYNSetupAdpcm(HBMSYNVOICE *voice)
{
	AXVPB *axvpb = voice->axvpb;

	if (voice->region->loopStart + voice->region->loopLength != 0)
	{
		u32 sampleStart;
		u32 sampleLoop;
		u32 sampleEnd;
		u32 *p;
		u32 *adpcm;
		u16 *adpcmloop;

		adpcm = (u32 *)voice->adpcm;
		voice->type = 1;

		sampleStart = voice->synth->samplesBaseNibble + voice->sample->offset;
		sampleLoop =
			sampleStart + __HBMSYNGetNibbleAddress(voice->region->loopStart);
		sampleEnd = sampleStart
		          + __HBMSYNGetNibbleAddress(voice->region->loopStart
		                                     + voice->region->loopLength - 1);

		OSAssert_Line(64, (sampleStart & 0x000f) == 0);
		OSAssert_Line(65, (sampleLoop & 0x000f) > 1);
		OSAssert_Line(66, (sampleEnd & 0x000f) > 1);

		sampleStart += sizeof(u16);
		p = (u32 *)&axvpb->pb.addr;

		// clang-format off
		/* addr.{loopFlag,format}     */ *p = 0x00010000; p++;
		/* addr.loopAddress{Hi,Lo}    */ *p = sampleLoop; p++;
		/* addr.endAddress{Hi,Lo}     */ *p = sampleEnd; p++;
		/* addr.currentAddress{Hi,Lo} */ *p = sampleStart; p++;

		/* adpcm.a[0][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[1][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[2][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[3][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[4][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[5][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[6][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[7][{0,1}]          */ *p = *adpcm; p++; adpcm++;

		/* adpcm.{gain,pred_scale}    */ *p = *adpcm; p++; adpcm++;
		/* adpcm.yn{1,2}              */ *p = *adpcm;
		// clang-format on

		adpcmloop = (u16 *)++adpcm;

		// clang-format off
		axvpb->pb.adpcmLoop.loop_pred_scale = *adpcmloop; adpcmloop++;
		axvpb->pb.adpcmLoop.loop_yn1 = *adpcmloop; adpcmloop++;
		axvpb->pb.adpcmLoop.loop_yn2 = *adpcmloop;
		// clang-format on

		axvpb->sync &=
			~(AX_VPB_SYNC_FLAG_ADDR_LOOP_FLAG | AX_VPB_SYNC_FLAG_ADDR_LOOP_ADDR
		      | AX_VPB_SYNC_FLAG_ADDR_END_ADDR
		      | AX_VPB_SYNC_FLAG_ADDR_CURRENT_ADDR);

		axvpb->sync |= AX_VPB_SYNC_FLAG_ADDR | AX_VPB_SYNC_FLAG_ADPCM
		             | AX_VPB_SYNC_FLAG_ADPCM_LOOP;
	}
	else
	{
		u32 sampleStart;
		u32 sampleLoop;
		u32 sampleEnd;
		u32 *p;
		u32 *adpcm;

		adpcm = (u32 *)voice->adpcm;
		voice->type = 0;

		sampleStart = voice->synth->samplesBaseNibble + voice->sample->offset;
		sampleLoop = voice->synth->samplesBaseNibble + voice->sample->offset;
		sampleEnd =
			sampleStart + __HBMSYNGetNibbleAddress(voice->sample->length - 1);

		OSAssert_Line(120, (sampleStart & 0x000f) == 0);
		OSAssert_Line(121, (sampleEnd & 0x000f) > 1);

		sampleStart += sizeof(u16);
		p = (u32 *)&axvpb->pb.addr;

		// clang-format off
		/* addr.{loopFlag,format}     */ *p = 0x00000000; p++;
		/* addr.loopAddress{Hi,Lo}    */ *p = sampleLoop; p++;
		/* addr.endAddress{Hi,Lo}     */ *p = sampleEnd; p++;
		/* addr.currentAddress{Hi,Lo} */ *p = sampleStart; p++;

		/* adpcm.a[0][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[1][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[2][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[3][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[4][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[5][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[6][{0,1}]          */ *p = *adpcm; p++; adpcm++;
		/* adpcm.a[7][{0,1}]          */ *p = *adpcm; p++; adpcm++;

		/* adpcm.{gain,pred_scale}    */ *p = *adpcm; p++; adpcm++;
		/* adpcm.yn{1,2}              */ *p = *adpcm;
		// clang-format on

		axvpb->sync &=
			~(AX_VPB_SYNC_FLAG_ADDR_LOOP_FLAG | AX_VPB_SYNC_FLAG_ADDR_LOOP_ADDR
		      | AX_VPB_SYNC_FLAG_ADDR_END_ADDR
		      | AX_VPB_SYNC_FLAG_ADDR_CURRENT_ADDR);

		axvpb->sync |= AX_VPB_SYNC_FLAG_ADDR | AX_VPB_SYNC_FLAG_ADPCM;
	}
}

static void __HBMSYNSetupPcm16(HBMSYNVOICE *voice)
{
	AXVPB *axvpb = voice->axvpb;

	if (voice->region->loopStart + voice->region->loopLength != 0)
	{
		u32 sampleStart;
		u32 sampleLoop;
		u32 sampleEnd;
		u32 *p;

		voice->type = 1;

		sampleStart = voice->synth->samplesBaseWord + voice->sample->offset;
		sampleLoop = sampleStart + voice->region->loopStart;
		sampleEnd = sampleLoop + voice->region->loopLength - 1;
		p = (u32 *)&axvpb->pb.addr;

		// clang-format off
		/* addr.{loopFlag,format}     */ *p = 0x0001000a; p++;
		/* addr.loopAddress{Hi,Lo}    */ *p = sampleLoop; p++;
		/* addr.endAddress{Hi,Lo}     */ *p = sampleEnd; p++;
		/* addr.currentAddress{Hi,Lo} */ *p = sampleStart; p++;

		/* adpcm.a[0][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[1][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[2][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[3][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[4][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[5][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[6][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[7][{0,1}]          */ *p = 0; p++;

		/* adpcm.{gain,pred_scale}    */ *p = 0x08000000; p++;
		/* adpcm.yn{1,2}              */ *p = 0x00000000;
		// clang-format on
	}
	else
	{
		u32 sampleStart;
		u32 sampleLoop;
		u32 sampleEnd;
		u32 *p;

		voice->type = 0;

		sampleStart = voice->synth->samplesBaseWord + voice->sample->offset;
		sampleLoop = voice->synth->samplesBaseWord + voice->sample->offset;
		sampleEnd = sampleStart + voice->sample->length - 1;
		p = (u32 *)&axvpb->pb.addr;

		// clang-format off
		/* addr.{loopFlag,format}     */ *p = 0x0000000a; p++;
		/* addr.loopAddress{Hi,Lo}    */ *p = sampleLoop; p++;
		/* addr.endAddress{Hi,Lo}     */ *p = sampleEnd; p++;
		/* addr.currentAddress{Hi,Lo} */ *p = sampleStart; p++;

		/* adpcm.a[0][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[1][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[2][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[3][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[4][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[5][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[6][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[7][{0,1}]          */ *p = 0; p++;

		/* adpcm.{gain,pred_scale}    */ *p = 0x08000000; p++;
		/* adpcm.yn{1,2}              */ *p = 0x00000000;
		// clang-format on
	}

	axvpb->sync &= ~(
		AX_VPB_SYNC_FLAG_ADDR_LOOP_FLAG | AX_VPB_SYNC_FLAG_ADDR_LOOP_ADDR
		| AX_VPB_SYNC_FLAG_ADDR_END_ADDR | AX_VPB_SYNC_FLAG_ADDR_CURRENT_ADDR);

	axvpb->sync |= AX_VPB_SYNC_FLAG_ADDR | AX_VPB_SYNC_FLAG_ADPCM;
}

static void __HBMSYNSetupPcm8(HBMSYNVOICE *voice)
{
	AXVPB *axvpb = voice->axvpb;

	if (voice->region->loopStart + voice->region->loopLength != 0)
	{
		u32 sampleStart;
		u32 sampleLoop;
		u32 sampleEnd;
		u32 *p;

		voice->type = 1;

		sampleStart = voice->synth->samplesBaseByte + voice->sample->offset;
		sampleLoop = sampleStart + voice->region->loopStart;
		sampleEnd = sampleLoop + voice->region->loopLength - 1;
		p = (u32 *)&axvpb->pb.addr;

		// clang-format off
		/* addr.{loopFlag,format}     */ *p = 0x00010019; p++;
		/* addr.loopAddress{Hi,Lo}    */ *p = sampleLoop; p++;
		/* addr.endAddress{Hi,Lo}     */ *p = sampleEnd; p++;
		/* addr.currentAddress{Hi,Lo} */ *p = sampleStart; p++;

		/* adpcm.a[0][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[1][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[2][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[3][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[4][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[5][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[6][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[7][{0,1}]          */ *p = 0; p++;

		/* adpcm.{gain,pred_scale}    */ *p = 0x01000000; p++;
		/* adpcm.yn{1,2}              */ *p = 0x00000000;
		// clang-format on
	}
	else
	{
		u32 sampleStart;
		u32 sampleLoop;
		u32 sampleEnd;
		u32 *p;

		voice->type = 0;

		sampleStart = voice->synth->samplesBaseByte + voice->sample->offset;
		sampleLoop = voice->synth->samplesBaseByte + voice->sample->offset;
		sampleEnd = sampleStart + voice->sample->length - 1;
		p = (u32 *)&axvpb->pb.addr;

		// clang-format off
		/* addr.{loopFlag,format}     */ *p = 0x00000019; p++;
		/* addr.loopAddress{Hi,Lo}    */ *p = sampleLoop; p++;
		/* addr.endAddress{Hi,Lo}     */ *p = sampleEnd; p++;
		/* addr.currentAddress{Hi,Lo} */ *p = sampleStart; p++;

		/* adpcm.a[0][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[1][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[2][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[3][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[4][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[5][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[6][{0,1}]          */ *p = 0; p++;
		/* adpcm.a[7][{0,1}]          */ *p = 0; p++;

		/* adpcm.{gain,pred_scale}    */ *p = 0x01000000; p++;
		/* adpcm.yn{1,2}              */ *p = 0x00000000;
		// clang-format on
	}

	axvpb->sync &= ~(
		AX_VPB_SYNC_FLAG_ADDR_LOOP_FLAG | AX_VPB_SYNC_FLAG_ADDR_LOOP_ADDR
		| AX_VPB_SYNC_FLAG_ADDR_END_ADDR | AX_VPB_SYNC_FLAG_ADDR_CURRENT_ADDR);

	axvpb->sync |= AX_VPB_SYNC_FLAG_ADDR | AX_VPB_SYNC_FLAG_ADPCM;
}

void __HBMSYNSetupSample(HBMSYNVOICE *voice)
{
	OSAssert_Line(346, voice);

	switch (voice->sample->format)
	{
	case 0:
		__HBMSYNSetupAdpcm(voice);
		break;

	case 1:
		__HBMSYNSetupPcm16(voice);
		break;

	case 2:
		__HBMSYNSetupPcm8(voice);
		break;

	default:
		OSAssertMessage_Line(370, FALSE, "unknown sample format\n");
		break;
	}
}
