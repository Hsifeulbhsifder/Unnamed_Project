#include "Platform.h"

INLINEFORCE Gamepad* GetGamepad(InputBuffer* input, U32 gamepadIndex) {
	//Assert(((gamepadIndex < sizeofArr(input->gamepads) && (gamepadIndex >= 0)), "Invalid gamepad index");

	return &(input->gamepads[gamepadIndex]);
}

INLINEFORCE DLLEXPORT F32 SecondsElapsed(U64 begin, U64 end, U64 perfFrequency) {
	return (F32)(end - begin) / (F32)perfFrequency;
}

INLINEFORCE DLLEXPORT U32 TruncU64(U64 value) {
	Assert(value <= 0xFFFFFFFF, "Invalid U32 value for truncation");
	return (U32)value;
}