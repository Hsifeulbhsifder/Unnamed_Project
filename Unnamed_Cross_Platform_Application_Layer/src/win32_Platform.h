#ifndef UCPAL_WIN32_PLATFORM_H
#define UCPAL_WIN32_PLATFORM_H

#include <Platform.h>
#include <windows.h>

#pragma warning(disable : 4005)

#undef DLLEXPORT
#undef DLLIMPORT
#undef INLINEFORCE

#define VARARGS __cdecl
#define CDECL __cdecl
#define STDCALL __stdcall
#define INLINEFORCE __forceinline
#define NOINLINE __declspec(noinline)

#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

#define AvroDebugBreak() DebugBreak()

glob INLINEFORCE B32 IsNaN(float f) { return _isnan(f); }
glob INLINEFORCE B32 IsFinite(float f) { return _finite(f); }

#define LoadLib(str) LoadLibraryA(str)

#define PlatformDebugPrint(str){ OutputDebugStringA(str);}
#define PlatformDebugBreak(){DebugBreak();}

#define ErrorBox(str, title){\
	MessageBox(NULL, str, title, MB_ICONERROR | MB_OK);\
}

DLLEXPORT void Win32LoadXInput();



#endif