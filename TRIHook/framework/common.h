//
// Common resources
//

#pragma once

#if !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif
#define _CRT_NON_CONFORMING_SWPRINTFS


#include <cassert>

#include <type_traits>

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#include <windowsx.h>

#include <Shlwapi.h>
#include <ShlObj.h>

#include "util.h"

//  C4091: '__declspec(novtable)': ignored on left of 'x' when no variable is declared
#pragma warning (disable : 4091)
// disable warning/error about __identifier(<string>)
#pragma warning(disable:4483)

// Unsigned type definitions
typedef unsigned char byte, u_char;
typedef unsigned short ushort, u_short;
typedef unsigned int uint, u_int;
typedef unsigned long ulong, u_long;
typedef unsigned long long uint64, u_int64;