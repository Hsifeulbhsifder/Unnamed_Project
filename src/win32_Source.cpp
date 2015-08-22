#include <Platform.h>
#ifdef W32
#include <win32_Platform.h>
#include <Engine.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define TITLE "Avro Arrow"

I32 STDCALL WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){

	CreateEngine();
	PlatformDebugPrint("Hello World!\n");

	return 0;
}

#endif