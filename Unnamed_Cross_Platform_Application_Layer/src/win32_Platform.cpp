#include "Platform.h"
#ifdef W32

#include "win32_Platform.h"
#include <Xinput.h>
#include <dsound.h>

glob INLINEFORCE B32 IsNaN(float f) { return _isnan(f); }
glob INLINEFORCE B32 IsFinite(float f) { return _finite(f); }

#define PlatformErrorBox(title, str) MessageBox(NULL, str, title, MB_ICONERROR | MB_OK)

intern B32 Win32LoadXInput() {
	return False;
}

#endif