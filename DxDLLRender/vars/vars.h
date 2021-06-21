
uintptr_t closestHeli;
namespace Vars
{
	__declspec(selectany) uintptr_t PlayerxD = NULL;
	namespace Tabs
	{
		bool Aim, Silent, ESP, BOTESP, OtherESP, Player, Weapon, Color, Config = false;
		bool Preview = false;
	}
	namespace Global
	{
		
		Vector2 MenuPos = { 0, 0 };
		bool Panic = false;
		float ScreenHigh = 0;
		float ScreenWidth = 0;
		float ScreenHigh1 = 0;
		float ScreenWidth1 = 0;
		HWND hWindow = nullptr;
		bool MenuVisible = false;
		WNDPROC oWindproc = nullptr;

		Vector3 LastPos = { 0.f, 0.f, 0.f };
		ULONGLONG LastTime = 0;
		DWORD64 LastSteamID = 0;
		const wchar_t* LastName;
		Vector3 PlayerVeloc = { 0.f, 0.f, 0.f };

		int BoneToAim = 1;
		float BulletSpeed = 250.f;
		DWORD64 PresentDelta = 0;
		float CorX = 0.f;
		float CorY = 0.f;
		char ConfigName[0x100] = "Config";
	}
	namespace BotsEsp
	{
		bool BotsBoxes = false;
		bool d = false;
		bool botsESP = false;
		bool Bots = false;
		float MaxBotDistance = 400.f;
		bool SkeletonBots = false;
		bool ShowBotsHealth = false;
		bool BotsESP = false;
		bool BotsName = false;
		bool ShowBotsDist = false;
		bool ShowBotsWeapon = false;
		bool IgnoreNpc = false;
	}
	namespace Test
	{



	}

	namespace Storage
	{
		__declspec(selectany) uintptr_t gBase = (DWORD64)GetModuleHandleA("GameAssembly.dll");	
		__declspec(selectany) uintptr_t uBase = (DWORD64)GetModuleHandleA("UnityPlayer.dll");
		__declspec(selectany) uintptr_t closestPlayer = NULL;
		__declspec(selectany) uintptr_t PlayerxD = NULL;
	}
	namespace AimBot
	{
		bool pSilent = false;
		bool DrawPSilentFov = false;

		bool mouse_move = false;
		bool pSilenthelli = false;
		bool SilentHeli = false;
		int sget = 0;
		float LongNeckvolue = 0.f;
		bool FastReload = false;
		bool FastBullet = false;
		bool FatBullet = false;
		float SpeedBullets = 3.f;
		bool RapidFire = false;
		bool TargetPSilent = false;
		bool IgnoreTeam = false;
		bool MeleeAimPlayers = false;

		float PSilentFov = 100.f;
		float LimitDist = 300.f;
		bool PSilentClear = false;
		int Psilentclearkey = 0;
		
		//bool FatBullet = false;//Set_Psilent
		bool Fake_Dist = false;
		bool HellBullet = false;
		bool PSilentTarget = false;
		float distancefake = 500.f;
		bool Activate = false;
		bool MeleeAutoFarm = false;
		
		bool BodyAim = false;
		bool pSilentHead = false;
		bool AlwaysBody = false;
		bool pBody = false;
		bool randhitbox = false;
		bool RCS = false;
		bool Standalone = false;
		bool VisibleCheck = false;
		bool DrawFov = false;
		float Velocity = 1.480f;
		
		float Range = 400.f;
		float Fov = 100.f;

		int aimkey = 0;
		static int keystatus = 0;
		bool toggleaim = false;
		bool SilentBody = false;
		bool EnableSilentAim = false;
		bool AlwaysHeadshot = false;
		bool ThroughWall = false;
		bool DrawSilentFov = false;
		bool SilentTarget = false;
		float SilentDist = 500.f;
		float SilentFov = 100.f;
		bool SilentIgnoreBot = false;
		float RCSs = 0.f;
		bool SilentIgnoreSleep = false;
		bool SilentIgnoreWounded = false;
		bool SilentClear = false;
		int silentclearkey = 0;

		int firekey = 0;
		bool Trigger = false;
		bool DrawTriggerFov = true;
		float TriggerFov = 10;
		bool toggleauto = false;
		int autokey = 0;

	}

	struct
	{
		int m_mode = 0;									// 0 - 2				| 0 - Off, 1 - Constant, 2 - Linear
		float m_pitch = 0.f;						// 0.f - 100.f	| Vertical aim step or smooth amount
		float m_yaw = 0.f;							// 0.f - 100.f	| Horizontal aim step or smooth amount
	} m_step = { };

	namespace GG {

		bool rainbow = false;
		float  time = 0.f;
	}
	namespace Watermark
	{
		bool waterm = true;
		bool watermL = false;

