#define MAX_STRING_LEN 64
float w_last_syringe = 0.f;
bool w_healing = false;

class Str {
	char zpad_[0x10];
public:
	int size;
	wchar_t str[64 + 1];
	Str(const wchar_t* st) {
		size = min(wcslen((const wchar_t*)st), 64);
		for (int i = 0; i < size; i++) {
			str[i] = st[i];
		}
		str[size] = 0;
	}
};

void WeaponPatch()
{
	//pasted by Fe1Zep#7777
	WeaponData* weapon1 = LocalPlayer.BasePlayer->GetActiveWeapon();
	if (Vars::Misc::FastHeal && (weapon1->GetID() == 1079279582 || weapon1->GetID() == -2072273936) && LocalPlayer.BasePlayer->GetHealth() < 95.f) {
		typedef void(__stdcall* afamos1)(DWORD64, Str);
		DWORD64 Held = safe_read(weapon1 + oHeldEntity, DWORD64);
		safe_write(Held + oHeldEntity, 1.f, float); //disable animation
		float curtime = LocalPlayer.BasePlayer->GetTick();
		bool deployed = safe_read(Held + 0x190, bool); // protected bool isDeployed;
		//0x800 secondary
		if (deployed && curtime > w_last_syringe + 0.5f) {
			if (w_healing) {
				afamos1 ss = (afamos1)((DWORD64)Vars::Storage::gBase + oServerRPC); //public void ServerRPC(string funcName) { }
				ss(Held, Str(L"UseSelf"));
			}
			else curtime += 0.1f;
			w_last_syringe = curtime;
			w_healing = true;
		}
		else if (!deployed) {
			w_healing = false;
		}
	}
	else {
		w_healing = false;
	}

	USHORT Hash = 0;
	WeaponData* Weapon = LocalPlayer.BasePlayer->GetActiveWeapon();
	if (Weapon) Hash = Weapon->GetNameHash();

	switch (Hash)
	{

	case 0: return;

	case 0x5A9F:
		Weapon->SuperBow();

		break;

	case 0x6B1:
	case 0x74F5:
	case 0x67DA:
	case 0x3146:
	case 0x79C4:
	case 0x573C:
	case 0xB32A:
	case 0xC196:
		Weapon->FastBullets();
		Weapon->SetAutomatic();

	case 0x7983:
	case 0xE5EA:
	case 0x77E9:
	case 0xE97D:
	case 0xC2DD:
	case 0x52F7:
	case 0xFDC3:
	case 0x62E5:
	case 0x6A09:
	case 0x3511:
	case 0xCFA1:
	case 0xF87E:
		Weapon->FastBullets();
		Weapon->RapidFire();
		Weapon->AntiSpread();
		Weapon->NoRecoil();
	case 0xB0A0:
	case 0x435E:
	{
		if (Hash == 0x435E)
		{
			Weapon->FastBullets();
			Weapon->SetAutomatic();
			Weapon->SuperEoka();
		}
	} break;
	Weapon->FastBullets();


	case 0xF3B9:
		Weapon->BuildAsUWant();
		break;
	case 0xCBD8:
	case 0xAB85:
	case 0xFB2B:
	case 0x6104:
	case 0xC859:
	case 0x96D3:
	case 0x7340:
	case 0xC68B:
	case 0x2F12:
	case 0x65B4:
	case 0x1F2D:
	case 0x2658:
	case 0xAC02:
	case 0x282A:
	case 0x8151:
	case 0xFACE:
	case 0x7296:
	case 0x4B0A:
	case 0xCD:
	case 0x2333:
		if (Vars::Misc::LongHand) {
			Weapon->LongHand();
			Weapon->RunOnHit();
		} break;
	}
}

float GetFov(BasePlayer* Entity, BoneList Bone) {
	Vector2 ScreenPos;
	if (!LocalPlayer.WorldToScreen(Entity->GetBoneByID(Bone), ScreenPos)) return 1000.f;
	return Math::Calc2D_Dist(Vector2(Vars::Global::ScreenWidth / 2, Vars::Global::ScreenHigh / 2), ScreenPos);
}

