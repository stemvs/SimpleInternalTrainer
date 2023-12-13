#include "PCH.h"
#include <Windows.h>
#include "Hook.h"
#include "Mem.h"

void Mem::Detour32(void* toHook, void* hookFunc, size_t size) {
	BYTE* buffPtr = new BYTE[size];

	memset(buffPtr, 0x90, size);
	*buffPtr = 0xE9;
	*(DWORD*)(buffPtr + 1) = (DWORD)hookFunc - (DWORD)toHook - 5;
	Patch(toHook, buffPtr, size);
	delete[] buffPtr;
}

void* Mem::TrampolineHook32::Hook(void* toHook, void* hookFunc, size_t size) {
	if (!hooked && (gateway = VirtualAlloc(nullptr, size + 5, MEM_COMMIT, PAGE_EXECUTE_READWRITE))) {
		memcpy(gateway, toHook, size);
		*(BYTE*)((uintptr_t)gateway + size) = 0xE9;
		*(DWORD*)((uintptr_t)gateway + size + 1) = (DWORD)toHook - (DWORD)gateway - 5;
		Detour32(toHook, hookFunc, size);

		m_size = size;
		m_original = toHook;
		hooked = true;

		return gateway;
	}

	return gateway;
}
void Mem::TrampolineHook32::Unhook() {
	if (hooked) {
		Patch(m_original, gateway, m_size);
		VirtualFree(gateway, 0, MEM_RELEASE);
		hooked = false;
	}
}

