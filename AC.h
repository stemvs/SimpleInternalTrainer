#pragma once

#include "PCH.h"
#include <Windows.h>

namespace ACObjTypes {
	struct Vector3 {
		float x, y, z;
	};

	class Player
	{
	public:
		char pad_0000[4]; //0x0000
		Vector3 headPos; //0x0004
		Vector3 direction; //0x0010
		char pad_001C[12]; //0x001C
		Vector3 bodyPos; //0x0028
		Vector3 lookVector; //0x0034
		char pad_0040[52]; //0x0040
		int32_t clipThing; //0x0074
		char pad_0078[116]; //0x0078
		int32_t health; //0x00EC
		int32_t armor; //0x00F0
		char pad_00F4[12]; //0x00F4
		int32_t dualPistols; //0x0100
		char pad_0104[4]; //0x0104
		int32_t pistolMag; //0x0108
		char pad_010C[16]; //0x010C
		int32_t primaryMag; //0x011C
		char pad_0120[4]; //0x0120
		int32_t dualPMag; //0x0124
		char pad_0128[4]; //0x0128
		int32_t pistolAmmo; //0x012C
		char pad_0130[16]; //0x0130
		int32_t primaryAmmo; //0x0140
		int32_t grenades; //0x0144
		int32_t dualPAmmo; //0x0148
		int32_t knifeWait; //0x014C
		int32_t pistolWait; //0x0150
		char pad_0154[16]; //0x0154
		int32_t GunTimerWait; //0x0164
		int32_t grenadeWait; //0x0168
		int32_t dualpWait; //0x016C
		int32_t knifeAttacks; //0x0170
		int32_t pistolShotsFired; //0x0174
		char pad_0178[16]; //0x0178
		int32_t shotsFired1; //0x0188
		int32_t grenadesThrown; //0x018C
		int32_t shotsFired; //0x0190
		char pad_0194[72]; //0x0194
		int32_t kills; //0x01DC
		char pad_01E0[4]; //0x01E0
		int32_t deaths; //0x01E4
		char pad_01E8[376]; //0x01E8
		class Weapon* previousWeapon; //0x0360
		class Weapon* currentWeapon; //0x0364
		class Weapon* currentWeapon2; //0x0368
		char pad_036C[212]; //0x036C
	}; //Size: 0x0440
	static_assert(sizeof(Player) == 0x440, "");

	class Weapon
	{
	public:
		char pad_0000[4]; //0x0000
		int32_t weaponID; //0x0004
		class Player* weaponOwner; //0x0008
		class WeaponData* weaponData; //0x000C
		DWORD* weaponMag; //0x0010
		DWORD* weaponAmmo; //0x0014
		char pad_0018[4]; //0x0018
		int32_t shotsWhileHolding; //0x001C
		char pad_0020[32]; //0x0020
	}; //Size: 0x0040
	static_assert(sizeof(Weapon) == 0x40, "");

	class WeaponData
	{
	public:
		char pad_0000[66]; //0x0000
		int16_t N000001A9; //0x0042
		int16_t N000002C8; //0x0044
		int16_t reloadTimer; //0x0046
		int16_t shootTimer; //0x0048
		int16_t N000001AB; //0x004A
		int16_t N000002CC; //0x004C
		int16_t N000001AC; //0x004E
		int16_t N000002CE; //0x0050
		int16_t N000001AD; //0x0052
		int16_t N000002D0; //0x0054
		int16_t N000001AE; //0x0056
		int16_t ammoMax; //0x0058
		int16_t N000001AF; //0x005A
		int16_t N000002D4; //0x005C
		int16_t N000001B0; //0x005E
		int16_t recoil; //0x0060
		int16_t N000001B1; //0x0062
		int16_t N000002D8; //0x0064
		int16_t isAutomatic; //0x0066
	}; //Size: 0x0068
	static_assert(sizeof(WeaponData) == 0x68, "");

	class _DWORD
	{
	public:
		int32_t N000001FA; //0x0000
	}; //Size: 0x0004
	static_assert(sizeof(_DWORD) == 0x4, "");
}

namespace ACConstants {
	ACObjTypes::Player** LocalPlayerPtr = (ACObjTypes::Player**)0x58AC00;
	ACObjTypes::WeaponData* WeaponData = (ACObjTypes::WeaponData*)0x0056BCC0;
}