float GetFovHeli(Vector3 pos)
{
	Vector2 ScreenPos;
	if (!LocalPlayer.WorldToScreen(pos, ScreenPos)) return 1000.f;
	return Math::Calc2D_Dist(Vector2(viewport.Width / 2, viewport.Height / 2), ScreenPos);
}

float GetBulletSpeed()
{
	switch (LocalPlayer.BasePlayer->GetActiveWeapon()->GetNameHash())
	{
	case 0:
		return 0.f;

	case 0x77E9:
		return 420.26f;
		break;

	case 0xCFA1:
		return 656.26f;
		break;

	case 0x573C:
		return 420.05f;
		break;

	case 0x6A09:
		return 960.05f;
		break;

	case 0x7983:
	case 0xE5EA:
	case 0x79C4:
		return 340.05f;
		break;

	case 0xE97D:
		return 192.05f;
		break;

	case 0x3511:
		return 190.05f;
		break;

	case 0x67DA:
		return 260.05f;
		break;

	case 0x62E5:
		return 260.05f;
		break;

	case 0x3146:
		return 250.05f;
		break;

	case 0x6B1:
		return 260.05f;
		break;

	case 0x5A9F:
		return 60.10f;
		break;

	case 0xC196:
		return 60.10f;
		break;

	case 0xB0A0:
		return 95.05f;
		break;

	case 0x746A:
		return 125.05f;
		break;

	default:
		return 250.05f;
	}
}

Vector3 Prediction(const Vector3& LP_Pos, BasePlayer* Player, BoneList Bone)
{
	Vector3 BonePos = Player->GetBoneByID(Bone);
	float Dist = Math::Calc3D_Dist(LP_Pos, BonePos);

	if (Dist > 0.001f) {
		float BulletTime = Dist / GetBulletSpeed();
		Vector3 vel = Player->GetVelocity();
		Vector3 PredictVel = vel * BulletTime * 0.75f;
		BonePos += PredictVel; BonePos.y += (4.905f * BulletTime * BulletTime);
	} return BonePos;
}

void Normalize(float& Yaw, float& Pitch)
{
	if (Pitch < -89) Pitch = -89;
	else if (Pitch > 89) Pitch = 89;
	if (Yaw < -360) Yaw += 360;
	else if (Yaw > 360) Yaw -= 360;
}

void GoToTarget(BasePlayer* player)
{
	Vector3 Local = LocalPlayer.BasePlayer->GetBoneByID(neck);
	Vector3 PlayerPos = Prediction(Local, player, BoneList(Vars::Global::BoneToAim));

	Vector2 Offset = Math::CalcAngle(Local, PlayerPos) - LocalPlayer.BasePlayer->GetVA();
	Vector2 RecoilAng = LocalPlayer.BasePlayer->GetRA();

	Normalize(Offset.y, Offset.x);

	Vector2 AngleToAim = LocalPlayer.BasePlayer->GetVA() + Offset;
	if (Vars::AimBot::RCS) {
		AngleToAim = AngleToAim - RecoilAng;
	}

	Normalize(AngleToAim.y, AngleToAim.x);
	LocalPlayer.BasePlayer->SetVA(AngleToAim);
}
void Aim(BasePlayer* AimEntity)
{

	if (Vars::AimBot::Activate)
	{
		WeaponData* ActWeapon = LocalPlayer.BasePlayer->GetActiveWeapon();
		if (Vars::AimBot::Standalone && Vars::AimBot::RCS)
			LocalPlayer.BasePlayer->SetRA();

		if (AimEntity && !LocalPlayer.BasePlayer->IsMenu()) {
			if (FC(user32, GetAsyncKeyState, Vars::AimBot::aimkey))
				if (ActWeapon) {
					GoToTarget(AimEntity);
				}
		}
	}
}