		float PosX = 37.f;
		float PosY = 14.f;
	}
	namespace Visuals
	{
		bool Mushrooms = false;
		bool FillBox = false;
		bool boxxuina = false;
		bool PlayerBoxK = false;
		bool PlayerBox = false;
		bool elite = false;
		bool normalbox = false;
		bool PlayerChams = false;
		bool food = false;
		bool medicalbox = false;
		bool toolbox = false;
		bool morebox = false;
		bool normalbox2 = false;
		bool supply_drop = false;
		bool turrel = false;
		bool mine = false;
		bool ShowPlayerBox = false;
		bool healthbarpreviw = true;
		bool ShowPlayerHealthBar1 = false;
		bool ShowPlayerName = false;
		bool ShowPlayerHealth = false;
		bool InfoTopLeft = false;
		bool SnapLines = false;
		bool ShowPlayerWeapon = false;
		bool Colapse1 = false;
		bool ShowPlayerModelColor = false;
		bool SEXCrosshair = false;
		bool Chams = false;
		bool Shkaf = false;
		float ActiveSlotPos_X = 0.f;
		bool infohp = false;
		float ActiveSlotPos_Y = 0.f;
		bool ShowPlayerActiveSlot = false;
		bool healthbar = false;
		bool FillFov = false;
		bool SEXXCrosshair = false;
		bool RainbowESP = false;
		bool ShowPlayerDefault = false;
		bool tracers = false;
		bool SEXXXCrosshair = false;
		bool MaterialChams = false;
		bool Collapse = false;
		bool SnapLines2 = false;
		bool SnapLines1 = false;
		bool Crosshair11 = false;
		bool ShowPlayerDist = false;
		//bool CSnapLines = false;
		bool AlwaysDay = false;
		bool Orig_CHAMSESP = false;
		bool NightMode = false;
		bool DropedItem = false;
		bool IgnoreSleepers = false;
		bool SkeletonPlayer = false;
		bool SkeletonBots = false;
		bool Crosshair = false;
		bool CircleCrosshair = false;
		bool Box = true;
		bool Name = true;
		bool Weapon = true;
		bool Dist = true;

		bool TargetLine = false;
		bool PlayerESP = false;
		bool BotsESP = false;
	}

	namespace DropedItem
	{
		bool showDistance = false;
		float DrawDistance = 300.f;
	}

	namespace CFG
	{
		bool LEGITCFGBYFe1zep = false;
		bool RAGECFGBYFe1zep = false;
		bool SBROSCFGBYFe1zep = false;
		bool n1ntendo = false;
		bool n1ntendolegit = false;
	}

	namespace Misc
	{
		bool AdminTools = false;
		bool MeleeAimPlayers = false;
		bool LongNeck = false;
		bool noclip = false;
		bool issleepers = false;
		bool DebugBypass = false;
		bool TakeFallDamage = false;
		bool attack_on_mountables = false;
		bool fastmelee = false;
		bool ThirdPersone = false;
		bool MeleeAutoFarm = false;
		bool rainbow = false;
		bool Onladder = false;
		bool WaterMark = true;
		bool canrotatecam = false;
		float  time = 0.f;
		bool SulfurEsp = false;
		bool AutoFarmOre = false;
		bool Zoom = false;
		int Zoomkey = 0;
		bool Crosshairs = false;
		bool checkbox = false;
		bool Antiafk = false;
		bool Crosshairs1 = false;
		int LongNeckkey = 0;
		int TimeScalekey = 0;
		float Zoomvalue = 20.f;
		
		bool MeleeAttack = false;
		bool canHoldItems = false;
		bool AutoFarmTree = false;
		float GraphicsZoom = 40.f;
		
		
		
