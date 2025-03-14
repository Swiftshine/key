#ifndef CONTEXT_RVL_H
#define CONTEXT_RVL_H

#include <macros.h> // ROUND_UP
#include <revolution/types.h>
#include <revolution/OS.h>
#include <revolution/context_bte.h>

/* Contains the context of the other Revolution SDK libraries that the WPAD
 * library needs to compile.
 *
 * This is not the full context; the other half of the context is in
 * "context_bte.h".
 *
 * Ideally, this file's usages should be replaced with the headers in your
 * project that declare these symbols.
 */

#if !defined(NDEBUG)
# define OSAssertMessage_FileLine(file_, line_, exp_, ...)	\
	(void)((exp_) || (OSPanic(file_, line_, __VA_ARGS__), 0))
#else
# define OSAssertMessage_FileLine(file_, line_, exp_, ...)	\
	((void)0)
#endif

// defined in terms of OSAssertMessage_FileLine
#define OSAssertMessage_Line(line_, exp_, ...)	\
	OSAssertMessage_FileLine(__FILE__, line_, exp_, __VA_ARGS__)
/* #define OSAssert_Line(line_, exp_) \ */
	// OSAssertMessage_FileLine(__FILE__, line_, exp_, "Failed assertion " #exp_)

#define OSAssert_Line(line_, exp_) { }


// OSError
#define OSError_FileLine(file_, line_, ...)	\
	OSPanic(file_, line_, __VA_ARGS__)

// defined in terms of OSError_FileLine
#define OSError_Line(line_, ...)	\
	OSError_FileLine(__FILE__, line_, __VA_ARGS__)

// OS

typedef s64 OSTime;
typedef u32 OSTick;

// typedef u8 OSAppType;
// enum OSAppType_et
// {
// 	OS_APP_TYPE_IPL		= 0x40,
// 	OS_APP_TYPE_DVD		= 0x80,
// 	OS_APP_TYPE_CHANNEL	= 0x81,
// };

extern BOOL __OSInIPL;
extern OSTime __OSStartTime;

void OSRegisterVersion(const char *version);
const char *OSGetAppGamename(void);
// OSAppType OSGetAppType(void);
u8 OSGetAppType(void);

#if defined(NDEBUG)
# define OSPhysicalToCached(addr)	(void *)((u32)(addr) + 0x80000000)
# define OSPhysicalToUncached(addr)	(void *)((u32)(addr) + 0xC0000000)
# define OSCachedToPhysical(addr)	(void *)((u32)(addr) - 0x80000000)
# define OSUncachedToPhysical(addr)	(void *)((u32)(addr) - 0xC0000000)
#endif // defined(NDEBUG)

void *(OSPhysicalToCached)(void *addr);
void *(OSPhysicalToUncached)(void *addr);
void *(OSCachedToPhysical)(void *addr);
void *(OSUncachedToPhysical)(void *addr);

typedef struct OSAlarm OSAlarm;
typedef struct OSContext OSContext;

// typedef void OSAlarmHandler(OSAlarm *alarm, OSContext *context);

// [SPQE7T]/ISpyD.elf:.debug_info::0x2950d7
// struct OSAlarm
// {
// 	OSAlarmHandler	*handler;	// size 0x04, offset 0x00
// 	u32				tag;		// size 0x04, offset 0x04
// 	OSTime			fire;		// size 0x08, offset 0x08
// 	OSAlarm			*prev;		// size 0x04, offset 0x10
// 	OSAlarm			*next;		// size 0x04, offset 0x14
// 	OSTime			period;		// size 0x08, offset 0x18
// 	OSTime			start;		// size 0x08, offset 0x20
// 	void			*userData;	// size 0x04, offset 0x28
// 	// 4 bytes padding
// }; // size 0x30

void OSCreateAlarm(OSAlarm *alarm);
void OSSetPeriodicAlarm(OSAlarm *alarm, OSTime tick, OSTime period,
                        OSAlarmHandler handler);
void OSCancelAlarm(OSAlarm *alarm);

void DCInvalidateRange(const void *buf, u32 len);

typedef void OSFiber(/* unspecified */);

