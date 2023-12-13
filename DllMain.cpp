// AC Version: 1.3.0.2

#include "PCH.h"
#include <iostream>
#include <Windows.h>
#include "Hook.h"
#include "AC.h"

typedef int (__thiscall *damage)(DWORD ecx, DWORD a1, DWORD a2);

static bool bInvincibility = false;
static bool bOneShot = false;
static damage damageHookRet;

void __declspec(naked) damageHook(void* retAddr, int damage, int, ACObjTypes::Player* attacker) { //custom prologue & epilogue because __thiscall
	__asm {
		push ecx; // store this pointer
		push ebp; // set function scope
		mov ebp, esp;
		sub esp, __LOCAL_SIZE
	}

	ACObjTypes::Player* _p;

	__asm lea ecx, [ecx - 0xE8];
	__asm mov _p, ecx;

	if (bInvincibility && _p == *ACConstants::LocalPlayerPtr) {
		damage = 0;
	}
	else if (bOneShot && attacker == *ACConstants::LocalPlayerPtr) {
		damage = 0x7FFFFFFF;
	}

	__asm {
		mov esp, ebp; // restore stack
		pop ebp;
		pop ecx; // this
	}
	__asm jmp damageHookRet;
}

DWORD WINAPI MainThread(HMODULE hModule) {
	FILE* f;

	AllocConsole();
	freopen_s(&f, "CONOUT$", "w", stdout);

	Mem::TrampolineHook32 damageTHook;
	ACObjTypes::Player* localP = *ACConstants::LocalPlayerPtr;

	damageHookRet = (damage)damageTHook.Hook((void*)0x0041C130, damageHook, 5);

	std::cout << "Numpad 0: Invincibility\n";
	std::cout << "Numpad 1: One Shot Kill\n";
	std::cout << "Numpad 2: Infinite Ammo\n";
	std::cout << "Numpad 3: Infinite Grenades\n";
	std::cout << "Numpad 4: No Recoil\n";
	std::cout << "Numpad 5: 1337 Kills\n";
	std::cout << "Numpad 6: Invisibility\n";
	std::cout << "Numpad 7: Dual Pistols\n";

	std::cout << "Del: Exit\n";

	while (true) {
		if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
			bInvincibility = !bInvincibility;
		}
		if (GetAsyncKeyState(VK_NUMPAD1) & 1) {
			bOneShot = !bOneShot;
		}
		if (GetAsyncKeyState(VK_NUMPAD2) & 1) { // should patch instructions but it's late
			localP->primaryAmmo = INT_MAX;
			localP->pistolAmmo = INT_MAX;
			localP->dualPAmmo = INT_MAX;
		}
		if (GetAsyncKeyState(VK_NUMPAD3) & 1) {// ^
			localP->grenades = INT_MAX;
		}
		if (GetAsyncKeyState(VK_NUMPAD4) & 1) {//^^
			ACObjTypes::WeaponData* awjeif = ACConstants::WeaponData;
			for (int i = 0; i < 9; i++) {
				awjeif[i].recoil = 0;
				((ACObjTypes::WeaponData*)((DWORD)awjeif + i * sizeof(awjeif)))->recoil = 0;
			}
		}
		if (GetAsyncKeyState(VK_NUMPAD5) & 1) {
			localP->kills = 1337;
		}
		if (GetAsyncKeyState(VK_NUMPAD6) & 1) {
			localP->clipThing ^= 0x01000000;
		}
		if (GetAsyncKeyState(VK_NUMPAD7) & 1) {
			localP->dualPistols ^= 1;
		}
		if (GetAsyncKeyState(VK_DELETE) & 1) {
			damageTHook.Unhook();
			break;
		}
		
		Sleep(30);
	}

	FreeConsole();
	fclose(f);
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr);

		if (hThread) 
			CloseHandle(hThread);
		return TRUE;
	}
}
