#ifndef UCPAL_PLATFORM_H
#define UCPAL_PLATFORM_H

#ifdef _WIN32 //TODO: declare this in cmake
#define W32
#ifdef _WIN64
#define W64
#endif
#elif __unix
#define UNX
#endif

#ifndef INLINEFORCE
#define INLINEFORCE
#endif

#ifndef DLLEXPORT
#define DLLEXPORT
#endif

#ifndef DLLIMPORT
#define DLLIMPORT
#endif

#define lscope static
#define glob static
#define intern static
#define scast static_cast
#define rcast reinterpret_cast

#include <float.h>
#include <limits.h>
#include <iostream>

typedef unsigned __int32 B32;

typedef signed __int8 I8;
typedef signed __int16 I16;
typedef signed __int32 I32;
typedef signed __int64 I64;

typedef unsigned __int8 U8;
typedef unsigned __int16 U16;
typedef unsigned __int32 U32;
typedef unsigned __int64 U64;

typedef float F32;
typedef double F64;

typedef char* CSTR;

//CONSTANTS
#define PI (3.1415926535897932f)
#define TAU (6.2831853071795865f)
#define E (2.71828182845904523526f)
#define EZERO (1.0e-8f)
#define EPSILON (1.0e-4f)
#define ARCFINITY (3.402e+38f)
#define VECTOR_PROXIMITY_THRESHOLD (0.00002f)
#define VECTOR_PARALLEL_THRESHOLD (0.02f)
#define RAD_TO_DEG (57.2957795f)
#define DEG_TO_RAD (0.0174532925f)
#define True (0xFFFFFFFF)
#define False (0x00000000)

#define PlatformDebugPrint(str) {}
#define PlatformDebugBreak() {}

#define LoadLib {}

#define PlatformErrorBox(title, str) {}

#ifdef AVRO_DEBUG
#define CHECK_NAN 1
#define Assert(expr, strmessage) if(expr){} \
		else{ \
			char buffer [512]; \
			sprintf_s(buffer, sizeof(buffer), "%s Failed Assertion at: %s ln:%d :: %s\n", \
			(#expr), __FILE__, __LINE__, (strmessage));\
			PlatformDebugPrint(buffer);\
			PlatformDebugBreak();\
}

#elif AVRO_PROFILE
#define Assert(expr, strmessage) if((expr)){}else{ \
			char buffer [512]; \
			sprintf_s(buffer, sizeof(buffer), "%s Failed Assertion at: %s ln:%d :: %s\n", \
			(#expr), __FILE__, __LINE__, (strmessage));\
			PlatformDebugPrint(buffer);\
			PlatformDebugBreak();\
}  

#elif AVRO_RELEASE
#define Assert(expr, strmessage){}
#elif AVRO_PRODUCTION
#define Assert(expr, strmessage){}
#endif

#define INVALID_CODE_PATH Assert(false, "Invalid Code Path")
#define INVALID_DEFAULT_CASE default: {INVALID_CODE_PATH;} break

#define KiB(value) ((value)*1024LL)
#define MiB(value) (KiB(value)*1024LL)
#define GiB(value) (MiB(value)*1024LL)
#define TiB(value) (GiB(value)*1024LL)

#define sizeofArr(arr) (sizeof(arr) / sizeof((arr)[0]))

#define AlignPo2(value, alignment) ((value + ((alignment) - 1)) & ~((alignment) - 1))
#define Align4(value) ((value + 3) & ~3)
#define Align8(value) ((value + 7) & ~7)
#define Align16(value) ((value + 15) & ~15)

	INLINEFORCE DLLEXPORT U32 TruncU64(U64 value);

	INLINEFORCE DLLEXPORT F32 SecondsElapsed(U64 begin, U64 end, U64 perfFrequency);

	glob INLINEFORCE B32 IsNaN(float f);
	glob INLINEFORCE B32 IsFinite(float f);

	struct WindowDimensions {
		U32 width;
		U32 height;
	};

	struct DLLEXPORT GraphicsBuffer {
		//Pixels are always 32-bits wide, BB GG RR XX
		U32* buffer;
		U32 width;
		U32 height;
	};

#define NUM_KEYS 256

	struct DLLEXPORT AudioBuffer {
		U32 sampleHz;
		U32 sampleCount;
		U16* buffer;
	};

	struct DLLEXPORT Gamepad {
		F32 lx;
		F32 ly;
		F32 rx;
		F32 ry;
		F32 lt;
		F32 rt;
		F32 lv;
		F32 rv;
		U16 buttons;
		U16 inputType;
	};

	struct DLLEXPORT InputBuffer {
		U8 keys[NUM_KEYS];
		U8 prevKeys[NUM_KEYS];
		Gamepad gamepads[4];
	};

	struct DLLEXPORT RuntimeMemory {
		U64 permanentStorageSize;
		void* permanentStorage;
		U64 transientStorageSize;
		void* transientStorage;
	};


	template <typename T>
	struct DLLEXPORT HDL {
		T* ptr; //TODO: 32-bit support
	};

	struct DLLEXPORT ASTR {
		CSTR str;
		U32 len;



	};

	INLINEFORCE Gamepad* GetGamepad(InputBuffer* input, U32 gamepadIndex);
	


	/************************************************************************/
	/* Platform defined functions                                           */
	/************************************************************************/

	DLLEXPORT B32 CreatePlatformWindow(const WindowDimensions& size);



	/************************************************************************/
	/* Memory functions                                                     */
	/************************************************************************/

	DLLEXPORT B32 InitializeRuntimeMemory(RuntimeMemory* runtimeMemory);

	DLLEXPORT void* PAlloc(U64 sizeBytes, B32 zeroMem = True);

	DLLEXPORT U64 PFree(void* memToFree, B32 zeroMem = True); //Returns number of bytes freed

	DLLEXPORT void* TAlloc(U64 sizeBytes, B32 zeroMem = True);

	DLLEXPORT U64 TFree(void* memToFree, B32 zeroMem = True); //Returns number of bytes freed

	DLLEXPORT void TerminateRuntimeMemory(RuntimeMemory* runtimeMemory);

	/************************************************************************/
	/* String functions                                                     */
	/************************************************************************/




#endif