// [SPQE7T]/ISpyD.elf:.debug_info::0x3135
// struct OSContext
// {
// 	register_t	gpr[32];			// size 0x080, offset 0x000
// 	register_t	cr;					// size 0x004, offset 0x080
// 	register_t	lr;					// size 0x004, offset 0x084
// 	register_t	ctr;				// size 0x004, offset 0x088
// 	register_t	xer;				// size 0x004, offset 0x08c
// 	f64			fpr[32];			// size 0x100, offset 0x090
// 	u32			fpscr_pad;			// size 0x004, offset 0x190
// 	register_t	fpscr;				// size 0x004, offset 0x194
// 	register_t	srr0;				// size 0x004, offset 0x198
// 	register_t	srr1;				// size 0x004, offset 0x19c
// 	u16			mode;				// size 0x002, offset 0x1a0
// 	u16			state;				// size 0x002, offset 0x1a2
// 	register_t	gqr[8];				// size 0x020, offset 0x1a4
// 	u32			psf_pad;			// size 0x004, offset 0x1c4
// 	f64			psf[32];			// size 0x100, offset 0x1c8
// }; // size 0x2c8

void OSSwitchFiberEx(register_t arg0, register_t arg1, register_t arg2,
                     register_t arg3, OSFiber *fiber, void *stack);

u32 OSCalcCRC32(const void *data, u32 length);

__attribute__((weak)) void OSReport(const char *msg, ...);
__attribute__((weak)) void OSPanic(const char *file, int line,
                                   const char *msg, ...);

BOOL OSDisableInterrupts(void);
BOOL OSRestoreInterrupts(BOOL status);

typedef struct OSMutex OSMutex;

// [SPQE7T]/ISpyD.elf:.debug_info::0x333a
typedef struct OSMutexLink
{
	OSMutex	*next;	// size 0x04, offset 0x00
	OSMutex	*prev;	// size 0x04, offset 0x04
} OSMutexLink; // size 0x08

typedef int OSShutdownPass;
enum OSShutdownPass_et
{
	OS_SHUTDOWN_PASS_FIRST,
	OS_SHUTDOWN_PASS_SECOND
};

// typedef u32 OSShutdownEvent;
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

// typedef BOOL OSShutdownFunction(OSShutdownPass pass, OSShutdownEvent event);

// typedef struct OSShutdownFunctionInfo OSShutdownFunctionInfo;
// struct OSShutdownFunctionInfo
// {
// 	OSShutdownFunction		*func;	// size 0x04, offset 0x00	/* name known from asserts */
// 	u32						prio;	// size 0x04, offset 0x04
// 	OSShutdownFunctionInfo	*next;	// size 0x04, offset 0x08
// 	OSShutdownFunctionInfo	*prev;	// size 0x04, offset 0x0c
// }; // size 0x10

typedef struct OSShutdownFunctionQueue
{
	OSShutdownFunctionInfo	*head;	// size 0x04, offset 0x00
	OSShutdownFunctionInfo	*tail;	// size 0x04, offset 0x04
} OSShutdownFunctionQueue; // size 0x08

extern BOOL __OSIsReturnToIdle;

void OSRegisterShutdownFunction(OSShutdownFunctionInfo *info);

typedef struct OSThread OSThread;

enum OSThreadState
{
	OS_THREAD_STATE_EXITED		= 0,
	OS_THREAD_STATE_READY		= (1 << 0),
	OS_THREAD_STATE_RUNNING		= (1 << 1),
	OS_THREAD_STATE_SLEEPING	= (1 << 2),
	OS_THREAD_STATE_MORIBUND	= (1 << 3),
} typedef OSThreadState;

typedef u16 OSThreadFlags;
enum OSThreadFlags_et
{
	OS_THREAD_NO_FLAGS	= 0,

	OS_THREAD_DETACHED	= (1 << 0),
};

typedef void OSSwitchThreadCallback(OSThread *curThread, OSThread *newThread);
typedef void *OSThreadFunction(void *arg);

