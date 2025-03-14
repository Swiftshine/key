#ifndef RVL_SDK_WPAD_MEMORY_H
#define RVL_SDK_WPAD_MEMORY_H

/*******************************************************************************
 * headers
 */

#include <revolution/types.h>

#include <revolution/WPAD/WPAD.h>
#include <revolution/WPAD/WPADMem.h>

// #include <revolution/WPAD/context_rvl.h>

// #if 0
#include <revolution/OS/OSTime.h>
// #endif

#include <revolution/OS.h>
#include <revolution/NAND.h>
#include <revolution/SC.h>
#include <revolution/VI.h>
/*******************************************************************************
 * macros
 */

#define WM_MEM_ADDR(addr_)	((addr_) & 0xffff)
#define WM_EXT_REG_ADDR(type_, addr_)	\
	(((addr_) & 0xffff) | ((WPAD_EXT_REG_ ## type_) << 16) | (1 << 26))

/*******************************************************************************
 * types
 */

#ifdef __cplusplus
	extern "C" {
#endif

typedef u32 OSTick;

extern u32 OS_BUS_CLOCK : 0x800000f8;

#define OS_TIMER_CLOCK	(OS_BUS_CLOCK / 4)

// clang-format off
#define OSTicksToSeconds(ticks)			((ticks)        / (OS_TIMER_CLOCK         )       )
#define OSTicksToMilliseconds(ticks)	((ticks)        / (OS_TIMER_CLOCK / 1000  )       )
#define OSTicksToMicroseconds(ticks)	((ticks) * 8    / (OS_TIMER_CLOCK / 125000)       )
#define OSTicksToNanoseconds(ticks)		((ticks) * 8000 / (OS_TIMER_CLOCK / 125000)       )

#define OSSecondsToTicks(sec)			((  sec)        * (OS_TIMER_CLOCK         )       )
#define OSMillisecondsToTicks(msec)		(( msec)        * (OS_TIMER_CLOCK / 1000  )       )
#define OSMicrosecondsToTicks(usec)		(( usec)        * (OS_TIMER_CLOCK / 125000) / 8   )
#define OSNanosecondsToTicks(nsec)		(( nsec)        * (OS_TIMER_CLOCK / 125000) / 8000)

#define OSDiffTick(tick1, tick0)		((OSTick)(tick1) - (OSTick)(tick0))

typedef s64 OSTime;

extern BOOL __OSIsReturnToIdle;

enum OSShutdownEvent_et
{
	OS_SHUTDOWN_EVENT_FATAL, // seems to be used by OSFatal
	OS_SHUTDOWN_EVENT_1,
	OS_SHUTDOWN_EVENT_SHUTDOWN,
	OS_SHUTDOWN_EVENT_3,
	OS_SHUTDOWN_EVENT_RESTART,
	OS_SHUTDOWN_EVENT_RETURN_TO_MENU,
	OS_SHUTDOWN_EVENT_LAUNCH_APP,
};

typedef u8 WPADExtRegType;
enum WPADExtRegType_et
{
	WPAD_EXT_REG_SPEAKER		= 0xa2,
	WPAD_EXT_REG_EXTENSION		= 0xa4,
	WPAD_EXT_REG_MOTION_PLUS	= 0xa6,
	WPAD_EXT_REG_DPD			= 0xb0,
};

// https://wiibrew.org/wiki/Wiimote#EEPROM_Memory
typedef struct WPADGameInfo
{
	OSTime	timestamp;		// size 0x08, offset 0x00
	u16		gameName[17];	// size 0x22, offset 0x08
	char	gameID[4];		// size 0x04, offset 0x2a
	u8		gameType;		// size 0x01, offset 0x2e
	u8		checksum;		// size 0x01, offset 0x2f

	/* wiibrew says this exists in the header on the Wiimote but goes unused,
	 * which matches up with the code I see here
	 */
	byte_t	unknown[8];
} WPADGameInfo; // size 0x38

/*******************************************************************************
 * functions
 */

WPADResult WPADWriteExtReg(WPADChannel chan, const void *data, u16 length,
                           WPADExtRegType extReg, u16 address,
                           WPADCallback *cb);

#ifdef __cplusplus
	}
#endif

#endif // RVL_SDK_WPAD_MEMORY_H