		bool compound = false;
		bool AutoFarm = false;
		bool MetalEsp = false;
		bool StoneEsp = false;
		bool SwimOnGround = false;
		bool fastcompbow = false;
		bool menushka = false;
		bool MenuSteep2 = false;
		bool MenuSteep = false;
		bool instarevive = false;
		bool swiming = false;
		bool Resolver = false;
		float SetSwim = 0.f;
		bool NewSwimOnGround = false;
		bool Door = false;
		bool rollbulding = false;
		bool HitSound = false;
		bool HitSound1 = false;
		bool HitSound2 = false;
		bool HitSound3 = false;
		bool HitSound4 = false;
		bool WorkBench = false;
		bool AutoPickUp = false;
		bool CustomHitsound = false;
		bool FastHeal = false;
		bool waslagging = false;
		bool no_playercollision = false;
		bool FakeLag = false;
		bool AntiAim = false;
		bool SlideWalk = false;
		bool SilentWalk = false;
		bool Flyhack = false;
		bool Crosshair1 = false;
		bool ShotGunTochka = false;		
		bool CustomTime = false;
		float Time = 1.0f;
		bool CustomFov = false; //Camera
		float GraphicsFov = 90.f;
		float pred = 0.f;
		bool SpiderMan = false;
		bool FlyHack = false;
		bool InfinityJump = false;
		bool AntiSpread = false;
		bool NoRecoil = false;
		bool FastReload = false;
		bool Automatic = false;
		bool SuperEoka = false;
		bool SkinChanger = false;
		bool BuildAsUWant = false;
		int buildkey = 0;
		bool NoSway = false;
		bool SuperBow = false;
		bool FakeAdmin = false; //need
		bool NoGreenZone = false;
		bool LongHand = false;
		bool RunOnHit = false;
		bool HighJump = false;
		bool SpeedHack = false;
		bool JumpAiming = false;
		int highkey = 0;
		////////////////////////////
		bool TargetLine = false;
		bool WalkOnWater = false;
		int walkkey = 0;
		///////////////////////////
		float JumpValue = 1.0f;
		bool WaterBoost = false;
		bool NoFall = false;
		bool AirStuck = false;
		bool AntiKastrulya = false;
		bool NoHeavyReduct = false;
		//meme dot
		bool Crosshair = false;


	}

	namespace HvH
	{
		float Tick = 2.3f;
		float Tick2 = 2.3f;
		float FOV = 0.5f;
	}

	namespace Visuals
	{

		bool FakeWorkBench = false;
		bool ore = false;
		bool EnableBoxResourses = false;
		bool Sulphur = false;
		float SulphurOreDistation = 100.f;
		bool Metal = false;
		float MetalOreDistation = 100.f;
		bool Stone = false;
		float StoneOreDistation = 100.f;
		bool BerryBlue = false;
		float BerryBlueDistation = 100.f;
		float FakeWorkBenchDist = 100.f;
		float MushroomsDistation = 100.f;
		bool shkaf = false;
		float ShkafDIST = 100.f;
		bool c4_explosion = false;
		float c4_explosionDistation = 100.f;
		bool Stash = false;
		float StashDistation = 100.f;
		bool Minicopter = false;
		float MinicopterDistation = 100.f;
		bool Patrul = false;
		float PatrulDistation = 100.f;
		float Patrulhealth = 0.f;
		bool Bradley = false;
		float BradleyDistation = 100.f;
		float Bradleyhealth = 0.f;
		bool Traps = false;
		float TrapsDistation = 100.f;
		bool Hemp = false;
		float HempDistation = 100.f;
		bool Supply = false;
		float SupplyDistation = 100.f;
		bool Corpse = false;
		float CorpseDistation = 100.f;
		bool Crate = false;
		float CrateDistation = 100.f;
		bool workbench1 = false;
		float workbench1Distation = 100.f;

		bool workbench2 = false;
		float workbench2Distation = 100.f;

		bool workbench3 = false;
		float workbench3Distation = 100.f;
		//
		bool show_Weapons = false;
		float show_WeaponsDistation = 100.f;

	}

	namespace WorckbeanchEsp
	{
		bool Activate = false;
		bool workbench1 = false;
		bool workbench2 = false;
		bool workbench3 = false;
	}

	namespace Drop
	{
		bool Activate = false;
		bool supply_drop = false;
		bool WoodBox_bacpack = false;
		bool closestPlayer = false;
		bool inventoryESP = false;
	}

	namespace PicUpEsp
	{
		bool Activate = false;
		bool StonePicUp = false;
		bool MetalPicUp = false;
		bool SulfurPicUp = false;
		bool WoodPicUp = false;
		bool hempEsp = false;
	}

	namespace Color {
		float CSnapColor[] = { 255.f,255.f,255.f,255.f };

		float HandChams[] = { 0, 255, 0 };
		float Fov[] = { 255.f, 255.f, 255.f };
		//float SilentFovColor[] = { 0.f, 0.f, 0.f };
		float TriggerFovColor[] = { 0.f, 0.f, 0.f };

		float normalbox[] = { 0, 255, 0 };
		float mine[] = { 0, 255, 0 };
		float elite[] = { 0, 255, 0 };
		float plaeyrChams[] = { 0, 255, 0 };
		float food[] = { 0, 255, 0 };
		float toolbox[] = { 0, 255, 0 };
		float medicalbox[] = { 0, 255, 0 };
		float normalbox2[] = { 0, 255, 0 };

