#include "Platform.h"

#define HEADER_SIZE sizeof(U64)
#define FOOTER_SIZE sizeof(U64)
#define ALLOC_BIT 0x8000000000000000
#define SIZE_BIT  0x7FFFFFFFFFFFFFFF
#define BYTE_0    0x7F00000000000000 
#define BYTE_1    0x00FF000000000000 
#define BYTE_2    0x0000FF0000000000 
#define BYTE_3    0x000000FF00000000 
#define BYTE_4    0x00000000FF000000 
#define BYTE_5    0x0000000000FF0000 
#define BYTE_6    0x000000000000FF00 
#define BYTE_7    0x00000000000000FF 

//GLOBAL VARIABLES
RuntimeMemory* grm; //Global runtime memory
U64 permanentMemoryAvailable;
U64 transientMemoryAvailable;
U64 permanentBlocks;
U64 transientBlocks;

//Adds HEADER and FOOTER to the memory
intern INLINEFORCE U64 TotalMemSize(U64 memSize) {
	return memSize + HEADER_SIZE + FOOTER_SIZE;
}

intern INLINEFORCE B32 GetAllocationBit(void* mem) {
	U8* ptr = scast<U8*>(mem);
	return ptr[0] & (ALLOC_BIT >> 0x38);
}

intern INLINEFORCE U64 GetBlockSize(void* mem) {
	U64 sizeBytes = 0;
	U8* ptr = scast<U8*>(mem);
	sizeBytes += ((U64)ptr[0] << 0x38) & BYTE_0;
	sizeBytes += ((U64)ptr[1] << 0x30) & BYTE_1;
	sizeBytes += ((U64)ptr[2] << 0x28) & BYTE_2;
	sizeBytes += ((U64)ptr[3] << 0x20) & BYTE_3;
	sizeBytes += ((U64)ptr[4] << 0x18) & BYTE_4;
	sizeBytes += ((U64)ptr[5] << 0x10) & BYTE_5;
	sizeBytes += ((U64)ptr[6] << 0x08) & BYTE_6;
	sizeBytes += ((U64)ptr[7] << 0x00) & BYTE_7;
	return sizeBytes;
}

intern INLINEFORCE void WriteSizeAndAllocationBit(void* mem, U64 sizeBytes, B32 alloc) {
	U8* ptr = scast<U8*>(mem);
	ptr[0] = (U8)((sizeBytes & BYTE_0) >> 0x38);
	ptr[0] |= alloc?(U8)(ALLOC_BIT>>0x38):False;
	ptr[1] = (U8)((sizeBytes & BYTE_1) >> 0x30);
	ptr[2] = (U8)((sizeBytes & BYTE_2) >> 0x28);
	ptr[3] = (U8)((sizeBytes & BYTE_3) >> 0x20);
	ptr[4] = (U8)((sizeBytes & BYTE_4) >> 0x18);
	ptr[5] = (U8)((sizeBytes & BYTE_5) >> 0x10);
	ptr[6] = (U8)((sizeBytes & BYTE_6) >> 0x08);
	ptr[7] = (U8)((sizeBytes & BYTE_7) >> 0x00);
	ptr[HEADER_SIZE + sizeBytes + 0] = (U8)((sizeBytes & BYTE_0) >> 0x38);
	ptr[HEADER_SIZE + sizeBytes + 0] |= alloc?(U8)(ALLOC_BIT>>0x38):False;
	ptr[HEADER_SIZE + sizeBytes + 1] = (U8)((sizeBytes & BYTE_1) >> 0x30);
	ptr[HEADER_SIZE + sizeBytes + 2] = (U8)((sizeBytes & BYTE_2) >> 0x28);
	ptr[HEADER_SIZE + sizeBytes + 3] = (U8)((sizeBytes & BYTE_3) >> 0x20);
	ptr[HEADER_SIZE + sizeBytes + 4] = (U8)((sizeBytes & BYTE_4) >> 0x18);
	ptr[HEADER_SIZE + sizeBytes + 5] = (U8)((sizeBytes & BYTE_5) >> 0x10);
	ptr[HEADER_SIZE + sizeBytes + 6] = (U8)((sizeBytes & BYTE_6) >> 0x08);
	ptr[HEADER_SIZE + sizeBytes + 7] = (U8)((sizeBytes & BYTE_7) >> 0x00);
}

