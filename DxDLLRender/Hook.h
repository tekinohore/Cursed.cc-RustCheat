#pragma once
#include "Ofssets.h"


class Color
{
public:
	float r;
	float g;
	float b;
	float a;
	float Green;
	Color(float rr, float gg, float bb, float aa)
	{
		r = rr;
		g = gg;
		b = bb;
		Green = Green;
		a = aa;
	}
};

typedef void(__fastcall* SendProjectileAttack_fn)(void*, void*);
SendProjectileAttack_fn Orig_SendProjectileAttack{ };

typedef void(__fastcall* SilentHeli)(void*, void*);
SilentHeli Orig_HeliSendProjectileAttack{ };

typedef void(__fastcall* SetFlying_fn)(void*, void*);
SetFlying_fn original_setflying{};

__declspec(selectany) uintptr_t TargetSilentPlayer = NULL;
__declspec(selectany) uintptr_t TargetPSilentPlayer = NULL;
__declspec(selectany) uintptr_t closestPlayer = NULL;

__declspec(selectany) uintptr_t TargetSilientHeli = NULL;

typedef bool(__fastcall* Can_Attack)(void*, void*);
inline Can_Attack Orig_CanAttack;

typedef float(__fastcall* GetSpeed)(float* a1, float* a2);
inline GetSpeed Orig_GetSpeed;

typedef void(__fastcall* SendProjectileAttack_fn)(void*, void*);
inline SendProjectileAttack_fn original_sendprojectileattack{ };

typedef Vector3(__fastcall* clientinput)(DWORD64, DWORD64);
inline clientinput original_clientinput;

typedef bool(__fastcall* cancan)(void*, void*);
inline cancan original_canholditems;

typedef pUncStr(__fastcall* consoleRun)(uintptr_t, pUncStr, DWORD64);
inline consoleRun original_consolerun{};


typedef DWORD64(__fastcall* playerChams_fn)(DWORD64, float);
playerChams_fn original_playerChams{};

typedef void(__fastcall* BlockSprint)(void*);
inline BlockSprint Orig_BlockSprint;

typedef void(__fastcall* HandleRunning_fn)(void* a1, void* a2, bool);
inline HandleRunning_fn orig_handleRunning;

typedef void(__fastcall* Blockt)(void*, D2D1::ColorF);
inline Blockt Orig_CHAMSESP;

typedef void(__fastcall* FastHeal_)(void* a1, void* a2);
inline FastHeal_ Orig_Heal;

typedef uintptr_t(__fastcall* create_projectile_fn)(void*, void*, Vector3, Vector3, Vector3);
inline create_projectile_fn original_create_projectile{ };

typedef float(__fastcall* GetIndexedSpreadScalar)(int*, int*);
inline GetIndexedSpreadScalar Orig_GetIndexedSpreadScalar{ };

typedef void(__fastcall* AntiAim)(void*);
inline AntiAim original_sendclienttick;

typedef void(__fastcall* NightMode_)(void* a1, void* a2);
inline NightMode_ original_mode;


void __fastcall NightMode(void* a1, void* a2)
{
	if (Vars::Visuals::NightMode)
	{
		typedef void(__stdcall* F)(float);
		typedef void(__stdcall* I)(int);
		typedef void(__stdcall* C)(D2D1::ColorF);
		((I)(GetModBase(StrW(L"GameAssembly.dll")) + oAmbientMode))(3);
		((F)(GetModBase(StrW(L"GameAssembly.dll")) + oambientIntensit))(1.f);
		((C)(GetModBase(StrW(L"GameAssembly.dll")) + oambientLight))(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));

	}
	return  original_mode(a1, a2);
}

inline void __fastcall hook_sendclienttick(void* self)
{
	if (Vars::Misc::AntiAim)
	{
		auto input = safe_read(self + oPlayerInput, uintptr_t);  //Input
		if (!input)
		{
			//std::cout << "Failed to get input!" << std::endl;
			return original_sendclienttick(self);
		}

		auto state = safe_read(input + 0x20, uintptr_t);
		if (!state)
		{
			//std::cout << "Failed to get state!" << std::endl;
			return original_sendclienttick(self);
		}

		auto current = safe_read(state + 0x10, uintptr_t);
		if (!current)
		{
			//std::cout << "Failed to get current!" << std::endl;
			return original_sendclienttick(self);
		}
		safe_write(current + 0x18, Vector3(100, rand() % 999 + -999, rand() % 999 + -999), Vector3);
	}
	return original_sendclienttick(self);
}

