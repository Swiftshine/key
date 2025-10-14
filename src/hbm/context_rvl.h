#ifndef HBM_CONTEXT_RVL_H
#define HBM_CONTEXT_RVL_H


#include <revolution/MEM.h>
#include <revolution/ARC.h>
#include <revolution/AX.h>
#include <revolution/GX.h>
#include <revolution/KPAD.h>
#include <revolution/SC.h>
#include <revolution/WPAD.h>
#include <revolution/OS.h>

#define OSGetAlarmUserDataAny(type_, alarm_)	\
	((type_)(OSGetAlarmUserData(alarm_)))

#define OSSetAlarmUserDataAny(alarm_, data_)	\
	OSSetAlarmUserData(alarm_, (void *)(data_))

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
#define OSAssert_Line(line_, exp_)	\
	OSAssertMessage_FileLine(__FILE__, line_, exp_, "Failed assertion " #exp_)

typedef s64 OSTime;

#endif
