#include <Platform.h>
#ifdef W32
#include <win32_Platform.h>
#include <Engine.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define TITLE "Avro Arrow"

I32 WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){

	U64 sizep = MiB(500);
	U64 sizet = GiB(2);

	RuntimeMemory runtimeMemory{ sizep, NULL, sizet, NULL };
	InitializeRuntimeMemory(&runtimeMemory);
	
	U8* arrp = (U8*)PAlloc(sizep);
	U8* arrt = (U8*)TAlloc(sizet);
	U64 arrpSize = sizeofArr(arrp);
	U64 arrtSize = sizeofArr(arrt);

	U64 rSizep = PFree(arrp);
	U64 rSizet = TFree(arrt);

	TerminateRuntimeMemory(&runtimeMemory);
	for (;;) {

	}



	return 0;
}

#endif