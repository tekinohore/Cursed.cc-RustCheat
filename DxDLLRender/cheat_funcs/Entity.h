bool mfound = false;
void ESP(BasePlayer* BP, BasePlayer* LP);
inline void RadarPlayer(BasePlayer* player);
void RenderActiveSlot(BasePlayer* player, float Pos_x, float Pos_Y);
BasePlayer* Player;
D3DCOLOR FLOAT4TOD3DCOLOR(float Col[]);
void FindMatrix() {
	static DWORD64 dwGameObjectManager = 0;
	if (!dwGameObjectManager)
		dwGameObjectManager = RVA(FindPattern((PBYTE)"\x48\x8B\x15\x00\x00\x00\x00\x66\x39", "xxx????xx", L"UnityPlayer.dll"), 7);

	DWORD64 ObjMgr = safe_read(dwGameObjectManager, DWORD64);
	if (!ObjMgr) return;
	UINT64 end = safe_read(ObjMgr, UINT64);
	for (UINT64 Obj = safe_read(ObjMgr + 0x8, UINT64); (Obj && (Obj != end)); Obj = safe_read(Obj + 0x8, UINT64))
	{
		UINT64 GameObject = safe_read(Obj + 0x10, UINT64);
		WORD Tag = safe_read(GameObject + 0x54, WORD);
		if (Tag == 5)
		{
			UINT64 ObjClass = safe_read(GameObject + 0x30, UINT64);
			UINT64	Entity = safe_read(ObjClass + 0x18, UINT64);
			LocalPlayer.pViewMatrix = (Matrix4x4*)(Entity + 0x2E4);// 0xDC
			mfound = true;
			return;
		}
	}
}

void PickupItem(DWORD64 item)
{
	typedef void(__stdcall* Pick)(DWORD64, Str);
	return ((Pick)(GetModBase(L"GameAssembly.dll") + oServerRPC))(item, Str(L"Pickup"));
}
int dlastKnock;
int dlastOpen;
void EbynMozga(DWORD64 Door) {
	typedef void(__stdcall* Daun)(DWORD64, BasePlayer*);
	float time = LocalPlayer.BasePlayer->GetTickTime();
	if (time > dlastKnock + 1.f)
	{
		//0x493CC0
		((Daun)(GetModBase(L"GameAssembly.dll") + oKnockDoor))(Door, LocalPlayer.BasePlayer);
		dlastKnock = time;
	}

	if (time > dlastOpen + 1.f)
	{
		//0x493D40
		((Daun)(GetModBase(L"GameAssembly.dll") + oKnockDoor))(Door, LocalPlayer.BasePlayer);
		dlastOpen = time;
	}

}

inline void FakeLag()
{
	if (Vars::Misc::FakeLag)
	{
		safe_write(reinterpret_cast<uintptr_t>(LocalPlayer.BasePlayer) + oClientTickInterval, 0.4f, float);
	}
	else
	{
		safe_write(reinterpret_cast<uintptr_t>(LocalPlayer.BasePlayer) + oClientTickInterval, 0.05f, float);
	}
}

class Qlist {
public:
	template <typename T>
	T get_value() {
		auto list = *reinterpret_cast<uintptr_t*>(this + 0x10);
		if (!list)
			return 0;

		auto value = *reinterpret_cast<T*>(list + 0x28);
		if (!value)
			return 0;
		return value;
	}

	int get_size() {
		auto value = get_value<uintptr_t>();
		if (!value)
			return 0;

		auto size = safe_read(value + 0x10, int);
		if (!size)
			return 0;
	}

	template <typename T>
	T get_buffer() {
		auto value = get_value<uintptr_t>();

		return *reinterpret_cast<uintptr_t*>(value + 0x18);
	}
};

class AimResult
{
public:
	bool valid;
	BasePlayer* entity;
	Vector3 pos;
	float dist = 10000.f;
	float realdist = 0.f;
	float fov = 10000.f;

	bool operator<(const AimResult& b)
	{
		if (fov == 10000.f) {
			return this->dist < b.dist;
		}
		else {
			return this->fov < b.fov;
		}
	}

