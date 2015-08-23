#include "Platform.h"
#include <windows.h>
#include <Xinput.h>
#include <dsound.h>

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
#ifdef PlatfromErrorBox
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

glob INLINEFORCE B32 IsNaN(float f) { return _isnan(f); }
glob INLINEFORCE B32 IsFinite(float f) { return _finite(f); }

#define PlatformErrorBox(title, str) MessageBox(NULL, str, title, MB_ICONERROR | MB_OK)

intern B32 Win32LoadXInput() {
	return false;
}