		/// <summary>
		float BerryBlueEsp[] = { 0.f, 6.f, 255.f };
		float StoneEsp[] = { 255.f, 0.f, 0.f };
		float SulfurEsp[] = { 255.f, 0.f, 0.f };
		float SilentColor1[] = { 255.f, 0.f, 0.f };
		float MetalEsp[] = { 255.f, 0.f, 0.f };
		float Workbench[] = { 255.f, 0.f, 0.f };
		float Name[] = { 255.f, 0.f, 0.f };
		float ambientLightcolor[] = { 255.f, 0.f, 0.f };
		float unactiv[] = { 255.f, 0.f, 0.f }; 
		float weaponactivslot[] = { 255.f, 0.f, 0.f };
		float Line[] = { 255.f, 0.f, 0.f };
		float StashEsp[] = { 255.f, 0.f, 0.f };
		float Shkaf[] = { 255.f, 0.f, 0.f };
		float ShkafDIST[] = { 255.f, 0.f, 0.f };
		float MinicopterEsp[] = { 255.f, 0.f, 0.f };
		float PatrulEsp[] = { 255.f, 0.f, 0.f };
		float FillBox[] = { 255.f, 0.f, 0.f };
		float BradleyEsp[] = { 255.f, 0.f, 0.f };
		float TrapsEsp[] = { 255.f, 0.f, 0.f };
		float CollapseColor[] = { 255.f, 0.f, 0.f };
		float HempEsp[] = { 255.f, 0.f, 0.f };
		float FillFovColors[] = { 0.f, 0.f, 0.f, 0.f };
		float SupplyEsp[] = { 255.f, 0.f, 0.f };
		float CorpseEsp[] = { 255.f, 0.f, 0.f };
		float CrateEsp[] = { 255.f, 0.f, 0.f };
		float BoxColors[] = { 255.f, 255.f, 255.f };
		float show_WeaponsEsp[] = { 255.f, 0.f, 0.f };
		/// </summary>
		float SkeletonColor[] = { 255.f, 0.f, 0.f };
		float LineEsp[] = { 255.f, 0.f, 0.f };
		float BoxColor[] = { 255.f, 0.f, 0.f };
		float window[] = { 255.f, 0.f, 0.f };
		float Mushrooms[] = { 255.f, 0.f, 0.f };
		float NameColor[] = { 255.f, 0.f, 0.f };
		float PlayerHeath[] = { 255.f, 0.f, 0.f };
		float DistanceColor[] = { 255.f, 0.f, 0.f };
		float WeaponColor[] = { 255.f, 0.f, 0.f };
		float SnapColors[] = { 255.f, 0.f, 0.f };
		float CircleCrosshair[] = { 255.f,255.f,255.f,255.f };
		float CrosshairColor[] = { 0.f, 255.f, 0.f };
		float CrosshairColors[] = { 255.f, 255.f, 255.f };
		float ChamsESP[] = { 255.f, 255.f, 255.f };
		float Crosshair1[] = { 255.f, 255.f, 255.f };
		float SEXCrosshair[] = { 255.f,255.f,255.f,255.f };
		float SEXXCrosshair[] = { 255.f,255.f,255.f,255.f };
		float SEXXXCrosshair[] = { 255.f,255.f,255.f,255.f };
		float Crosshair11[] = { 255.f, 255.f, 255.f };

		float helfbarcolorpreviw[] = { 0, 255, 0 };


		float BotColor[] = { 255, 0, 255 };
		float SilentColor[] = { 255, 255, 0 };
		float ColorPreview[] = { 25, 30, 35 };
		float Steep[] = { 255, 0, 255 };
	}

	namespace Radar
	{
		float ActiveSlotPos_X = 63.f;
		float ActiveSlotPos_Y = 315.f;
		bool ActiveSlot = false;
		bool Enable = false;
		bool infobarleft = false;
		bool ShowRadarBackground = false;
		bool ShowRadarPlayer = false;
		bool ShowRadarSleeper = false;
		bool ShowRadarStoneOre = false;
		bool ShowRadarMettalOre = false;
		bool ShowRadarSulfureOre = false;
		float Pos_X = 0;
		float Pos_Y = 0;
		float Radar_Size = 250.f;
		float Radar_Range = 300.f;
		bool EnableDinamicRadar = false;
	}

	namespace RadarColor
	{
		static float RadarBackground[] = { 0,0,0,1, 0.5f };
		static float RadarPlayerColor[] = { 1,0,0,1 };
		static float RadarPlayerSleeperColor[] = { 0,0,1,1 };
		static float RadarStoneOreColor[] = { 0.487,0.487,0.487,1 };
		static float RadarMettalOreColor[] = { 0.162,0.178,0.440,1 };
		static float RadarSulfureOreColor[] = { 0.392,0.353,0.84,1 };
	}

	namespace Config {
		static char configname[128] = "My";
		bool LoadConfig = false;
		bool SaveConfig = false;
		bool InitConfig = false;
	}
}
