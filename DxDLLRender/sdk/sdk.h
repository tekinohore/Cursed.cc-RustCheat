

const unsigned short Crc16Table[256] = {
0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50A5, 0x60C6, 0x70E7,
0x8108, 0x9129, 0xA14A, 0xB16B, 0xC18C, 0xD1AD, 0xE1CE, 0xF1EF,
0x1231, 0x0210, 0x3273, 0x2252, 0x52B5, 0x4294, 0x72F7, 0x62D6,
0x9339, 0x8318, 0xB37B, 0xA35A, 0xD3BD, 0xC39C, 0xF3FF, 0xE3DE,
0x2462, 0x3443, 0x0420, 0x1401, 0x64E6, 0x74C7, 0x44A4, 0x5485,
0xA56A, 0xB54B, 0x8528, 0x9509, 0xE5EE, 0xF5CF, 0xC5AC, 0xD58D,
0x3653, 0x2672, 0x1611, 0x0630, 0x76D7, 0x66F6, 0x5695, 0x46B4,
0xB75B, 0xA77A, 0x9719, 0x8738, 0xF7DF, 0xE7FE, 0xD79D, 0xC7BC,
0x48C4, 0x58E5, 0x6886, 0x78A7, 0x0840, 0x1861, 0x2802, 0x3823,
0xC9CC, 0xD9ED, 0xE98E, 0xF9AF, 0x8948, 0x9969, 0xA90A, 0xB92B,
0x5AF5, 0x4AD4, 0x7AB7, 0x6A96, 0x1A71, 0x0A50, 0x3A33, 0x2A12,
0xDBFD, 0xCBDC, 0xFBBF, 0xEB9E, 0x9B79, 0x8B58, 0xBB3B, 0xAB1A,
0x6CA6, 0x7C87, 0x4CE4, 0x5CC5, 0x2C22, 0x3C03, 0x0C60, 0x1C41,
0xEDAE, 0xFD8F, 0xCDEC, 0xDDCD, 0xAD2A, 0xBD0B, 0x8D68, 0x9D49,
0x7E97, 0x6EB6, 0x5ED5, 0x4EF4, 0x3E13, 0x2E32, 0x1E51, 0x0E70,
0xFF9F, 0xEFBE, 0xDFDD, 0xCFFC, 0xBF1B, 0xAF3A, 0x9F59, 0x8F78,
0x9188, 0x81A9, 0xB1CA, 0xA1EB, 0xD10C, 0xC12D, 0xF14E, 0xE16F,
0x1080, 0x00A1, 0x30C2, 0x20E3, 0x5004, 0x4025, 0x7046, 0x6067,
0x83B9, 0x9398, 0xA3FB, 0xB3DA, 0xC33D, 0xD31C, 0xE37F, 0xF35E,
0x02B1, 0x1290, 0x22F3, 0x32D2, 0x4235, 0x5214, 0x6277, 0x7256,
0xB5EA, 0xA5CB, 0x95A8, 0x8589, 0xF56E, 0xE54F, 0xD52C, 0xC50D,
0x34E2, 0x24C3, 0x14A0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
0xA7DB, 0xB7FA, 0x8799, 0x97B8, 0xE75F, 0xF77E, 0xC71D, 0xD73C,
0x26D3, 0x36F2, 0x0691, 0x16B0, 0x6657, 0x7676, 0x4615, 0x5634,
0xD94C, 0xC96D, 0xF90E, 0xE92F, 0x99C8, 0x89E9, 0xB98A, 0xA9AB,
0x5844, 0x4865, 0x7806, 0x6827, 0x18C0, 0x08E1, 0x3882, 0x28A3,
0xCB7D, 0xDB5C, 0xEB3F, 0xFB1E, 0x8BF9, 0x9BD8, 0xABBB, 0xBB9A,
0x4A75, 0x5A54, 0x6A37, 0x7A16, 0x0AF1, 0x1AD0, 0x2AB3, 0x3A92,
0xFD2E, 0xED0F, 0xDD6C, 0xCD4D, 0xBDAA, 0xAD8B, 0x9DE8, 0x8DC9,
0x7C26, 0x6C07, 0x5C64, 0x4C45, 0x3CA2, 0x2C83, 0x1CE0, 0x0CC1,
0xEF1F, 0xFF3E, 0xCF5D, 0xDF7C, 0xAF9B, 0xBFBA, 0x8FD9, 0x9FF8,
0x6E17, 0x7E36, 0x4E55, 0x5E74, 0x2E93, 0x3EB2, 0x0ED1, 0x1EF0
};