	AimResult() {
		this->valid = false;
		this->fov = 10000.f;
	}
	AimResult(Vector3 target)
	{
		this->valid = false;
		this->pos = target;
	}
};

float CurFOV;
BasePlayer* SilentTargetedPlayer = 0;

AimResult TargetMeleeTest(BasePlayer* Player, DWORD64 melee)
{
	AimResult res = AimResult();
	if (!Player || !Player->IsValid()) return res;

	if (Player->IsWounded()) return res;
	/*if (!Vars::Aim::AimOnSleepers && Player->IsSleeping()) return res;
	if (!Vars::Aim::AimOnTeam && Player->IsTeamMate()) return res;*/
	typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);

	Vector3 prepos = Player->GetBoneByID(BoneList::head);
	Vector3 lppos = LocalPlayer.BasePlayer->GetBoneByID(head);
	/*res.valid = PLOS(lppos, target);*/
	if (!res.valid) return res;

	/*res.dist = realdist;
	res.entity = Player;
	res.pos = target;
	return res;*/
}

void Entity()
{
	bool LP_isValid = true;
	float FOV = 1000000.f;
	BasePlayer* AimEntity = 0;
	BasePlayer* TargetAimBotPlayer = nullptr;
	BasePlayer* AimEntity2 = 0;

	if (!LocalPlayer.pViewMatrix || !mfound)
	{
		FindMatrix();
	}


	DWORD64 BaseNetworkable;
	BaseNetworkable = safe_read(GetModBase(StrW(L"GameAssembly.dll")) + oBaseNetworkable, DWORD64);
	DWORD64 EntityRealm = safe_read(BaseNetworkable + 0xB8, DWORD64);
	DWORD64 ClientEntities = safe_read(EntityRealm, DWORD64);
	DWORD64 ClientEntities_list = safe_read(ClientEntities + 0x10, DWORD64);
	DWORD64 ClientEntities_values = safe_read(ClientEntities_list + 0x28, DWORD64);
	if (!ClientEntities_values) return;
	int EntityCount = safe_read(ClientEntities_values + 0x10, int);
	DWORD64 EntityBuffer = safe_read(ClientEntities_values + 0x18, DWORD64);

	for (int i = 0; i <= EntityCount; i++)
	{
		DWORD64 Entity = safe_read(EntityBuffer + 0x20 + (i * 0x8), DWORD64);
		if (Entity <= 100000) continue;
		DWORD64 Object = safe_read(Entity + 0x10, DWORD64); //BaseObject
		if (Object <= 100000) continue;
		DWORD64 ObjectClass = safe_read(Object + 0x30, DWORD64); //Object
		//
		WORD tag = safe_read(ObjectClass + 0x54, WORD);
		uintptr_t localElement = safe_read(EntityBuffer + 0x20, uintptr_t);
		//
		if (ObjectClass <= 100000) continue;

		DWORD64 ent = safe_read(Object + 0x28, UINT64);
		pUncStr name = safe_read(ObjectClass + 0x60, pUncStr);
		uintptr_t BaseObject = safe_read(ObjectClass + 0x30, uintptr_t);
		uintptr_t BaseEntity = safe_read(BaseObject + 0x18, uintptr_t);
		uintptr_t BaseHelicopter = safe_read(BaseEntity + 0x28, uintptr_t);
		if (!name) continue;
		char* buff = name->stub;
		//std::cout << buff << '\n';
		BasePlayer* Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64); //strstr(buff, "npc") ||
		if (strstr(buff, StrA("Local"))) {
			Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64);
			if (!safe_read(Player + oPlayerModel, DWORD64)) continue; // public PlayerModel playerModel;???
			if (Player != LocalPlayer.BasePlayer /*lp changed*/)
			{
				//printf("LocalPlayer %lld\n", Player->GetSteamID());
				mfound = false;
			}
			//printf("lp pos %f %f %f\n", pos.x, pos.y, pos.z);
			LocalPlayer.BasePlayer = Player;
			LP_isValid = true;


		}

		else if (strstr(buff, "player.prefab") || (strstr(buff, "scientist")) && (!strstr(buff, "prop") && !strstr(buff, "corpse")))
		{
			BasePlayer* Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64); //public ulong playerID;
			if (!safe_read(Player + oPlayerModel, DWORD64)) continue;// 0x4A8 public PlayerModel playerModel;
			if (!Player->IsValid()) continue;
			bool ex = false;
			RadarPlayer(Player);
			
			ESP(Player, LocalPlayer.BasePlayer);

			if (Vars::Radar::ActiveSlot && GetFov(Player, head) <= 150)
				RenderActiveSlot(Player, Vars::Radar::ActiveSlotPos_X, Vars::Radar::ActiveSlotPos_Y);

			if (Vars::AimBot::IgnoreTeam && Player->IsTeamMate(LocalPlayer.BasePlayer->GetSteamID())) continue;
			{
				if (CurFOV <= Vars::AimBot::Fov)
				{
					FOV = CurFOV; AimEntity = Player;
				}
				if (CurFOV <= Vars::AimBot::SilentFov)
				{
					TargetSilentPlayer = (uintptr_t)Player;
					//PsilentPlayer = (uintptr_t)Player;
				}
				if (CurFOV <= Vars::AimBot::PSilentFov)
				{
					TargetPSilentPlayer = (uintptr_t)Player;
					/*IsTarget(Player);*/
				}
			}

			if (Vars::Visuals::IgnoreSleepers && Player->HasFlags(16)) continue;


			if (Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), Player->GetBoneByID(head)) > Vars::AimBot::Range)
				continue;

			//calc visible & low fov
			if (Player->IsVisible() && (FOV > (CurFOV = GetFov(Player, BoneList(Vars::Global::BoneToAim)))))
			{				
				if (CurFOV <= Vars::AimBot::Fov)
				{
					FOV = CurFOV; AimEntity = Player;
				}
				if (CurFOV <= Vars::AimBot::SilentFov)
				{
					TargetSilentPlayer = (uintptr_t)Player;
					//PsilentPlayer = (uintptr_t)Player;
				}
				if (CurFOV <= Vars::AimBot::PSilentFov)
				{
					TargetPSilentPlayer = (uintptr_t)Player;
					/*IsTarget(Player);*/
				}
			}
		}

		else if (Vars::AimBot::MeleeAutoFarm && (m_strstr((char*)safe_read(safe_read(ent, DWORD64) + 0x10, DWORD64), ("TreeEntity")) || m_strstr((char*)safe_read(safe_read(ent, DWORD64) + 0x10, DWORD64),("OreHotSpot")))) {
			char* name = (char*)safe_read(safe_read(ent, DWORD64) + 0x10, DWORD64);
			UINT64 gameObject = safe_read(ObjectClass + 0x30, UINT64);
			UINT64 Trans = safe_read(gameObject + 0x8, UINT64);
			UINT64 Vec = safe_read(Trans + 0x38, UINT64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3); //TODO Hit tree marker
			typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);

			Vector3 local = ((CPoint)((DWORD64)GetModuleHandleA("GameAssembly.dll") + oClosestPoint))(LocalPlayer.BasePlayer, pos); //public Vector3 ClosestPoint(Vector3 position) { }
			if (Math::Calc3D_Dist(local, pos) >= 3.f) {
				continue;
			}

			AimResult target = AimResult();
			target.valid = true;
			target.pos = pos;
			target.entity = (BasePlayer*)ent;

		}

		if (LP_isValid)
		{
			WeaponPatch();
			Aim(AimEntity);
			//AutoAimAndFire(AimEntity);
			Misc();
			FakeLag();;

		}

	

		auto* weapon_ = LocalPlayer.BasePlayer->GetActiveWeapon();
		char* classname = weapon_->ClassName();
		bool weaponmelee = weapon_ && classname && (m_strcmp(classname, "BaseMelee") || m_strcmp(classname, "Jackhammer"));
		DWORD64 active = safe_read(weapon_ + oHeldEntity, DWORD64);

		if (Vars::Misc::Door && m_strstr((char*)safe_read(safe_read(ent, DWORD64) + 0x10, DWORD64), "Door"))
		{
			UINT64 gameObject = safe_read(ObjectClass + 0x30, UINT64);
			UINT64 Trans = safe_read(gameObject + 0x8, UINT64);
			UINT64 Vec = safe_read(Trans + 0x38, UINT64);//public EZSoftBone.Bone childBone;
			Vector3 pos = safe_read(Vec + 0x90, Vector3);//public Vector3 systemPosition;
			typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);
			Vector3 local = ((CPoint)(GetModBase(L"GameAssembly.dll") + oClosestPoint))(LocalPlayer.BasePlayer, pos);
			if (ent && Math::Calc3D_Dist(local, pos) < 3.f)
			{
				EbynMozga(ent);
			}
		}

		else if (Vars::Visuals::Shkaf && strstr(buff, ("cupboard.tool.deployed.prefab"))) {
			wchar_t res[64];
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				_swprintf(res, L"[Шкаф] %d m", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetPosition(), pos));
				GUI::Render.String(Pos, res, FLOAT4TOD3DCOLOR(Vars::Color::Shkaf));
				GUI::Render.String(Pos, res, FLOAT4TOD3DCOLOR(Vars::Color::ShkafDIST));
			}
		}

		if (Vars::Misc::AutoPickUp && m_strstr(buff, "/collectable/"))
		{
			UINT64 gameObject = safe_read(ObjectClass + 0x30, UINT64);
			UINT64 Trans = safe_read(gameObject + 0x8, UINT64);
			UINT64 Vec = safe_read(Trans + 0x38, UINT64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			typedef Vector3(__stdcall* CPoint)(BasePlayer*, Vector3);
			Vector3 local = ((CPoint)(GetModBase(L"GameAssembly.dll") + oClosestPoint))(LocalPlayer.BasePlayer, pos);
			if (Math::Calc3D_Dist(local, pos) < 5.f)
			{
				PickupItem(ent);
			}
		}

		if (Vars::Visuals::Stone && strstr(buff, "stone-ore.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			/*Vector2 ScreenPos, BoxPos;*/
			Vector2 Pos;

			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				/*float num2 = abs(ScreenPos.y - BoxPos.y);*/
				wchar_t text[0x100];

				_swprintf(text, L"[Камень] [%d m]", distation);

				//CornerBox(ScreenPos.x - num2 / 2, ScreenPos.y - num2 / 4, num2, num2 / 2, FLOAT4TOD3DCOLOR(Vars::ResourcesColor::StoneOreColor));//Vars::Visuals::Stone
				if (distation <= Vars::Visuals::StoneOreDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Black);
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::StoneEsp)); 
			}
		}

		else if (strstr(buff, "workbench1.deployed.prefab") && Vars::Visuals::workbench1) {
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				wchar_t res[15];
				_swprintf(res, L"𝚠𝚘𝚛𝚔𝚋𝚎𝚌𝚗𝚑 𝚕𝚟𝚕𝟷 [%d m]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos));
				GUI::Render.String(Pos, res, D2D1::ColorF::Snow);
			}
		}
		else if (strstr(buff, "workbench2.deployed.prefab") && Vars::Visuals::workbench2) {
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				wchar_t res[15];
				_swprintf(res, L"𝚠𝚘𝚛𝚔𝚋𝚎𝚌𝚗𝚑 𝚕𝚟𝚕𝟸 [%d m]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos));
				GUI::Render.String(Pos, res, D2D1::ColorF::Snow);
			}
		}
		else if (strstr(buff, "workbench3.deployed.prefab") && Vars::Visuals::workbench3) {
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				wchar_t res[15];
				_swprintf(res, L"𝚠𝚘𝚛𝚔𝚋𝚎𝚌𝚗𝚑 𝚕𝚟𝚕𝟹 [%d m]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos));
				GUI::Render.String(Pos, res, D2D1::ColorF::Snow);
			}
		}

		////crate box
		if (strstr(buff, "crate_normal.prefab") && Vars::Visuals::normalbox) {
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				wchar_t res[15];
				_swprintf(res, L"𝙼𝚒𝚕𝚒𝚝𝚊𝚛𝚢 𝚋𝚘𝚡 [%d m]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos));
				GUI::Render.String(Pos, res, FLOAT4TOD3DCOLOR(Vars::Color::normalbox));
			}
		}

		if (strstr(buff, "crate_mine.prefab") && Vars::Visuals::mine) {
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				wchar_t res[15];
				_swprintf(res, L"𝚖𝚒𝚗𝚎 box [%d m]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos));
				GUI::Render.String(Pos, res, FLOAT4TOD3DCOLOR(Vars::Color::mine));
			}
		}

		if (strstr(buff, "crate_elite.prefab") && Vars::Visuals::elite) {
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				wchar_t res[15];
				_swprintf(res, L"Elite [%d m]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos));
				GUI::Render.String(Pos, res, FLOAT4TOD3DCOLOR(Vars::Color::elite));
			}
		}

		if (strstr(buff, "crate_normal_2_food.prefab") && Vars::Visuals::food) {
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				wchar_t res[15];
				_swprintf(res, L"𝚏𝚘𝚘𝚍 [%d m]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos));
				GUI::Render.String(Pos, res, FLOAT4TOD3DCOLOR(Vars::Color::food));
			}
		}

		if (strstr(buff, "crate_tools.prefab") && Vars::Visuals::toolbox) {
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				wchar_t res[15];
				_swprintf(res, L"𝚝𝚘𝚘𝚕𝚋𝚘𝚡 [%d m]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos));
				GUI::Render.String(Pos, res, FLOAT4TOD3DCOLOR(Vars::Color::toolbox));
			}
		}

		if (strstr(buff, "crate_normal_2_medical.prefab") && Vars::Visuals::medicalbox) {
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				wchar_t res[15];
				_swprintf(res, L"𝚖𝚎𝚍𝚒𝚌𝚊𝚕 𝚋𝚘𝚡 [%d m]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos));
				GUI::Render.String(Pos, res, FLOAT4TOD3DCOLOR(Vars::Color::medicalbox));
			}
		}

		if (strstr(buff, "crate_normal_2.prefab") && Vars::Visuals::normalbox2) {
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				wchar_t res[15];
				_swprintf(res, L"𝙻𝚘𝚘𝚝 𝚋𝚘𝚡 [%d m]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos));
				GUI::Render.String(Pos, res, FLOAT4TOD3DCOLOR(Vars::Color::normalbox2));
			}
		}

		if (Vars::Visuals::Sulphur && strstr(buff, "sulfur-ore.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"[Сера] [%d m]", distation);
				if (distation <= Vars::Visuals::SulphurOreDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Black);
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::SulfurEsp));
			}
		}

		if (Vars::Visuals::BerryBlue && strstr(buff, "berry-blue-collectable.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];
				wchar_t BerryDistation[0x100];
				_swprintf(text, L"[Сера]");
				_swprintf(BerryDistation, L"[%d m]", distation);
				if (distation <= Vars::Visuals::BerryBlueDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Black);
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::BerryBlueEsp));
			}
		}

		if (Vars::Visuals::Metal && strstr(buff, "metal-ore.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"[Метал] [%d m]", distation);
				if (distation <= Vars::Visuals::MetalOreDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Black);
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::MetalEsp));
			}
		}
		if (Vars::Visuals::Stash && strstr(buff, "small_stash_deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"[Стэш] [%d m]", distation);
				if (distation <= Vars::Visuals::StashDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Black);
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::StashEsp));
			}
		}
		if (Vars::Visuals::c4_explosion && strstr(buff, "c4_explosion.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"[c4] [%d m]", distation);
				if (distation <= Vars::Visuals::c4_explosionDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Black);
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::StashEsp));
			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////Minicopter, scrapheli - работает хорошо
		if (Vars::Visuals::Minicopter && strstr(buff, "minicopter.entity.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"minicopter [%d m]", distation);
				if (distation <= Vars::Visuals::MinicopterDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Black);
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::MinicopterEsp));
			}
		}

		if (Vars::Visuals::Patrul && strstr(buff, "patrolhelicopter.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			Vector2 tempHead;
			Vector2 tempFeetR, tempFeetL;
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				int health = (int)safe_read(BaseHelicopter + oHealth, float);
				wchar_t text[0x100];
				float maxheal = 100.f;
				float Entity_h = tempHead.y - tempFeet.y;
				float w = Entity_h / 4;
				float Entity_x = tempFeet.x - w;
				float Entity_y = tempFeet.y;
				float Entity_w = Entity_h /

					_swprintf(text, L"PatrulHeli [%d M][%d HP]", distation, health);
				if (distation <= Vars::Visuals::PatrulDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::PatrulEsp));
				if (Vars::Visuals::ShowPlayerHealthBar1)
				{
					if ((int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), LocalPlayer.BasePlayer->GetBoneByID(head)) < 201)
					{
						//Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF(0.f, 0.f, 0.f, 0.4f));
						//Render::Object.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / minheal) }, D2D1::ColorF::Magenta);
						if ((int)safe_read(BaseHelicopter + oHealth, float) <= 33)
						{
							GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 0.f, 0.f, 0.8f));
						}
						if ((int)safe_read(BaseHelicopter + oHealth, float) >= 34 && (int)safe_read(BaseHelicopter + oHealth, float) <= 66)
						{
							GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(255.f, 202.f, 0.f, 0.8f));
						}
						if ((int)safe_read(BaseHelicopter + oHealth, float) >= 67)
						{
							GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h * (health / maxheal) }, D2D1::ColorF(0.f, 255.f, 0.f, 0.8f));
						}
						GUI::Render.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
					}
				}
			}
		}

		if (Vars::Visuals::Bradley && strstr(buff, "bradleyapc.prefab")) {

			BasePlayer* Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64);
			if (!safe_read(Player + oHealth, DWORD64)) continue;
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;

			int health = (int)safe_read(BaseHelicopter + oHealth, float);
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"[%dHP] Helicopter [%dm]", health, (int)(LocalPlayer.BasePlayer->GetPosition(), distation));
				//_swprintf(text, L"Patrul [%d m] [%dHP]", GetPosition, distation);
				if (distation <= Vars::Visuals::BradleyDistation)
					GUI::Render.String(Pos, text, D2D1::ColorF::Black);
				GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::BradleyEsp));
			}
		}
		

		//else if (Vars::Visuals::ScrapHeli && strstr(buff, "scraptransporthelicopter.prefab"))
		//{
		//	BasePlayer* Player = (BasePlayer*)safe_read(Object + 0x28, DWORD64);
		//	if (!safe_read(Player + oHealth, DWORD64)) continue;
		//	DWORD64 Res = safe_read(Object + 0x28, DWORD64);
		//	DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
		//	DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
		//	DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
		//	Vector3 pos = safe_read(Vec + 0x90, Vector3);
		//	Vector2 Pos;
		//	int ScrapHeli = (int)safe_read(BaseHelicopter + oHealth, float);
		//	if (LocalPlayer.WorldToScreen(pos, Pos))
		//	{
		//		int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
		//		wchar_t text[0x100];

		//		_swprintf(text, L"[%dHP] ScrapHeli [%d m]", ScrapHeli, (int)(LocalPlayer.BasePlayer->GetPosition(), distation));
		//		if (distation <= Vars::Visuals::ScrapHeliDistation)
		//			GUI::Render.String(Pos, text, D2D1::ColorF::Yellow/*FLOAT4TOD3DCOLOR(Vars::Color::TrapsEsp)*/);
		//	}
		//
		//}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////////////////TRAPS - работает хорошо

		if (Vars::Visuals::Traps && strstr(buff, "guntrap.deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"ShGun Trap [%d m]", distation);
				if (distation <= Vars::Visuals::TrapsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::TrapsEsp));
			}
		}
		if (Vars::Visuals::Traps && strstr(buff, "flameturret.deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Flameturret [%d m]", distation);
				if (distation <= Vars::Visuals::TrapsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::TrapsEsp));
			}
		}
		if (Vars::Visuals::Traps && strstr(buff, "autoturret_deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Autoturret [%d m]", distation);
				if (distation <= Vars::Visuals::TrapsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::TrapsEsp));
			}
		}
		if (Vars::Visuals::Traps && strstr(buff, "sam_site_turret_deployed.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Land-Air Turret [%d m]", distation);
				if (distation <= Vars::Visuals::TrapsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::TrapsEsp));
			}
		}

		if (Vars::Visuals::Hemp && strstr(buff, "hemp-collectable.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Hemp [%d m]", distation);
				if (distation <= Vars::Visuals::HempDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::HempEsp));
			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////supply - работает хорошо

		if (strstr(buff, "supply_drop.prefab") && Vars::Visuals::Supply)
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Airdrop [%d m]", distation);
				if (distation <= Vars::Visuals::SupplyDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::SupplyEsp));
			}
		}
		if (strstr(buff, "codelockedhackablecrate.prefab") && Vars::Visuals::Supply)
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Ch47_drop [%d m]", distation);
				if (distation <= Vars::Visuals::SupplyDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::SupplyEsp));
			}
		}

		//if (Vars::Visuals::Corpse && strstr(buff, "player_corpse.prefab")) {
		//	DWORD64 Res = safe_read(Object + 0x28, DWORD64);
		//	DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
		//	DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
		//	DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
		//	Vector3 pos = safe_read(Vec + 0x90, Vector3);

		//	Vector2 Pos;
		//	if (LocalPlayer.WorldToScreen(pos, Pos)) {
		//		int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
		//		wchar_t CorpseName[0x100];
		//		wchar_t text[0x100];

		//		DWORD64 DeadCorpseName = safe_read(Res + oCorpsePlayerName, DWORD64);
		//		//DWORD64 DeadCorpseName = safe_read (Corpse + oCorpsePlayerName DWORD64);
		//		_swprintf(CorpseName, L"Dead : %s", DeadCorpseName);
		//		std::cout << CorpseName << "\n";
		//		_swprintf(text, L"Corpse [%d m]", distation);
		//		std::cout << text << "\n";
		//		std::cout << "x: " << Pos.x << " y: " << Pos.y << "\n";
		//		GUI::Render.String(Pos, text, D2D1::ColorF::Yellow);
		//		
		//		if (distation <= Vars::Visuals::CorpseDistation)
		//			GUI::Render.String(Pos, text, D2D1::ColorF::Yellow);
		//		Pos.x += 5; Pos.y += 5;
		//		GUI::Render.String(Pos, CorpseName, D2D1::ColorF::Yellow);
		//			//GUI::Render.String(Pos, text, D2D1::ColorF::Yellow);
		//	}
		if (Vars::Visuals::Corpse && strstr(buff, "player_corpse.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];


				_swprintf(text, L"Corpse [%d m]", distation);
				if (distation <= Vars::Visuals::CorpseDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::CorpseEsp));
			}
		}
		if (Vars::Visuals::Corpse && strstr(buff, "item_drop_backpack.prefab"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Backpack [%d m]", distation);
				if (distation <= Vars::Visuals::CorpseDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::CorpseEsp));
			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////

		if (Vars::Visuals::show_Weapons && strstr(buff, "lmg.m249"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"M249 LMG [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.bolt"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"BOLT Sniper [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		else if (strstr(buff, "mushroom-cluster-5.prefab") && Vars::Visuals::Mushrooms) {
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos)) {
				wchar_t res[90];
				_swprintf(res, L"Mushrooms [%d m]", (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(r_foot), pos));
				GUI::Render.String(Pos, res, FLOAT4TOD3DCOLOR(Vars::Color::Mushrooms));
			}

		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.ak"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"AK-47 Rifle [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.lr300"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"LR300 Rifle [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.l96"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"L96 Sniper [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.m39"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"M39 Rifle [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "rifle.semiauto"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Semi Auto Rifle [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "smg.mp5"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"MP5 SMG [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "smg.2"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"SMG Auto [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "smg.thompson"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Thompson SMG [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.nailgun"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Nailgun Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.eoka"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"EOKA Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.m92"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"M92 Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.python"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Python Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.revolver"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Revolver Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "pistol.semiauto"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Semi Auto Pistol [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "shotgun.pump"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Shotgun Pump [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "shotgun.double"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"Double Shotgun [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}

		if (Vars::Visuals::show_Weapons && strstr(buff, "shotgun.spas12"))
		{
			DWORD64 Res = safe_read(Object + 0x28, DWORD64);
			DWORD64 gameObject = safe_read(ObjectClass + 0x30, DWORD64); //Tag 449
			DWORD64 Trans = safe_read(gameObject + 0x8, DWORD64);
			DWORD64 Vec = safe_read(Trans + 0x38, DWORD64);
			Vector3 pos = safe_read(Vec + 0x90, Vector3);
			Vector2 Pos;
			if (LocalPlayer.WorldToScreen(pos, Pos))
			{
				int distation = (int)Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), pos);
				wchar_t text[0x100];

				_swprintf(text, L"SPAS-12 Shotgun [%d m]", distation);
				if (distation <= Vars::Visuals::show_WeaponsDistation)
					GUI::Render.String(Pos, text, FLOAT4TOD3DCOLOR(Vars::Color::show_WeaponsEsp));
			}
		}
	}
	static DWORD64 dwGameObjectManager = 0;
	if (!dwGameObjectManager)
		dwGameObjectManager = RVA(FindPattern((PBYTE)"\x48\x8B\x15\x00\x00\x00\x00\x66\x39", "xxx????xx", L"UnityPlayer.dll"), 7);

	DWORD64 ObjMgr = safe_read(dwGameObjectManager, DWORD64); if (!ObjMgr) return;

	for (DWORD64 Obj = safe_read(ObjMgr + 0x8, DWORD64); (Obj && (Obj != safe_read(ObjMgr, DWORD64))); Obj = safe_read(Obj + 0x8, DWORD64))
	{
		DWORD64 GameObject = safe_read(Obj + 0x10, DWORD64);
		WORD Tag = safe_read(GameObject + 0x54, WORD);

		if (Tag == 6,  Tag == 5  ,Tag == 20011)
		{
			DWORD64 ObjClass = safe_read(GameObject + 0x30, DWORD64);
			DWORD64    Entity = safe_read(ObjClass + 0x18, DWORD64);

			//entity
			if (Tag == 6)
			{
				BasePlayer* Player = (BasePlayer*)safe_read(Entity + 0x28, DWORD64);
				if (!Player->IsValid()) continue;
			}
			if (Vars::AimBot::IgnoreTeam) {
				DWORD64 EntitySID = Player->GetSteamID();
				for (int j = 0; j < LocalPlayer.BasePlayer->GetTeamSize(); j++) {
					DWORD64 SlotSID = LocalPlayer.BasePlayer->IsTeamMate(j);
					if (SlotSID == EntitySID) goto NextEnt;
				}
			}
			else if (Tag == 20011 && Vars::Misc::CustomTime) {
				DWORD64 Dome = safe_read(Entity + 0x28, DWORD64);
				DWORD64 TodCycle = safe_read(Dome + 0x38, DWORD64);
				safe_write(TodCycle + 0x10, Vars::Misc::Time, float);
			}
			//cut distance
			if (Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(neck), Player->GetBoneByID(neck)) > Vars::AimBot::Range)
				goto NextEnt;

		}

		//goto next entity
	NextEnt: continue;
	}
	if (LP_isValid)
	{
		WeaponPatch();
		Aim(AimEntity);
		//	AutoAimAndFire(AimEntity);
		Misc();
	}
	else LocalPlayer.BasePlayer = nullptr;	
}