inline uintptr_t __fastcall CreateProjectile(void* BaseProjectile, void* prefab_pathptr, Vector3 pos, Vector3 forward, Vector3 velocity) {
	uintptr_t projectile = original_create_projectile(BaseProjectile, prefab_pathptr, pos, forward, velocity);
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(Vars::Storage::closestPlayer);
	safe_write(projectile + 0x114, true, bool);
	if (Vars::AimBot::FatBullet) {
		safe_write(projectile + 0x2C, 1.f, float);
	}
	else {
		safe_write(projectile + 0x2C, 0.1f, float);
	}
	return projectile;
}

DWORD64 __fastcall GetSkinColor(DWORD64 skinset, float skinNumber) {
	DWORD64 color = original_playerChams(skinset, skinNumber);
	if (Vars::Visuals::Chams) {
		safe_write(color + 0x0, 0.50f, float);
		safe_write(color + 0x4, 0.00f, float);
		safe_write(color + 0x8, 1.00f, float);
		safe_write(color + 0xC, 1.00f, float);
	}
	return color;
}

void __fastcall Fake_handleRunning(void* a1, void* a2, bool wantsRun)
{
	if (Vars::Misc::SlideWalk)
		return orig_handleRunning(a1, a2, true);
	return orig_handleRunning(a1, a2, wantsRun);
}

bool __fastcall CanHoldItems(void* a1, void* a2) {
	if (Vars::Misc::canHoldItems)
		return true;
	return original_canholditems(a1, a2);
}

__forceinline Vector2 CalcAngle(const Vector3& Src, const Vector3& Dst)
{
	Vector3 dir = Src - Dst;

	return Vector2{ RAD2DEG(asin(dir.y / dir.Length())), RAD2DEG(-atan2(dir.x, -dir.z)) };
}

inline bool __fastcall Fake_Can_Attack(void* a1, void* a2)
{
	if (Vars::Misc::JumpAiming)
		return true;
	return Orig_CanAttack(a1, a2);
}
inline void __fastcall Fake_BlockSprint(void* a1)
{
	if (Vars::Misc::JumpAiming)
		return;

	return Orig_BlockSprint(a1);
}


bool IsUsing_FastHeal = true;
float Use_Last_FastHeal;

unsigned my_rand()
{
	if (!lfsr) {
		lfsr = 0xACE1u; bit = 0;
	}
	bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1;
	return lfsr = (lfsr >> 1) | (bit << 15);
}