enum BoneList : int
{
	l_hip = 1,
	l_knee,
	l_foot,
	l_toe,
	l_ankle_scale,
	pelvis,
	penis,
	GenitalCensor,
	GenitalCensor_LOD0,
	Inner_LOD0,
	GenitalCensor_LOD1,
	GenitalCensor_LOD2,
	r_hip,
	r_knee,
	r_foot,
	r_toe,
	r_ankle_scale,
	spine1,
	spine1_scale,
	spine2,
	spine3,
	spine4,
	l_clavicle,
	l_upperarm,
	l_forearm,
	l_hand,
	l_index1,
	l_index2,
	l_index3,
	l_little1,
	l_little2,
	l_little3,
	l_middle1,
	l_middle2,
	l_middle3,
	l_prop,
	l_ring1,
	l_ring2,
	l_ring3,
	l_thumb1,
	l_thumb2,
	l_thumb3,
	IKtarget_righthand_min,
	IKtarget_righthand_max,
	l_ulna,
	neck,
	head,
	body,
	jaw,
	eyeTranform,
	l_eye,
	l_Eyelid,
	r_eye,
	r_Eyelid,
	r_clavicle,
	r_upperarm,
	r_forearm,
	r_hand,
	r_index1,
	r_index2,
	r_index3,
	r_little1,
	r_little2,
	r_little3,
	r_middle1,
	r_middle2,
	r_middle3,
	r_prop,
	r_ring1,
	r_ring2,
	r_ring3,
	r_thumb1,
	r_thumb2,
	r_thumb3,
	IKtarget_lefthand_min,
	IKtarget_lefthand_max,
	r_ulna,
	l_breast,
	r_breast,
	BoobCensor,
	BreastCensor_LOD0,
	BreastCensor_LOD1,
	BreastCensor_LOD2,
	collision,
	displacement
};

enum PlayerFlags : int
{
	Unused1 = 1,
	Unused2 = 2,
	IsAdmin = 4,
	ReceivingSnapshot = 8,
	Sleeping = 16,
	Spectating = 32,
	Wounded = 64,
	IsDeveloper = 128,
	Connected = 256,
	ThirdPersonViewmode = 1024,
	EyesViewmode = 2048,
	ChatMute = 4096,
	NoSprint = 8192,
	Aiming = 16384,
	DisplaySash = 32768,
	Relaxed = 65536,
	SafeZone = 131072,
	ServerFall = 262144,
	Workbench1 = 1048576,
	Workbench2 = 2097152,
	Workbench3 = 4194304,
};

typedef struct _UncStr
{
	char stub[0x10];
	int len;
	wchar_t str[1];
} *pUncStr;

class WeaponData
{
private:
	unsigned short CRC(unsigned char* pcBlock, unsigned short len)
	{
		unsigned short crc = 0xFFFF;
		while (len--)
			crc = (crc << 8) ^ Crc16Table[(crc >> 8) ^ *pcBlock++];
		return crc;
	}

public:

	char* ClassName()
	{
		return (char*)safe_read(safe_read(safe_read(this + oHeldEntity, DWORD64), DWORD64) + 0x10, DWORD64);
	}

