#ifndef TYPES_H
#define TYPES_H

#ifdef __cplusplus
#include <stdarg.h>
#include <stddef.h>
#else
#include <stdarg.h>
#include <stddef.h>
#endif

#include "macros.h"

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned char u8;
typedef signed char s8;

typedef float f32;
typedef double f64;

enum { FALSE, TRUE };
typedef int BOOL;

#endif