inline void __fastcall Fake_SendProjectileAttack(void* a1, void* a2)
{
	uintptr_t PlayerAttack = safe_read((uintptr_t)a2 + 0x18, uintptr_t); // PlayerAttack playerAttack;
	uintptr_t Attack = safe_read(PlayerAttack + 0x18, uintptr_t); // public Attack attack;
	if (Vars::AimBot::EnableSilentAim)
	{
		if (TargetSilentPlayer != NULL)
		{
			safe_write(Attack + 0x30, 698017942, uint32_t); // public uint hitBone;
			safe_write(Attack + 0x64, 16144115, uint32_t); // public uint hitPartID;
			if (Vars::AimBot::ThroughWall)
			{
				safe_write(Attack + oHitNormalWorld, Vector3(0.f, -1000.f, 0.f) * -10000.f, Vector3);
			}
			safe_write(Attack + oHitID, safe_read(safe_read(TargetSilentPlayer + oNetworkable, uintptr_t) + oNetworkId, uint32_t), uint32_t);
		}
	}
	if (Vars::AimBot::AlwaysHeadshot)
	{
		safe_write(Attack + 0x30, 698017942, uint32_t); // public uint hitBone;
	}
	if (Vars::AimBot::AlwaysBody)
	{
		safe_write(Attack + 0x30, 1031402764, uint32_t); // public uint hitBone;
	}
	if (Vars::AimBot::randhitbox) {
		switch (my_rand() % 4) {
		case 0: // Head
			safe_write(Attack + 0x30, 698017942, uint32_t); // public uint hitBone;
			break;
		case 1: // Chest
			safe_write(Attack + 0x30, 1031402764, uint32_t); // public uint hitBone;
			break;
		case 2: // LHand
			safe_write(Attack + 0x30, 182688154, uint32_t); // public uint hitBone;
			break;
		case 3: // RHand
			safe_write(Attack + 0x30, 102231371, uint32_t); // public uint hitBone;
			break;
		}
	}
	if (Vars::AimBot::HellBullet) {
		if (TargetSilentPlayer != NULL)
		{
			const auto PlayerAttack = safe_read(reinterpret_cast<uintptr_t>(a2) + 0x18, uintptr_t);
			const auto Attack = safe_read(PlayerAttack + 0x18, uintptr_t);

			switch (my_rand() % 2) {
			case 0:
				safe_write(Attack + 0x30, 224139191, uint32_t);
				break;
			case 1:
				safe_write(Attack + 0x30, 2699525250, uint32_t);
				break;

			}
		}

	}
	return Orig_SendProjectileAttack(a1, a2);
}

inline void __fastcall silentheli(void* a1, void* a2)
{
	if (Vars::AimBot::SilentHeli)
	{
		{
			if (TargetSilientHeli != NULL)
			{
				const auto PlayerAttack = safe_read((uintptr_t)a2 + 0x18, uintptr_t);
				const auto Attack = safe_read(PlayerAttack + 0x18, uintptr_t);
				int health = (int)ceil(safe_read(TargetSilientHeli + 0x1FC, float)); // Player_Health ,// public float attackSpacing;
				if (health <= 5000)
				{
					safe_write(Attack + 0x30, 224139191, uint32_t); //public uint hitID;
				}
				else
				{
					safe_write(Attack + 0x30, 2699525250, uint32_t); //public uint hitID;
				}
			}
		}
	}
	return Orig_HeliSendProjectileAttack(a1, a2);
}

inline float __fastcall Fake_GetIndexedSpreadScalar(int* a1, int* a2)
{
	if (Vars::Misc::ShotGunTochka)
	{
		return 0;
	}
	return  Orig_GetIndexedSpreadScalar(a1, a2);
}

inline void CreateHook(void* Function, void** Original, void* Detour, bool autoEnable = true)
{
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED)
	{
		std::cout << "Failed to initialize Hook" << std::endl;
		return;
	}
	MH_CreateHook(Function, Detour, Original);
	if (autoEnable)
		MH_EnableHook(Function);
}

typedef Vector3(__fastcall* aimconedirection)(float, Vector3, bool);
inline aimconedirection original_aimconedirection;

Vector3 Prediction(const Vector3& LP_Pos, BasePlayer* Player, BoneList Bone);

pUncStr __fastcall Run(uintptr_t options, pUncStr strCommand, DWORD64 args) {
	bool IsFromServer = safe_read(options + 0x6, bool);
	if (IsFromServer) {
		std::wstring cmd = std::wstring(strCommand->str);
		if (cmd.find(L"noclip") != std::wstring::npos || cmd.find(L"debugcamera") != std::wstring::npos || cmd.find(L"camspeed") != std::wstring::npos || cmd.find(L"admintime") != std::wstring::npos) {
			strCommand = nullptr;
		}
	}
	return original_consolerun(options, strCommand, args);
}

bool __fastcall get_isFlying(void* BasePlayer)
{
	if (Vars::Misc::FakeAdmin)
	{
		return false;
	}
}

float GetBulletSpeedPS(Weapon tar, int ammo)
{
	if (ammo == 0) return tar.ammo[0].speed;
	for (Ammo am : tar.ammo) {
		for (int id : am.id) {
			if (id == ammo) {
				return am.speed;
			}
		}
		if (am.id[0] == 0) return am.speed;
	}
	return 250.f;
}