// [SPQE7T]/ISpyD.elf:.debug_info::0x2fb2
typedef struct OSThreadQueue
{
	OSThread	*head;	// size 0x04, offset 0x00
	OSThread	*tail;	// size 0x04, offset 0x04
} OSThreadQueue; // size 0x08

// [SPQE7T]/ISpyD.elf:.debug_info::0x328b
typedef struct OSThreadLink
{
	OSThread	*next;	// size 0x04, offset 0x00
	OSThread	*prev;	// size 0x04, offset 0x04
} OSThreadLink; // size 0x08

// [SPQE7T]/ISpyD.elf:.debug_info::0x32cf
typedef struct OSMutexQueue
{
	OSMutex	*head;	// size 0x04, offset 0x00
	OSMutex	*tail;	// size 0x04, offset 0x04
} OSMutexQueue; // size 0x08

// [SPQE7T]/ISpyD.elf:.debug_info::0x2feb
struct OSThread
{
	OSContext		context;		// size 0x2c8, offset 0x000
	u16				state;			// size 0x002, offset 0x2c8
	u16				attr;			// size 0x002, offset 0x2ca
	s32				suspend;		// size 0x004, offset 0x2cc
	s32				priority;		// size 0x004, offset 0x2d0
	s32				base;			// size 0x004, offset 0x2d4
	void			*val;			// size 0x004, offset 0x2d8
	OSThreadQueue	*queue;			// size 0x004, offset 0x2dc
	OSThreadLink	link;			// size 0x008, offset 0x2e0
	OSThreadQueue	queueJoin;		// size 0x008, offset 0x2e8
	OSMutex			*mutex;			// size 0x004, offset 0x2f0
	OSMutexQueue	queueMutex;		// size 0x008, offset 0x2f4
	OSThreadLink	linkActive;		// size 0x008, offset 0x2fc
	u8				*stackBase;		// size 0x004, offset 0x304
	u32				*stackEnd;		// size 0x004, offset 0x308
	s32				error;			// size 0x004, offset 0x30c
	void			*specific[2];	// size 0x008, offset 0x310
}; // size 0x318

void OSInitThreadQueue(OSThreadQueue *queue);

// [SPQE7T]/ISpyD.elf:.debug_info::0x2f63
struct OSMutex
{
	OSThreadQueue	queue;		// size 0x08, offset 0x00
	OSThread		*thread;	// size 0x04, offset 0x08
	s32				count;		// size 0x04, offset 0x0c
	OSMutexLink		link;		// size 0x08, offset 0x10
}; // size 0x18

#define OS_CORE_CLOCK	729000000u

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
// clang-format on

OSTime OSGetTime(void);
OSTick OSGetTick(void);
OSTime __OSGetSystemTime(void);

// IPC

volatile u32 __IPCRegs[] : 0xcd000000;

inline u32 ACRReadReg(u32 reg)
{
	return __IPCRegs[reg >> 2];
}

inline void ACRWriteReg(u32 reg, u32 val)
{
	__IPCRegs[reg >> 2] = val;
}

// NAND

#define FS_MAX_PATH 64

typedef s32 NANDResult;
enum NANDResult_et
{
	NAND_RESULT_OK				= 0,

	NAND_RESULT_FATAL_ERROR		= -128,
	NAND_RESULT_UNKNOWN			= -64,

	NAND_RESULT_ACCESS			= -1,
	NAND_RESULT_ALLOC_FAILED	= -2,
	NAND_RESULT_BUSY			= -3,
	NAND_RESULT_CORRUPT			= -4,
	NAND_RESULT_ECC_CRIT		= -5,
	NAND_RESULT_EXISTS			= -6,

	NAND_RESULT_INVALID			= -8,
	NAND_RESULT_MAXBLOCKS		= -9,
	NAND_RESULT_MAXFD			= -10,
	NAND_RESULT_MAXFILES		= -11,
	NAND_RESULT_NOEXISTS		= -12,
	NAND_RESULT_NOTEMPTY		= -13,
	NAND_RESULT_OPENFD			= -14,
	NAND_RESULT_AUTHENTICATION	= -15,
	NAND_RESULT_MAXDEPTH		= -16,

#define NAND_ESUCCESS	NAND_RESULT_OK
#define NAND_EFATAL		NAND_RESULT_FATAL_ERROR
};