	wchar_t* GetShortName(int* len)
	{
		DWORD64 Info = safe_read(this + ItemDefinition, DWORD64);
		pUncStr Str = ((pUncStr)safe_read(Info + oShortname, DWORD64));
		int leng = safe_read(Str + 0x10, int);
		if (!leng) return nullptr;
		if (len)*len = leng;
		return Str->str;
	}

	void RapidFire() {
		if (Vars::AimBot::RapidFire) {
			DWORD64 heldentity = safe_read(this + oHeldEntity, DWORD64);
			safe_write(heldentity + 0x1E4, 0.09f, float); // repeatDelay
		}
	}

	int LoadedAmmo()
	{
		const auto Held = safe_read(this + oHeldEntity, DWORD64);
		if (Held <= 0)
			return 0;
		const auto Magazine = safe_read(Held + oPrimaryMagazine, DWORD64);
		if (Magazine <= 0 || Magazine == 0x3F000000)
		{
			return 0;
		}
		const auto ammoType = safe_read(Magazine + 0x20, DWORD64);
		if (ammoType <= 0 || ammoType == 0x3F000000)
		{
			return 0;
		}
		const int ammo = safe_read(ammoType + 0x18, int);
		return ammo;
	}
	void FastBullets()
	{
		if (Vars::AimBot::FastBullet)
		{
			DWORD64 Held = safe_read(this + 0x98, DWORD64);
			safe_write(Held + 0x5B0, Vars::AimBot::SpeedBullets, float); //public float bulletSpeed; // 0x550
			//0x2E4 Мб это ещё
		}
	}
	typedef struct _UncStr
	{
		char stub[0x10];
		int len;
		wchar_t str[1];
	} *pUncStr;

	void BuildAsUWant()
	{
		DWORD64 Held = safe_read(this + oHeldEntity, DWORD64);
		DWORD64 Construction = safe_read(Held + oHornOrigin, DWORD64);
		if (Vars::Misc::BuildAsUWant && FC(user32, GetAsyncKeyState, Vars::Misc::buildkey)) safe_write(Construction + 0xEC, 15, int);
		if (!Vars::Misc::BuildAsUWant) safe_write(Construction + 0x1E0, 180, int);
		// private Vector3 rotationOffset
	}

	USHORT GetNameHash()
	{
		int Len;
		UCHAR* ShortName = (UCHAR*)GetShortName(&Len);
		if (ShortName == nullptr) return 0;
		return CRC(ShortName, (Len * 2));
	}

	wchar_t* GetName()
	{
		DWORD64 Info = safe_read(this + ItemDefinition, DWORD64);
		DWORD64 DispName = safe_read(Info + odisplayname, DWORD64);
		pUncStr Str = ((pUncStr)safe_read(DispName + 0x18, DWORD64)); // default
		if (!Str) return nullptr; return Str->str;
	}

	int GetUID()
	{
		//cout <<"UID: "<< safe_read(this + oUID, int) << '\n';
		return safe_read(this + oUID, int);
	}

	int GetID() {
		DWORD64 Info = safe_read((DWORD64)this + 0x20, DWORD64);
		int ID = safe_read(Info + 0x18, int);
		return ID;
	}

	Weapon Info() {
		int ID = GetID();
		for (Weapon k : info) {
			if (k.id == ID) {
				return k;
			}
		}
		return Weapon{ 0 };
	}

	void AntiSpread()
	{
		if (Vars::Misc::AntiSpread)
		{
			DWORD64 Held = safe_read(this + oHeldEntity, DWORD64);
			safe_write(Held + oStancePenalty, 0.f, float);
			safe_write(Held + oAimconePenalty, 0.f, float);
			safe_write(Held + oAimCone, 0.f, float);
			safe_write(Held + oHipAimCone, 0.f, float);
			safe_write(Held + oAimconePenaltyPerShot, 0.f, float);
		}
	}

