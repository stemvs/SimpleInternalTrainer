#include "PCH.h"
#include <vector>
#include "Mem.h"

void Mem::Patch(void* dst, void* src, size_t size) {
	DWORD oldProtect;

	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldProtect, &oldProtect);
}

void Mem::Nop(void* dst, size_t size) {
	BYTE* nops = new BYTE[size];

	memset(nops, 0x90, size);
	Patch(dst, nops, size);
	delete[] nops;
}

uintptr_t Mem::FindDMAAddy(uintptr_t base, std::vector<BYTE> offsets) {
	uintptr_t addr = base;

	for (size_t i = 0; i < offsets.size(); i++) {
		addr = *(uintptr_t*)addr + offsets[i];
	}
	return addr;
}