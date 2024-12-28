#include "HBMCommon.hpp"

/*******************************************************************************
 * headers
 */

#include <revolution/HBM/HBMConfig.h>

#include <macros.h>
#include <types.h>

#include "HBMAxSound.hpp"
#include "HBMBase.hpp"

#include "../nw4hbm/lyt/lyt_layout.hpp"

#if 0
#include <revolution/OS/OS.h>
#include <revolution/OS/OSAssert.h>
#include <revolution/MEM/mem_expHeap.h>
#include <revolution/MEM/mem_allocator.h>
#endif

#include <hbm/context_rvl.h>

/*******************************************************************************
 * macros
 */

#if !defined(NDEBUG)
#define RVL_SDK_HBM_VERSION_STRING	\
	"<< RVL_SDK - HBM \tdebug build: Dec 10 2009 13:25:28 (" STR(__CWCC__) "_" STR(__CWBUILD__) ") >>"
#else
# if HBM_APP_TYPE == HBM_APP_TYPE_DVD
# define RVL_SDK_HBM_VERSION_STRING	\
	"<< RVL_SDK - HBM \trelease build: Dec 10 2009 13:25:50 (" STR(__CWCC__) "_" STR(__CWBUILD__) ") >>"
#elif HBM_APP_TYPE == HBM_APP_TYPE_NAND
# define RVL_SDK_HBM_VERSION_STRING	\
	"<< RVL_SDK - HBM \trelease build: Dec 10 2009 13:27:22 (" STR(__CWCC__) "_" STR(__CWBUILD__) ") >>"
# endif
#endif // !defined(NDEBUG)

/*******************************************************************************
 * types
 */

// [SGLEA4]/GormitiDebug.elf:.debug_info::0x47ef1e
enum HBMAllocatorType
{
	HBM_ALLOCATOR_APPLI, /* application */
	HBM_ALLOCATOR_LOCAL,
	HBM_ALLOCATOR_NW4R,
};

/*******************************************************************************
 * local function declarations
 */

static HBMAllocatorType getAllocatorType(const HBMDataInfo *info);

/*******************************************************************************
 * variables
 */

// .data
const char *__HBMVersion = RVL_SDK_HBM_VERSION_STRING;

// .bss
static MEMAllocator sAllocator;

// .data (not .sdata, HBM is -sdata 0)
MEMAllocator *spAllocator = &sAllocator;

/*******************************************************************************
 * functions
 */

void *HBMAllocMem(u32 size)
{
	void *addr = MEMAllocFromAllocator(spAllocator, size);

	// why into a variable?

	return addr;
}

void HBMFreeMem(void *mem)
{
	MEMFreeToAllocator(spAllocator, mem);
}

static HBMAllocatorType getAllocatorType(const HBMDataInfo *pHBInfo)
{
	if (pHBInfo->pAllocator)
		return HBM_ALLOCATOR_APPLI;
	else if (pHBInfo->mem)
		return HBM_ALLOCATOR_LOCAL;
	else
		return HBM_ALLOCATOR_NW4R;
}

void HBMCreate(const HBMDataInfo *pHBInfo)
{
	MEMiHeapHead *hExpHeap;

	if (getAllocatorType(pHBInfo) == HBM_ALLOCATOR_LOCAL)
	{
		hExpHeap = MEMCreateExpHeap(pHBInfo->mem, pHBInfo->memSize);
		MEMInitAllocatorForExpHeap(&sAllocator, hExpHeap, 32);
		spAllocator = &sAllocator;
	}

	switch (getAllocatorType(pHBInfo))
	{
	case HBM_ALLOCATOR_APPLI:
		nw4hbm::lyt::Layout::SetAllocator(pHBInfo->pAllocator);
		spAllocator = pHBInfo->pAllocator;
		break;

	case HBM_ALLOCATOR_LOCAL:
		nw4hbm::lyt::Layout::SetAllocator(spAllocator);
		break;

	case HBM_ALLOCATOR_NW4R:
		OSAssert_Line(87, nw4hbm::lyt::Layout::GetAllocator());

		spAllocator = nw4hbm::lyt::Layout::GetAllocator();
		break;
	}

	homebutton::HomeButton::createInstance(pHBInfo);
	homebutton::HomeButton::getInstance()->create();
}

void HBMDelete()
{
	const HBMDataInfo *pHBInfo =
		homebutton::HomeButton::getInstance()->getHBMDataInfo();

	homebutton::HomeButton::deleteInstance();
	if (getAllocatorType(pHBInfo) == HBM_ALLOCATOR_LOCAL)
		MEMDestroyExpHeap(spAllocator->pHeap);
}

void HBMInit()
{
	OSAssert_Line(113, homebutton::HomeButton::getInstance());

	OSRegisterVersion(__HBMVersion);
	homebutton::HomeButton::getInstance()->init();
}

HBMSelectBtnNum HBMCalc(const HBMControllerData *pController)
{
	OSAssert_Line(120, homebutton::HomeButton::getInstance());

	homebutton::HomeButton::getInstance()->calc(pController);
	return homebutton::HomeButton::getInstance()->getSelectBtnNum();
}

void HBMDraw()
{
	OSAssert_Line(128, homebutton::HomeButton::getInstance());

	homebutton::HomeButton::getInstance()->draw();
}

HBMSelectBtnNum HBMGetSelectBtnNum()
{
	return homebutton::HomeButton::getInstance()->getSelectBtnNum();
}

void HBMSetAdjustFlag(BOOL flag)
{
	homebutton::HomeButton::getInstance()->setAdjustFlag(flag);
}

void HBMStartBlackOut()
{
	homebutton::HomeButton::getInstance()->startBlackOut();
}

BOOL HBMIsReassignedControllers()
{
	OSAssert_Line(149, homebutton::HomeButton::getInstance());

	return homebutton::HomeButton::getInstance()->getReassignedFlag();
}

void HBMCreateSound(void *soundData, void *memBuf, u32 memSize)
{
	const HBMDataInfo *pHBInfo ATTR_UNUSED =
		homebutton::HomeButton::getInstance()->getHBMDataInfo();

	// What

	homebutton::InitAxSound(soundData, memBuf, memSize);
}

void HBMDeleteSound()
{
	homebutton::ShutdownAxSound();
}

void HBMUpdateSound()
{
	OSAssert_Line(212, homebutton::HomeButton::getInstance());

	homebutton::HomeButton::getInstance()->update_sound();
}

#if HBM_APP_TYPE == HBM_APP_TYPE_NAND
void HBMCreateInfoEx(const HBMDataInfoEx *pHBInfoEx)
{
	homebutton::HomeButton::getInstance()->createInfoEx(pHBInfoEx);
}

void HBMDeleteInfoEx()
{
	homebutton::HomeButton::getInstance()->destroyInfoEx();
}
#endif // HBM_APP_TYPE == HBM_APP_TYPE_NAND