float GetGravityPS(int ammoid) {
	switch (ammoid) {
	case 14241751:
		return 1.f;
	case -1234735557:
		return 0.75f;
	case 215754713:
		return 0.75f;
	case -1023065463:
		return 0.5f;
	case -2097376851:
		return 0.75f;
	case -1321651331:
		return 1.25f;
	default:
		return 1.f;
	}
}

typedef bool(__fastcall* orig_sleeper_)(DWORD64*);
inline orig_sleeper_ orig_sleeper;

typedef bool(__fastcall* orig_getFly_)(DWORD64*);
inline orig_getFly_ orig_getFly;

bool getFly(DWORD64* ModelState) {
	auto out = orig_getFly(ModelState);
	if (Vars::Misc::noclip)
		return false;
	else
		return out;
}

bool issleeper(DWORD64* ModelState) {
	auto out = orig_sleeper(ModelState);
	if (Vars::Misc::issleepers)
		return false;
	else
		return out;
}

Vector3 PredictionPS(Vector3 LP_Pos, BasePlayer* Player, BoneList Bone)
{
	WeaponData* active = LocalPlayer.BasePlayer->GetActiveWeapon();
	Weapon tar = active->Info();
	int ammo = active->LoadedAmmo();
	if (Vars::AimBot::pSilent) {
		Vector3 BonePos = Player->GetBoneByID(Bone);
		float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);
		if (Dist > 0.001f) {
			float speed = GetBulletSpeedPS(tar, ammo) * Vars::AimBot::Velocity;
			if (!speed) speed = 250.f;
			float BulletTime = Dist / speed;
			Vector3 vel = Player->GetVelocity();
			Vector3 PredictVel = vel * BulletTime * 0.75f;
			BonePos += PredictVel;
			float gravity = GetGravityPS(ammo);
			BonePos.y += (4.905f * BulletTime * BulletTime) * gravity;
		}
		return BonePos;
	}
	if (Vars::AimBot::pBody) {
		Vector3 BonePos = Player->GetBoneByID(spine1);
		float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);
		if (Dist > 0.001f) {
			float speed = GetBulletSpeedPS(tar, ammo) * Vars::AimBot::Velocity;
			if (!speed) speed = 250.f;
			float BulletTime = Dist / speed;
			Vector3 vel = Player->GetVelocity();
			Vector3 PredictVel = vel * BulletTime * 0.75f;
			BonePos += PredictVel;
			float gravity = GetGravityPS(ammo);
			BonePos.y += (4.905f * BulletTime * BulletTime) * gravity; // 4.905f
		}
		return BonePos;
	}
}

typedef void(__fastcall* hitsound_fn)(DWORD64);
inline hitsound_fn original_sound;

typedef bool(__fastcall* canrotate)(void*, void*);
inline canrotate original_canrotate;

inline void __fastcall CustomHitsound(DWORD64 info) {
	if (Vars::Misc::CustomHitsound) {

		if (Vars::Misc::HitSound1) {
			PlaySoundW((L"C:\\FrogGang.cc\\Sound\\1.wav"), NULL, SND_ASYNC);
		}

	}
	else {
		return (original_sound)(info);
	}
}


Vector3 __fastcall pSilent(float aimCone, Vector3 inputVec, bool anywhereInside = true) // wanna hang myself
{
	auto* TargetPlayer = reinterpret_cast<BasePlayer*>(TargetPSilentPlayer);
	Vector3 dir = (Prediction(LocalPlayer.BasePlayer->GetBoneByID(head), TargetPlayer, head) - LocalPlayer.BasePlayer->GetBoneByID(head)).Normalized();
	if (Vars::AimBot::pSilent) {
		if (!(TargetPlayer->GetBoneByID(body).x == 0 && TargetPlayer->GetBoneByID(neck).y == 0 && TargetPlayer->GetBoneByID(spine1).z == 0)) {
			return original_aimconedirection(0.f, dir, anywhereInside);
		}
		else {
			return original_aimconedirection(aimCone, inputVec, anywhereInside);
		}
	}
	else return original_aimconedirection(aimCone, inputVec, anywhereInside);
}

