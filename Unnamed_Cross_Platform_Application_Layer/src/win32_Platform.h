#ifndef UCPAL_WIN32_PLATFORM_H
#define UCPAL_WIN32_PLATFORM_H

#include <windows.h>
#include "Platform.h"

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#pragma warning(disable : 4005)
#ifdef DLLEXPORT
#undef DLLEXPORT
#endif
#ifdef DLLIMPORT
#undef DLLIMPORT
#endif
#ifdef INLINEFORCE
#undef INLINEFORCE
#endif
#ifdef PlatformDebugPrint
#undef PlatformDebugPrint
#endif
#ifdef PlatformDebugBreak
#undef PlatformDebugBreak
#endif
#ifdef LoadLib
#undef LoadLib
#endif
#ifdef PlatformErrorBox
#undef PlatformErrorBox
#endif

#define VARARGS __cdecl
#define CDECL __cdecl
#define STDCALL __stdcall
#define INLINEFORCE __forceinline
#define NOINLINE __declspec(noinline)

#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

#define PlatformDebugPrint(str) OutputDebugStringA(str)
#define PlatformDebugBreak() DebugBreak()

#define LoadLib(str) LoadLibraryA(str)

#endif