	void NoRecoil()
	{
		if (Vars::Misc::NoRecoil)
		{
			DWORD64 Held = safe_read(this + oHeldEntity, DWORD64);
			DWORD64 recoil = safe_read(Held + oRecoil, DWORD64);
			safe_write(recoil + oRecoilYawMin, 0.4f, float);
			safe_write(recoil + oRecoilYawMax, 0.5f, float);
			safe_write(recoil + oRecoilPitchMin, 0.4f, float);
			safe_write(recoil + oRecoilPitchMax, 0.5f, float);
			safe_write(recoil + oADSScale, 0.4f, float);
			safe_write(recoil + oMovementPenalty, 0.f, float);
		}
	}

	void SetAutomatic()
	{
		if (Vars::Misc::Automatic)
		{
			DWORD64 Held = safe_read(this + oHeldEntity, DWORD64);
			safe_write(Held + oAutomatic, 1, bool);
		}
	}

	void SuperEoka()
	{
		if (Vars::Misc::SuperEoka)
		{
			DWORD64 Held = safe_read(this + oHeldEntity, DWORD64);
			safe_write(Held + oSuccessFraction, 1.f, float);
			safe_write(Held + 0x360, true, bool);//private bool _didSparkThisFrame; // 0x350 ??
		}
	}

	void SuperBow()
	{
		if (Vars::Misc::SuperBow)
		{
			DWORD64 Held = safe_read(this + oHeldEntity, DWORD64);
			safe_write(Held + oAttackReady, 1, bool);
			safe_write(Held + oArrowBack, 1.f, float);
		}
	}

	//inline void FatBullet()
	//{
	//	if (Vars::AimBot::FatBullet)
	//	{
	//		DWORD64 Held = safe_read(this + 0x98, DWORD64); //	private EntityRef heldEntity; // 0x90
	//		DWORD64 List = safe_read(Held + 0x348, DWORD64); //private List<Projectile> createdProjectiles; // 0x338
	//		int size = safe_read(List + 0x18, DWORD64);
	//		List = safe_read(List + 0x10, DWORD64);
	//		{
	//			for (int i = 0; i < size; ++i)
	//			{
	//				UINT64 Item = safe_read(List + 0x20 + (i * 0x8), UINT64);
	//				safe_write(Item + 0x2C, 1.f, float); //public float thickness; // 0x2C??
	//			}
	//		}

	//	}
	//}

	void LongHand()
	{
		DWORD64 Held = safe_read(this + oHeldEntity, DWORD64);
		safe_write(Held + 0x280, 5.f, float); //public float maxDistance; public class BaseMelee : AttackEntity // TypeDefIndex: 8803
	}

	void RunOnHit()
	{
		DWORD64 Held = safe_read(this + oHeldEntity, DWORD64);
		safe_write(Held + oBlockSprintOnAttack, 0, int);
	}

};

class BasePlayer
{
public:
	//*** base entity info ***//
	float GetHealth()
	{
		return safe_read(this + oHealth, float);
	}