void __fastcall ClientInput(DWORD64 baseplayah, DWORD64 ModelState)
{
	typedef void(__stdcall* ClientInput)(DWORD64, DWORD64);
	((ClientInput)original_clientinput)(baseplayah, ModelState);
	if (Vars::Misc::Flyhack)
		LocalPlayer.BasePlayer->AddFlag(32);
	if (Vars::Misc::SilentWalk)
		LocalPlayer.BasePlayer->SetRemoveFlag(4);
	else {
		(Vars::Storage::gBase + 0x1FC1B30); //set_timescale
		(1);
	}
	if (Vars::Misc::SwimOnGround) {
		LocalPlayer.BasePlayer->SetWaterLevel(0.65f);
	}
	typedef void(__stdcall* afamos1)(float);
	if (Vars::Misc::SpeedHack) {
		if (FC(user32, GetAsyncKeyState, Vars::Misc::TimeScalekey))
		{
			afamos1 ss = (afamos1)(Vars::Storage::gBase + 0x1FC1B30); //set_timescale
			ss(2);
		}
		else {
			afamos1 ss = (afamos1)(Vars::Storage::gBase + 0x1FC1B30); //set_timescale
			ss(1);
		}
	}
	static auto IgnoreLayerCollision = reinterpret_cast<void(*)(rust::classes::layer, rust::classes::layer, bool)>(Vars::Storage::uBase + 0xB331A0);
	IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::Water, !Vars::Misc::no_playercollision);
	IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::Tree, Vars::Misc::no_playercollision);
	IgnoreLayerCollision(rust::classes::layer::PlayerMovement, rust::classes::layer::AI, Vars::Misc::no_playercollision);
}


inline void InitHook()
{
	if (MH_Initialize() != MH_OK && MH_Initialize() != MH_ERROR_ALREADY_INITIALIZED)
	{
		std::cout << "Failed to initialize Hook" << std::endl;
		return;

	}
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oSetFlying)), reinterpret_cast<void**>(&original_setflying), get_isFlying);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + 0x3F5D90)), reinterpret_cast<void**>(&original_sound), CustomHitsound);//public void DoHitNotify(HitInfo info) { }
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + 0x20DF480)), reinterpret_cast<void**>(&original_consolerun), Run);//&public static string Run(ConsoleSystem.Option options, string strCommand, object[] args) { }
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + 0x743150)), reinterpret_cast<void**>(&original_create_projectile), CreateProjectile);// private Projectile CreateProjectile(string prefabPath, Vector3 pos, Vector3 forward, Vector3 velocity) { }
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oTodSky)), reinterpret_cast<void**>(&original_mode), NightMode);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oGetSkinColor)), reinterpret_cast<void**>(&original_playerChams), GetSkinColor);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + 0x2F5100)), reinterpret_cast<void**>(&original_canholditems), CanHoldItems);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oGetFlying)), reinterpret_cast<void**>(&orig_getFly), getFly);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + osleeper)), reinterpret_cast<void**>(&orig_sleeper), issleeper);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oClientInput)), reinterpret_cast<void**>(&original_clientinput), ClientInput);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oAimConeUtil)), reinterpret_cast<void**>(&original_aimconedirection), pSilent);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oSendProjectileAttack)), reinterpret_cast<void**>(&Orig_SendProjectileAttack), Fake_SendProjectileAttack);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oCanAttack)), reinterpret_cast<void**>(&Orig_CanAttack), Fake_Can_Attack);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oBlockSprint)), reinterpret_cast<void**>(&Orig_BlockSprint), Fake_BlockSprint);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oGetIndexedSpreadScalar)), reinterpret_cast<void**>(&Orig_GetIndexedSpreadScalar), Fake_GetIndexedSpreadScalar);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oSlideWalk)), reinterpret_cast<void**>(&orig_handleRunning), Fake_handleRunning);
	CreateHook(reinterpret_cast<void*>(static_cast<uintptr_t>(GetModBase(L"GameAssembly.dll") + oAntiAim)), reinterpret_cast<void**>(&original_sendclienttick), hook_sendclienttick);



}