typedef u8 NANDOpenMode;
enum NANDOpenMode_et
{
	NAND_OPEN_NONE,

	NAND_OPEN_READ,
	NAND_OPEN_WRITE,
	NAND_OPEN_RW,
};

typedef enum NANDSeekMode
{
	NAND_SEEK_SET,
	NAND_SEEK_CUR,
	NAND_SEEK_END
} NANDSeekMode;

typedef struct NANDCommandBlock NANDCommandBlock;
typedef void NANDAsyncCallback(NANDResult result, NANDCommandBlock *block);

// [SPQE7T]/ISpyD.elf:.debug_info::0x283b92
typedef struct NANDFileInfo
{
	s32		fileDescriptor;			// size 0x04, offset 0x00
	s32		origFd;					// size 0x04, offset 0x04
	char	origPath[FS_MAX_PATH];	// size 0x40, offset 0x08
	char	tmpPath[FS_MAX_PATH];	// size 0x40, offset 0x48
	u8		accType;				// size 0x01, offset 0x88
	u8		stage;					// size 0x01, offset 0x89
	u8		mark;					// size 0x01, offset 0x8a
	// 1 byte padding
} NANDFileInfo; // size 0x8c

// [SPQE7T]/ISpyD.elf:.debug_info::0x2837aa
struct NANDCommandBlock
{
	void		*userData;				// size 0x04, offset 0x00
	void		*callback;				// size 0x04, offset 0x04 // not NANDAsyncCallback *?
	void		*fileInfo;				// size 0x04, offset 0x08 // not NANDFileInfo *?
	void		*bytes;					// size 0x04, offset 0x0c
	void		*inodes;				// size 0x04, offset 0x10
	void		*status;				// size 0x04, offset 0x14
	u16			ownerId;				// size 0x02, offset 0x18
	u16			groupId;				// size 0x02, offset 0x1a
	u8			nextStage;				// size 0x01, offset 0x1c
	// 3 bytes padding
	u32			attr;					// size 0x04, offset 0x20
	u32			ownerAcc;				// size 0x04, offset 0x24
	u32			groupAcc;				// size 0x04, offset 0x28
	u32			othersAcc;				// size 0x04, offset 0x2c
	u32			num;					// size 0x04, offset 0x30
	char		absPath[FS_MAX_PATH];	// size 0x40, offset 0x34
	u32			*length;				// size 0x04, offset 0x74
	u32			*pos;					// size 0x04, offset 0x78
	int			state;					// size 0x04, offset 0x7c
	void		*copyBuf;				// size 0x04, offset 0x80
	u32			bufLength;				// size 0x04, offset 0x84
	u8			*type;					// size 0x04, offset 0x88
	u32			uniqNo;					// size 0x04, offset 0x8c
	u32			reqBlocks;				// size 0x04, offset 0x90
	u32			reqInodes;				// size 0x04, offset 0x94
	u32			*answer;				// size 0x04, offset 0x98
	u32			homeBlocks;				// size 0x04, offset 0x9c
	u32			homeInodes;				// size 0x04, offset 0xa0
	u32			userBlocks;				// size 0x04, offset 0xa4
	u32			userInodes;				// size 0x04, offset 0xa8
	u32			workBlocks;				// size 0x04, offset 0xac
	u32			workInodes;				// size 0x04, offset 0xb0
	const char	**dir;					// size 0x04, offset 0xb4
	int			simpleFlag;				// size 0x04, offset 0xb8
}; // size 0xbc

NANDResult NANDReadAsync(NANDFileInfo *info, void *buf, u32 len,
                         NANDAsyncCallback *callback, NANDCommandBlock *block);
NANDResult NANDWriteAsync(NANDFileInfo *info, const void *buf, u32 len,
                          NANDAsyncCallback *callback, NANDCommandBlock *block);
NANDResult NANDSeekAsync(NANDFileInfo *info, s32 offset, NANDSeekMode whence,
                         NANDAsyncCallback *callback, NANDCommandBlock *block);

