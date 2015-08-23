#include <Platform.h>
#ifdef W32
#include <windows.h>
#include <Engine.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define TITLE "Avro Arrow"

I32 WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){

	CreateEngine();
	PlatformDebugPrint("Hello World!\n");

	return 0;
}

#endif