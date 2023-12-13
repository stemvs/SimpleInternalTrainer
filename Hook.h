#pragma once

namespace Mem {
	void Detour32(void* toHook, void* hookFunc, size_t size);
	
	struct TrampolineHook32 {
		void* gateway = 0;
		bool hooked = false;
	private:
		size_t m_size = 0;
		void* m_original = 0;
	public:
		void* Hook(void* toHook, void* hookFunc, size_t size);
		void Unhook();

		~TrampolineHook32() {
			if (hooked)
				Unhook();
		}
	};
}