NANDResult NANDInit(void);

NANDResult NANDOpenAsync(const char *path, NANDFileInfo *info,
                         NANDOpenMode mode, NANDAsyncCallback *callback,
                         NANDCommandBlock *block);
NANDResult NANDCloseAsync(NANDFileInfo *info, NANDAsyncCallback *callback,
                          NANDCommandBlock *block);

// SC

// from ogws

enum SCSensorBarPos
{
	SC_SENSOR_BAR_BOTTOM,
	SC_SENSOR_BAR_TOP
} typedef SCSensorBarPos;

typedef struct SCBtDeviceInfo // basic dev info?
{
	BD_ADDR					devAddr;	// size 0x06, offset 0x00
	struct small_dev_info	small;		// size 0x40, offset 0x06
} SCBtDeviceInfo; // size 0x46

typedef struct SCBtDeviceInfoArray
{
	u8				num;			// size 0x001, offset 0x000	/* name known from asserts */

	/* NOTE: contents of the devices member are actually
	 *
	 * SCBtDeviceInfo	registered[WUD_MAX_DEV_ENTRY_FOR_STD];
	 * SCBtDeviceInfo	active[WUD_MAX_CHANNELS];
	 *
	 * but functions in WUD act as if it's only one buffer (see
	 * __wudSecurityEventStackCallback, case BTA_DM_LINK_DOWN_EVT)
	 */
	SCBtDeviceInfo	devices[14];	// size 0x3d4, offset 0x001

	SCBtDeviceInfo	wbc;			// size 0x046, offset 0x3d5
	SCBtDeviceInfo	at_0x41b;		// size 0x046, offset 0x41b
} SCBtDeviceInfoArray; // size 0x461

typedef struct SCBtCmpDevInfo // complex dev info?
{
	BD_ADDR					devAddr;	// size 0x06, offset 0x00
	struct small_dev_info	small;		// size 0x40, offset 0x06
	LINK_KEY				linkKey;	// size 0x10, offset 0x30 // ? or just a buffer
} SCBtCmpDevInfo; // size 0x56

typedef struct SCBtCmpDevInfoArray
{
	u8				num;			// size 0x001, offset 0x000 /* name known from asserts */
	SCBtCmpDevInfo	devices[6];		// size 0x204, offset 0x001
} SCBtCmpDevInfoArray; // size 0x205

void SCGetBtDeviceInfoArray(SCBtDeviceInfoArray *array);
BOOL SCSetBtDeviceInfoArray(const SCBtDeviceInfoArray *array);
void SCGetBtCmpDevInfoArray(SCBtCmpDevInfoArray *array);
BOOL SCSetBtCmpDevInfoArray(const SCBtCmpDevInfoArray *array);
u32 SCGetBtDpdSensibility(void);
u8 SCGetWpadMotorMode(void);
BOOL SCSetWpadMotorMode(u8 mode);
u8 SCGetWpadSensorBarPosition(void);
u8 SCGetWpadSpeakerVolume(void);
BOOL SCSetWpadSpeakerVolume(u8 vol);

typedef s8 SCProductGameRegion;
enum SCProductGameRegion_et
{
	SC_PRD_GAME_REG_JP,
	SC_PRD_GAME_REG_US,
	SC_PRD_GAME_REG_EU,
	SC_PRD_GAME_REG_DEBUG,

	SC_PRD_GAME_REG_KR,
	SC_PRD_GAME_REG_CN,

	SC_PRD_GAME_REG_MAX,
	SC_PRD_GAME_REG_NULL	= -1
};

SCProductGameRegion SCGetProductGameRegion(void);

typedef u32 SCStatus;
enum SCStatus_et
{
	SC_STATUS_OK,
	SC_STATUS_BUSY,
	SC_STATUS_FATAL,
	SC_STATUS_PARSE,
};

typedef void SCFlushCallback(SCStatus status);

void SCInit(void);
SCStatus SCCheckStatus(void);

void SCFlushAsync(SCFlushCallback *cb);

// VI

void __VIResetRFIdle(void);

#endif // CONTEXT_RVL_H