	void mouse_move() {

		SetCursorPos(826, 500);
		Sleep(100);

		// first slot
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(20);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(50);
		SetCursorPos(1200, 500);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(30);
		SetCursorPos(1380, 700);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		// first slot done

		Sleep(50);
		SetCursorPos(1200, 500);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(30);
		SetCursorPos(1450, 700);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

		Sleep(200);
		SetCursorPos(1150, 500);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);

		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		Sleep(200);
		SetCursorPos(1200, 500);
		Sleep(200);
		mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		Sleep(30);
		SetCursorPos(1615, 700);
		Sleep(50);
		mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);

	}

	void AddFlag(int flag)
	{
		DWORD64 mstate = safe_read(this + 0x588, DWORD64);
		int flags = safe_read(mstate + 0x24, int);
		safe_write(mstate + 0x24, flags |= flag, int);
	}

	void SetWaterLevel(float val) {
		DWORD64 mstate = safe_read(this + 0x5C8, DWORD64);
		safe_write(mstate + 0x14, val, float);
	}

	float GetTick() {
		return safe_read(this + oLastSentTickTime, float);
	}

	void SetRemoveFlag(int flag)
	{
		DWORD64 mstate = safe_read(this + 0x5C8, DWORD64);//public ModelState modelState; // 0x588
		int flags = safe_read(mstate + 0x24, int);// 	public int flags; // 0x24
		safe_write(mstate + 0x24, flags &= ~flag, int);//	public int flags; // 0x24
	}

	void PatchDebug()
	{
		DWORD64 Client = safe_read(GetModBase((L"GameAssembly.dll")) + 0x307BC48 + 0xB8, DWORD64); // ConVar_Client_c*
		safe_write(Client + 0x2C, 1.f, float); // camspeed
		safe_write(Client + 0x20, 1.f, float); // camlerp
	}

	void AirStuck(bool state)
	{
		safe_write(this + 0x4B8, state, bool); //public bool Frozen;
		//РАБОТАЕТ
	}

	void FakeThirdPerson(int Val) {
		int Flags = safe_read(this + 0x638, int); //public BasePlayer.PlayerFlags playerFlags;
		safe_write(this + 0x638, (Flags |= 1024), int);
	}

	void LongNeck(float val) 
	{
		if (FC(user32, GetAsyncKeyState, Vars::Misc::LongNeckkey))
		{
			DWORD64 eyes = safe_read(this + 0x640, DWORD64); //public PlayerEyes eyes; // 0x640
			safe_write(eyes + 0x38, Vector3(0, (0.8f), 0), Vector3);
		}
	}
	void SetFov()
	{
		auto klass = safe_read(Vars::Storage::gBase + oConVar, DWORD64);
		auto static_fields = safe_read(klass + 0xB8, DWORD64);
		safe_write(static_fields + 0x18, Vars::Misc::GraphicsFov, float);
	}

	void Zoom()
	{

		if (FC(user32, GetAsyncKeyState, Vars::Misc::Zoomkey))
		{

			auto klass = safe_read(Vars::Storage::gBase + oConVar, DWORD64);
			auto static_fields = safe_read(klass + 0xB8, DWORD64);
			safe_write(static_fields + 0x18, Vars::Misc::Zoomvalue, float);
		}
		else
		{
			auto klass = safe_read(Vars::Storage::gBase + oConVar, DWORD64);
			auto static_fields = safe_read(klass + 0xB8, DWORD64);
			safe_write(static_fields + 0x18, Vars::Misc::GraphicsFov, float);
		}
	}

	const wchar_t* GetName()
	{
		pUncStr Str = ((pUncStr)(safe_read(this + oDisplayName, DWORD64)));
		if (!Str) return L""; return Str->str;
	}

	Vector3 GetVelocity()
	{
		DWORD64 PlayerModel = safe_read(this + oPlayerModel, DWORD64);
		return safe_read(PlayerModel + oNewVelocity, Vector3);
	}

	bool IsNpc() {
		DWORD64 PlayerModel = safe_read(this + 0x4B0, DWORD64); //	public PlayerModel playerModel;
		return safe_read(PlayerModel + 0x2C0, bool);
	}

	bool IsVisible() {
		if (Vars::AimBot::VisibleCheck)
		{
			DWORD64 PlayerModel = safe_read(this + oPlayerModel, DWORD64);
			return safe_read(PlayerModel + oVisible, bool);
		}
		else return true;
	}

	float GetTickTime() {
		return safe_read(this + oLastSentTickTime, float);
	}

	bool IsValid(bool LPlayer = false)
	{
		return (((LPlayer || Vars::Visuals::IgnoreSleepers) ? !HasFlags(16) : true) && !IsDead() && (GetHealth() >= 0.8f));
	}

	bool HasFlags(int Flg) {
		return (safe_read(this + oPlayerFlags, int) & Flg);
	}


	Vector3 GetBoneByID(BoneList BoneID)
	{
		return GetPosition(GetTransform(BoneID));
	}

	bool IsDead()
	{
		if (!this) return true;
		return safe_read(this + oLifeState, bool);;
	}

	bool HasFlag(int PlayerFlag)
	{
		return (safe_read(this + oPlayerFlags, DWORD64) & PlayerFlag);
	}

	bool IsSleeping()
	{
		if (!this) return false;
		return HasFlag(Sleeping);
	}

	bool IsWounded()
	{
		if (!this) return false;
		return HasFlag(Wounded);
	}

	DWORD64 GetSteamID() {
		return safe_read(this + oUserID, DWORD64);
	}

	//*** localplayer ***//
	bool IsMenu()
	{
		if (!this) return true;
		DWORD64 Input = safe_read(this + oPlayerInput, DWORD64);
		return !(safe_read(Input + oKeyFocus, bool));
	}

	void SetVA(const Vector2& VA)
	{
		DWORD64 Input = safe_read(this + oPlayerInput, DWORD64);
		safe_write(Input + oBodyAngles, VA, Vector2);
	}

	Vector2 GetVA()
	{
		DWORD64 Input = safe_read(this + oPlayerInput, DWORD64);
		return safe_read(Input + oBodyAngles, Vector2);
	}

	void SetRA() {
		if (Vars::AimBot::RCS) {
			DWORD64 Input = safe_read(this + oPlayerInput, DWORD64);//	public PlayerInput input;
			Vector2 RA = { 0.f, 0.f };
			safe_write(Input + oRecoilAngles, RA, Vector2); //public Vector3 recoilAngles;
		}
	}

	Vector2 GetRA()
	{
		DWORD64 Input = safe_read(this + oPlayerInput, DWORD64);
		return safe_read(Input + oRecoilAngles, Vector2);
	}

	WeaponData* GetWeaponInfo(int Id)
	{
		DWORD64 Inventory = safe_read(this + oInventory, DWORD64);
		DWORD64 Belt = safe_read(Inventory + 0x28, DWORD64);
		DWORD64 ItemList = safe_read(Belt + 0x38, DWORD64);// public List<Item> itemList;
		DWORD64 Items = safe_read(ItemList + 0x10, DWORD64); //	public List<InventoryItem.Amount> items;
		return (WeaponData*)safe_read(Items + 0x20 + (Id * 0x8), DWORD64);
	}

	WeaponData* GetActiveWeapon()
	{
		int ActUID = safe_read(this + oClActiveItem, int);
		if (!ActUID) return nullptr;
		WeaponData* ActiveWeapon;
		for (int i = 0; i < 6; i++)
			if (ActUID == (ActiveWeapon = GetWeaponInfo(i))->GetUID())
				return ActiveWeapon;
		return nullptr;
	}

	void WaterBoost()
	{
		safe_write(this + 0x700, 0.65f, float); //	public float clothingWaterSpeedBonus;
		//РАБОТАЕТ
	}

	void FakeWorkBench(int Val)
	{
		int Flags = safe_read(this + 0x638, int); //public BasePlayer.PlayerFlags playerFlags;
		safe_write(this + 0x638, (Flags |= 4194304), int);
	}

	void FakeAdmin(int Val)
	{
		int Flags = safe_read(this + oPlayerFlags, int);
		safe_write(this + oPlayerFlags, (Flags |= 4), int);

	}

	void Pizda228() {
		if (Vars::Visuals::NightMode)
		{
			static DWORD64 dwGameObjectManager = 0;
			if (!dwGameObjectManager)
				dwGameObjectManager = safe_read(GetModBase(StrW(L"UnityPlayer.dll")) + oGameObjectManager, UINT64);
			DWORD64 ObjMgr = safe_read(dwGameObjectManager, DWORD64); if (!ObjMgr) return;
			DWORD64 Obj = safe_read(ObjMgr + 0x8, DWORD64); (Obj && (Obj != safe_read(ObjMgr, DWORD64))); Obj = safe_read(Obj + 0x8, DWORD64);
			DWORD64 GameObject = safe_read(Obj + 0x10, DWORD64);
			DWORD64 ObjClass = safe_read(GameObject + 0x30, DWORD64);
			DWORD64    Entity = safe_read(ObjClass + 0x18, DWORD64);
			DWORD64 Dome = safe_read(Entity + 0x28, DWORD64);
			DWORD64 TodCycle = safe_read(Dome + 0x38, DWORD64);
			safe_write(TodCycle + 0x10, 01.00f, float);
			return;
		}
		return;
	}

	void instarevive()
	{
		if (Vars::Misc::instarevive)
		{
			DWORD64 PlayerModel = safe_read(this + 0x4A8, DWORD64);
			DWORD64 Instane = safe_read(PlayerModel + 0x498, DWORD64); //private Vector3 lastRevivePoint; // 0x490
			safe_write(Instane + 0x18, 1.f, DWORD64);
		}
	}

	void FastMelee()
	{
		if (Vars::Misc::fastmelee)
		{
			DWORD64 HeldItem = safe_read(this + 0x98, DWORD64);
			safe_write(HeldItem + 0x248, 5.f, float); //private float speedFast;
		}
	}

	void SpiderMan()
	{
		DWORD64 Movement = safe_read(this + oMovement, DWORD64);
		safe_write(Movement + oGroundAngle, 0.f, float);
		safe_write(Movement + oGroundAngleNew, 0.f, float);
	}

	void InfinityJump()
	{
		INT64 Movement = safe_read((const uintptr_t)this + oMovement, UINT64);
		safe_write(Movement + oGroundAngleNew, Vector3(0, 1000000, 0), Vector3);
		safe_write(Movement + oGroundAngle, Vector3(9999999, 9999999, 9999999), Vector3);
	}

	void NoSway()
	{
		safe_write(this + oClothingAccuracyBonus, 1.f, float);
	}

	void NoBlockAiming()
	{
		safe_write(this + oClothingBlocksAiming, false, bool);
	}

	int GetTeamSize()
	{
		DWORD64 ClientTeam = safe_read(this + oClientTeam, DWORD64);
		DWORD64 members = safe_read(ClientTeam + 0x28, DWORD64);//	private ListHashSet<ILOD> members; //public PlayerInventory inventory; // 0x28 ���  public List<PlayerTeam.TeamMember> members; // 0x28
		return safe_read(members + 0x18, DWORD64);
	}
	DWORD64 GetTeammateByPos(int Id) {
		DWORD64 ClientTeam = safe_read(this + 0x580, DWORD64);//	public PlayerTeam clientTeam;
		DWORD64 members = safe_read(ClientTeam + 0x30, DWORD64);//	private ListHashSet<ILOD> members; // 0x28 ���  public List<PlayerTeam.TeamMember> members; // 0x28
		DWORD64 List = safe_read(members + 0x10, DWORD64);
		DWORD64 player = safe_read(List + 0x20 + (Id * 0x8), DWORD64); // 	private BasePlayer player;
		return safe_read(player + 0x18, DWORD64);
	}
	bool IsTeamMate(DWORD64 SteamID) {
		bool ret = false;

		for (int i = 0; i < 8; i++) {
			if (GetTeammateByPos(i) == SteamID) {
				ret = true;
				break;
			}
		}
		return ret;
	}

	void NoHeavyReduct()
	{
		float Reduct = safe_read(this + oClothingMoveSpeedReduction, float);
		if (Reduct == 0.f) { safe_write(this + oClothingMoveSpeedReduction, -0.1f, float); }
		else if ((Reduct > 0.15f) && (Reduct < 0.35f))
		{
			safe_write(this + oClothingMoveSpeedReduction, 0.15f, float);
		}
		else if (Reduct > 0.39f)
		{
			safe_write(this + oClothingMoveSpeedReduction, 0.15f, float);
		}
	}

	void Swim()
	{
		if (Vars::Misc::swiming)
		{
			DWORD64 ModelState = safe_read(this + 0x578, DWORD64);
			if (!ModelState)
				return;

			safe_write(ModelState + 0x13C, 1, bool); // private bool flying;
			safe_write(ModelState + 0x700, 1.f, float); //	public float clothingWaterSpeedBonus;
			safe_write(ModelState + 0x13C, Vars::Misc::SetSwim, float); // private bool flying;
		}
	}

	void SetGravity(float val)
	{
		DWORD64 Movement = safe_read(this + oMovement, DWORD64);
		safe_write(Movement + oGravityMultiplier, val, float);
	}

	Vector3 GetPosition()
	{
		return GetPosition(GetTransform(r_foot)).midPoint(GetPosition(GetTransform(l_foot)));
	}

	Vector3 GetEulerAngles()
	{
		return EulerAngles(GetTransform(r_foot)).midPoint(EulerAngles(GetTransform(l_foot)));
	}