intern B32 MemIsFirstPermanentBlock(void* mem) {
	return grm->permanentStorage == mem;
}

intern B32 MemIsLastPermanentBlock(void* mem) {
	U8* ptr = scast<U8*>(grm->permanentStorage);
	ptr += HEADER_SIZE + grm->permanentStorageSize;
	return &ptr[-(I64)GetBlockSize(ptr) - (I64)HEADER_SIZE] == mem;
}

intern B32 MemIsFirstTransientBlock(void* mem) {
	return grm->transientStorage == mem;
}

intern B32 MemIsLastTransientBlock(void* mem) {
	U8* ptr = scast<U8*>(grm->transientStorage);
	ptr += HEADER_SIZE + grm->transientStorageSize;
	return &ptr[-(I64)GetBlockSize(ptr) - (I64)HEADER_SIZE] == mem;
}

intern void PCoalesce(void* mem) {
	U8* ptr = scast<U8*>(mem);
	U64 sizeBytes = GetBlockSize(ptr);
	//Backwards Coalesce
	if (!MemIsFirstPermanentBlock(ptr) && !GetAllocationBit(&ptr[-(I64)FOOTER_SIZE])) {
		U64 prevSizeBytes = GetBlockSize(&ptr[-(I64)FOOTER_SIZE]);
		ptr -= TotalMemSize(prevSizeBytes);
		sizeBytes += TotalMemSize(prevSizeBytes);
		WriteSizeAndAllocationBit(ptr, sizeBytes, False);
		permanentBlocks--;
	}
	//Forward Coalesce
	if (!MemIsLastPermanentBlock(ptr) && !GetAllocationBit(&ptr[TotalMemSize(sizeBytes)])) {
		U64 nextSizeBytes = GetBlockSize(&ptr[TotalMemSize(sizeBytes)]);
		sizeBytes += TotalMemSize(nextSizeBytes);
		WriteSizeAndAllocationBit(ptr, sizeBytes, False);
		transientBlocks--;
	}
}


intern void TCoalesce(void* mem) {
	U8* ptr = scast<U8*>(mem);
	U64 sizeBytes = GetBlockSize(ptr);
	//Backwards Coalesce
	if (!MemIsFirstTransientBlock(ptr) && !GetAllocationBit(&ptr[-(I64)FOOTER_SIZE])) {
		U64 prevSizeBytes = GetBlockSize(&ptr[-(I64)FOOTER_SIZE]);
		ptr -= TotalMemSize(prevSizeBytes);
		sizeBytes += TotalMemSize(prevSizeBytes);
		WriteSizeAndAllocationBit(ptr, sizeBytes, False);
	}
	//Forward Coalesce
	if (!MemIsLastTransientBlock(ptr) && !GetAllocationBit(&ptr[TotalMemSize(sizeBytes)])) {
		U64 nextSizeBytes = GetBlockSize(&ptr[TotalMemSize(sizeBytes)]);
		sizeBytes += TotalMemSize(nextSizeBytes);
		WriteSizeAndAllocationBit(ptr, sizeBytes, False);
	}
}

intern B32 AllocateNewBlock(void* mem, U64 sizeBytes) {
	U64 oldSize = GetBlockSize(mem);
	if (oldSize < TotalMemSize(sizeBytes) && sizeBytes < oldSize) {
		sizeBytes = oldSize;
	}
	WriteSizeAndAllocationBit(mem, sizeBytes, True);
	if (sizeBytes < oldSize) {
		U8* ptr = scast<U8*>(mem);
		WriteSizeAndAllocationBit((ptr + TotalMemSize(sizeBytes)), oldSize - TotalMemSize(sizeBytes), False);
		return True;
	}
	return False;
}

intern void GrowTransientHeap() {
	//TODO: Complete this as well as defragmentation once proper handle system is implemented
}

