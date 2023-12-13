#pragma once

#include "PCH.h"
#include <Windows.h>
#include <vector>

namespace Mem {
	void Patch(void* dst, void* src, size_t size);
	void Nop(void* dst, size_t size);
	uintptr_t FindDMAAddy(uintptr_t base, std::vector<BYTE> offsets);
}