private:
	typedef Vector3(__stdcall* Transform)(UINT64);
	Vector3 GetPosition(ULONG_PTR pTransform) {
		if (!pTransform) return Vector3();
		Transform original = (Transform)(Vars::Storage::gBase + oPosition);
		Vector3 res = original(pTransform);
		return res;
	}
	DWORD64 GetTransform(int bone)
	{
		DWORD64 player_model = safe_read(this + 0x120, DWORD64);// public Model model;_public class BaseEntity : BaseNetworkable, IProvider, ILerpTarget, IPrefabPreProcess // TypeDefIndex: 8714
		DWORD64 boneTransforms = safe_read(player_model + 0x48, DWORD64);//public Transform[] boneTransforms;
		DWORD64 BoneValue = safe_read((boneTransforms + (0x20 + (bone * 0x8))), DWORD64);
		return BoneValue;
	}
	static Vector3 EulerAngles(ULONG_PTR pTransform)
	{
		if (pTransform < 0xFFF)
			return Vector3();
		const auto original = reinterpret_cast<Transform>(GetModBase(StrW(L"GameAssembly.dll")) + oEulerAngles);
		const Vector3 Result = original(pTransform);
		return Result;
	}
};
//Base Player
class LPlayerBase
{
public:
	BasePlayer* BasePlayer = nullptr;
	Matrix4x4* pViewMatrix = nullptr;
	bool WorldToScreen(const Vector3& EntityPos, Vector2& ScreenPos)
	{
		if (!pViewMatrix) return false;
		Vector3 TransVec = Vector3(pViewMatrix->_14, pViewMatrix->_24, pViewMatrix->_34);
		Vector3 RightVec = Vector3(pViewMatrix->_11, pViewMatrix->_21, pViewMatrix->_31);
		Vector3 UpVec = Vector3(pViewMatrix->_12, pViewMatrix->_22, pViewMatrix->_32);
		float w = Math::Dot(TransVec, EntityPos) + pViewMatrix->_44;
		if (w < 0.098f) return false;
		float y = Math::Dot(UpVec, EntityPos) + pViewMatrix->_42;
		float x = Math::Dot(RightVec, EntityPos) + pViewMatrix->_41;
		ScreenPos = Vector2((Vars::Global::ScreenWidth / 2) * (1.f + x / w), (Vars::Global::ScreenHigh / 2) * (1.f - y / w));
		return true;
	}
};

DECLSPEC_NOINLINE void Flex()
{
	FC(kernel32, Sleep, 0);
}

LPlayerBase LocalPlayer;