intern void Reset() {
	memset(grm->permanentStorage, 0, TotalMemSize(grm->permanentStorageSize));
	memset(grm->transientStorage, 0, TotalMemSize(grm->transientStorageSize));
	permanentBlocks = 1;
	transientBlocks = 1;
	permanentMemoryAvailable = grm->permanentStorageSize;
	transientMemoryAvailable = grm->transientStorageSize;
	WriteSizeAndAllocationBit(grm->permanentStorage, grm->permanentStorageSize, False);
	WriteSizeAndAllocationBit(grm->transientStorage, grm->transientStorageSize, False);
}

B32 InitializeRuntimeMemory(RuntimeMemory* runtimeMemory) {
	grm = runtimeMemory;
	if (!(grm->permanentStorage)) {
		grm->permanentStorage = malloc(TotalMemSize(grm->permanentStorageSize));
		if (!(grm->permanentStorage)) {
			Assert(False, "Memory Allocation Failed");
		}
	}
	if (!(grm->transientStorage)) {
		grm->transientStorage = malloc(TotalMemSize(grm->transientStorageSize));
		if (!(grm->transientStorage)) {
			Assert(False, "Memory Allocation Failed");
		}
	}
	Reset();

	return True;
}

void* PAlloc(U64 sizeBytes, B32 zeroMem) {
	U8* currPtr = scast<U8*>(grm->permanentStorage);
	B32 found = False;
	for (U64 i = 0; i < permanentBlocks; i++) {
		U64 currBlockSize = GetBlockSize(currPtr);
		if (!GetAllocationBit(currPtr) && sizeBytes <= currBlockSize) {
			found = True;
			break;
		}
		currPtr += TotalMemSize(currBlockSize);
	}
	if (found) {
		B32 memRemaining = AllocateNewBlock(currPtr, sizeBytes);
		if(memRemaining) permanentMemoryAvailable -= TotalMemSize(sizeBytes);
		else permanentMemoryAvailable -= sizeBytes;
		void* returnMem = scast<void*>(&currPtr[HEADER_SIZE]);
		permanentBlocks++;
		if (zeroMem) memset(returnMem, 0, sizeBytes);
		return returnMem;
	}
	return NULL;
}

U64 PFree(void* memToFree, B32 zeroMem) {
	U8* ptr = scast<U8*>(memToFree);
	ptr -= HEADER_SIZE;
	U64 sizeBytes = GetBlockSize(ptr);
	if (zeroMem) memset(&ptr[HEADER_SIZE], 0, sizeBytes);
	WriteSizeAndAllocationBit(ptr, sizeBytes, False);
	PCoalesce(ptr);
	return sizeBytes;
}

void* TAlloc(U64 sizeBytes, B32 zeroMem) {
	U8* currPtr = scast<U8*>(grm->transientStorage);
	B32 found = False;
	for (U64 i = 0; i < transientBlocks; i++) {
		U64 currBlockSize = GetBlockSize(currPtr);
		if (!GetAllocationBit(currPtr) && sizeBytes <= currBlockSize) {
			found = True;
			break;
		}
		currPtr += TotalMemSize(currBlockSize);
	}
	if (found) {
		B32 memRemaining = AllocateNewBlock(currPtr, sizeBytes);
		if (memRemaining) transientMemoryAvailable -= TotalMemSize(sizeBytes);
		else transientMemoryAvailable -= sizeBytes;
		void* returnMem = scast<void*>(&currPtr[HEADER_SIZE]);
		transientBlocks++;
		if (zeroMem) memset(returnMem, 0, sizeBytes);
		return returnMem;
	}
	return NULL;
}

U64 TFree(void* memToFree, B32 zeroMem) {
	U8* ptr = scast<U8*>(memToFree);
	ptr -= HEADER_SIZE;
	U64 sizeBytes = GetBlockSize(ptr);
	if (zeroMem) memset(&ptr[HEADER_SIZE], 0, sizeBytes);
	WriteSizeAndAllocationBit(ptr, sizeBytes, False);
	TCoalesce(ptr);
	return sizeBytes;
}

void TerminateRuntimeMemory(RuntimeMemory* runtimeMemory) {
	permanentMemoryAvailable = 0;
	transientMemoryAvailable = 0;
	permanentBlocks = 0;
	transientBlocks = 0;
	free(grm->permanentStorage);
	free(grm->transientStorage);
	grm->permanentStorageSize = 0;
	grm->transientStorageSize = 0;
}