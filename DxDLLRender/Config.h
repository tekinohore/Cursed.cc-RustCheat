#pragma once
#include <direct.h>

CSimpleIniA cfg; //инициализируем объект

#pragma region Config Color

void SaveColorValue(const char* pSection, std::string name, float a_Value[4])
{
    int R, G, B, A;
    R = a_Value[0] * 1000;
    G = a_Value[1] * 1000;
    B = a_Value[2] * 1000;
    A = a_Value[3] * 1000;
    cfg.SetLongValue(pSection, (name + "_R").c_str(), R);
    cfg.SetLongValue(pSection, (name + "_G").c_str(), G);
    cfg.SetLongValue(pSection, (name + "_B").c_str(), B);
    cfg.SetLongValue(pSection, (name + "_A").c_str(), A);
}

void LoadColorValue(const char* pSection, std::string name, float a_Value[4])
{
    float R, G, B, A;
    R = cfg.GetLongValue(pSection, (name + "_R").c_str(), a_Value[0]);
    G = cfg.GetLongValue(pSection, (name + "_G").c_str(), a_Value[1]);
    B = cfg.GetLongValue(pSection, (name + "_B").c_str(), a_Value[2]);
    A = cfg.GetLongValue(pSection, (name + "_A").c_str(), a_Value[3]);
    a_Value[0] = R / 1000; a_Value[1] = G / 1000; a_Value[2] = B / 1000; a_Value[3] = A / 1000;
}

#pragma endregion 

inline bool folder_exists(const char* foldername)
{
    struct stat st;
    stat(foldername, &st);
    return st.st_mode & S_IFDIR;
}

void SaveCFG(const char* FileName)
{
    DWORD SerialNumber;

    GetVolumeInformation(L"C:\\", 0, 0, &SerialNumber, 0, 0, 0, 0);

    char Path[0x100];
    sprintf(Path, ("C:\\FrogGang.cc\\"));

    if (!folder_exists(Path))
        _mkdir(Path);
    cfg.SetUnicode();
    char result[0x100];
    sprintf(result, ("C:\\FrogGang.cc\\cfg\\%s.ini"), FileName);

#pragma region AimBot
    cfg.SetBoolValue("Aim", "Enable", Vars::AimBot::Activate);
    cfg.SetLongValue("Aim", "Aim Bot Key", Vars::AimBot::aimkey);
    cfg.SetLongValue("Aim", "Distance", Vars::AimBot::Range);
    cfg.SetLongValue("Aim", "Fov", Vars::AimBot::Fov);
    //cfg.GetLongValue("Aim", "FastReload", Vars::AimBot::FastReload);
    cfg.SetBoolValue("Aim", "Recoil Control System", Vars::AimBot::RCS);
    cfg.SetBoolValue("Aim", "RCS Standalone", Vars::AimBot::Standalone);
    cfg.SetBoolValue("Aim", "Show Fov", Vars::AimBot::DrawFov);
    cfg.SetBoolValue("Aim", "Visible Check", Vars::AimBot::VisibleCheck);
    cfg.SetBoolValue("Aim", "Body Aim", Vars::AimBot::BodyAim);
    cfg.SetBoolValue("Aim", "FatBullet", Vars::AimBot::FatBullet);
#pragma endregion

#pragma region SilentAim
    cfg.SetBoolValue("Silent", "SilentClear", Vars::AimBot::SilentClear);
    cfg.SetBoolValue("Silent", "SilentClear Key", Vars::AimBot::silentclearkey);
    cfg.SetBoolValue("Silent", "ThroughWall", Vars::AimBot::ThroughWall);
    cfg.SetBoolValue("Silent", "Enable Silent Aim", Vars::AimBot::EnableSilentAim);
    cfg.SetBoolValue("Silent", "Target Line", Vars::AimBot::SilentTarget);
    cfg.SetBoolValue("Silent", "Show Silent Fov", Vars::AimBot::DrawSilentFov);
    cfg.SetLongValue("Silent", "Fov", Vars::AimBot::SilentFov);
    /*cfg.SetBoolValue("Silent", "Is Ignore Sleeper", Bools::SilentAim::IsIgnoreSleeper);
    cfg.SetBoolValue("Silent", "Is Ignore Wounded", Bools::SilentAim::IsIgnoreWounded);
    cfg.SetBoolValue("Silent", "Is Ignore NPC", Bools::SilentAim::IsIgnoreNPC);
    cfg.SetLongValue("Silent", "Limit Dist", Bools::SilentAim::LimitDist);*/
#pragma endregion

#pragma region PlayerMisk
    cfg.SetLongValue("Misc", "Always Day", Vars::Visuals::AlwaysDay);
    cfg.SetBoolValue("Misc", "High Jump", Vars::Misc::HighJump);
    cfg.SetLongValue("Misc", "High Jump Value", Vars::Misc::JumpValue);
    cfg.SetBoolValue("Misc", "Jump Aiming", Vars::Misc::JumpAiming);
    cfg.SetBoolValue("Misc", "Fake Admin", Vars::Misc::FakeAdmin);
    cfg.SetBoolValue("Misc", "Swim",  Vars::Misc::swiming);
    cfg.SetBoolValue("Misc", "Speed Hack", Vars::Misc::SpeedHack);
    cfg.SetBoolValue("Misc", "Spider Man", Vars::Misc::SpiderMan);
   // cfg.SetBoolValue("Misc", "Custom Fov", Vars::Misc::CustomFov);
   
#pragma endregion

#pragma region WeaponMisk
    cfg.SetBoolValue("Weapn", "No Recoil", Vars::Misc::NoRecoil);
    cfg.SetBoolValue("Weapn", "CanHoldItems", Vars::Misc::canHoldItems);
    cfg.SetBoolValue("Weapn", "No Spread", Vars::Misc::AntiSpread);
    cfg.SetBoolValue("Weapn", "Automatic", Vars::Misc::Automatic);
    cfg.SetBoolValue("Weapn", "No Sway", Vars::Misc::NoSway);
    cfg.SetBoolValue("Weapn", "100% EOKA", Vars::Misc::SuperEoka);
    cfg.SetBoolValue("Weapn", "Shot Gun No Spread", Vars::Misc::ShotGunTochka);
#pragma endregion

#pragma region Player ESP
    cfg.SetLongValue("Player", "Enable", Vars::Visuals::PlayerESP);
    cfg.SetLongValue("Player", "Box", Vars::Visuals::ShowPlayerBox);
    cfg.SetLongValue("Player", "Health", Vars::Visuals::ShowPlayerHealth);
    cfg.SetLongValue("Player", "Distance", Vars::Visuals::ShowPlayerDist);
    cfg.SetLongValue("Player", "Weapon", Vars::Visuals::ShowPlayerWeapon);
    cfg.SetLongValue("Player", "Skeleton", Vars::Visuals::SkeletonPlayer);
    cfg.SetBoolValue("Player", "Target Player Info [top left]", Vars::Visuals::InfoTopLeft);
    cfg.SetLongValue("Player", "Corpse", Vars::Visuals::Corpse);
    cfg.SetLongValue("Player", "Ignore Sleepers", Vars::Visuals::IgnoreSleepers);
#pragma endregion

#pragma region Bots ESP
    cfg.SetLongValue("Bots", "Enable", Vars::Visuals::BotsESP);
    cfg.SetLongValue("Bots", "Skeleton", Vars::Visuals::SkeletonBots);
#pragma endregion

#pragma region Resources ESP
    cfg.SetBoolValue("Resources", "Sulphur", Vars::Visuals::Sulphur);
    cfg.SetBoolValue("Resources", "Metal", Vars::Visuals::Metal);
    cfg.SetBoolValue("Resources", "Stone", Vars::Visuals::Stone);
    cfg.SetLongValue("Resources", "Stash", Vars::Visuals::Stash);
    cfg.SetBoolValue("Resources", "MiniCopter", Vars::Visuals::Minicopter);
    cfg.SetLongValue("Resources", "Patrol Helicopter", Vars::Visuals::Patrul);
    cfg.SetBoolValue("Resources", "Traps", Vars::Visuals::Traps);
    cfg.SetLongValue("Resources", "Hemp", Vars::Visuals::Hemp);
    cfg.SetLongValue("Resources", "Supply", Vars::Visuals::Supply);
#pragma endregion

#pragma region Radar
    /*cfg.SetBoolValue("Radar", "Enable", Bools::Visual::Radar::Enable);
    cfg.SetBoolValue("Radar", "Show Radar Stone Ore", Bools::Visual::Radar::ShowRadarStoneOre);
    cfg.SetBoolValue("Radar", "Show Radar Mettal Ore", Bools::Visual::Radar::ShowRadarMettalOre);
    cfg.SetBoolValue("Radar", "Show Radar Sulfure Ore", Bools::Visual::Radar::ShowRadarSulfureOre);
    cfg.SetBoolValue("Radar", "Show Radar Background", Bools::Visual::Radar::ShowRadarBackground);
    cfg.SetBoolValue("Radar", "Show Radar Player", Bools::Visual::Radar::ShowRadarPlayer);
    cfg.SetBoolValue("Radar", "Show Radar Sleeper", Bools::Visual::Radar::ShowRadarSleeper);
    cfg.SetBoolValue("Radar", "Enable Dinamic Radar", Bools::Visual::Radar::EnableDinamicRadar);
    cfg.SetLongValue("Radar", "Pos X", Bools::Visual::Radar::Pos_X);
    cfg.SetLongValue("Radar", "Pos Y", Bools::Visual::Radar::Pos_Y);
    cfg.SetLongValue("Radar", "Radar Size", Bools::Visual::Radar::Radar_Size);
    cfg.SetLongValue("Radar", "Radar Range", Bools::Visual::Radar::Radar_Range);*/
#pragma endregion

#pragma region Construction ESP
    /*  cfg.SetBoolValue("Construction - ESP", "Enable", Bools::ConstructionESP::Enable);
      cfg.SetBoolValue("Construction - ESP", "Show Cupboard", Bools::ConstructionESP::ShowCupboard);
      cfg.SetLongValue("Construction - ESP", "Cupboard Distation", Bools::ConstructionESP::CupboardDistation);
      cfg.SetBoolValue("Construction - ESP", "Show Large Wood Box", Bools::ConstructionESP::ShowLargeWoodBox);
      cfg.SetLongValue("Construction - ESP", "Large Wood Box Distation", Bools::ConstructionESP::LargeWoodBoxDistation);
      cfg.SetLongValue("Construction - ESP", "Small Stash Distation", Bools::ConstructionESP::SmallStashDistance);
      cfg.SetBoolValue("Construction - ESP", "Show Small Stash", Bools::ConstructionESP::ShowSmallStash);*/
#pragma endregion 

#pragma region Aim Color
    SaveColorValue("Aim - Color", "Fov Color", Vars::Color::Fov);
    SaveColorValue("Aim - Color", "Target Line Color", Vars::Color::SilentColor);
#pragma endregion

#pragma region Radar Color
    /*SaveColorValue("Radar - Color", "Radar Background Color", Bools::RadarColor::RadarBackground);
    SaveColorValue("Radar - Color", "Radar Player Color", Bools::RadarColor::RadarPlayerColor);
    SaveColorValue("Radar - Color", "Radar Player Sleeper Color", Bools::RadarColor::RadarPlayerSleeperColor);
    SaveColorValue("Radar - Color", "Radar Stone Ore Color", Bools::RadarColor::RadarStoneOreColor);
    SaveColorValue("Radar - Color", "Radar Mettal Ore Color", Bools::RadarColor::RadarMettalOreColor);
    SaveColorValue("Radar - Color", "Radar Sulfure Sleeper Color", Bools::RadarColor::RadarSulfureOreColor);*/
#pragma endregion

#pragma region Bots Color
    /*SaveColorValue("Bots - Color", "Bots Render String Color", Bools::BotsColor::BotRenderStringColor);
    SaveColorValue("Bots - Color", "Bots Skeleton Color", Bools::BotsColor::BotSkeletonColor);
    SaveColorValue("Bots - Color", "Bots Box Color", Bools::BotsColor::BotBoxColor);
    SaveColorValue("Bots - Color", "Bots Fill Box Color", Bools::BotsColor::BotFillBoxColor);*/
#pragma endregion

#pragma region Player Color
    SaveColorValue("Player - Color", "Name", Vars::Color::NameColor);
    SaveColorValue("Player - Color", "Box", Vars::Color::BoxColor);
    SaveColorValue("Player - Color", "Health", Vars::Color::PlayerHeath);
    SaveColorValue("Player - Color", "Distance", Vars::Color::DistanceColor);
    SaveColorValue("Player - Color", "Weapon", Vars::Color::WeaponColor);
    /*SaveColorValue("Player - Color", "Player Fill Box Color", Bools::PlayerColor::PlayerFillBoxColor);
    SaveColorValue("Player - Color", "Player Dead Color", Bools::PlayerColor::PlayerDeadColor);
    SaveColorValue("Player - Color", "Player Backpack Color", Bools::PlayerColor::PlayerBackpackColor);*/
#pragma endregion

#pragma region Resourse Color
    /* SaveColorValue("Resourse - Color", "Stone - Ore Color", Bools::ResourcesColor::StoneOreColor);
     SaveColorValue("Resourse - Color", "Mettal - Ore Color", Bools::ResourcesColor::MettalOreColor);
     SaveColorValue("Resourse - Color", "Sulfure - Ore Color", Bools::ResourcesColor::SulfureOreColor);*/
#pragma endregion

#pragma region Construction Color
     /*
     SaveColorValue("Construction - Color", "Cupboard Color", Bools::ConstructionColor::CupboardColor);
     SaveColorValue("Construction - Color", "Large Wood Box Color", Bools::ConstructionColor::LargeWoodBoxColor);
     SaveColorValue("Construction - Color", "Small Stash Color", Bools::ConstructionColor::SmallStashColor);*/
#pragma endregion 

    cfg.SaveFile(result);
}

void LoadCFG(const char* FileName)
{
    DWORD SerialNumber;

    GetVolumeInformation(L"C:\\", 0, 0, &SerialNumber, 0, 0, 0, 0);

    char Path[0x100];
    sprintf(Path, "C:\\FrogGang.cc\\cfg\\{%lu}\\", SerialNumber);

    if (!folder_exists(Path))
        _mkdir(Path);
    cfg.SetUnicode();
    char result[0x100];
    sprintf(result, "C:\\FrogGang.cc\\cfg\\{%lu}\\%s.ini", SerialNumber, FileName);
    cfg.LoadFile(result);

#pragma region AimBot
    Vars::AimBot::BodyAim = cfg.GetLongValue("Aim", "Body Aim", Vars::AimBot::BodyAim);
    Vars::AimBot::aimkey = cfg.GetLongValue("Aim", "Aim Bot Key", Vars::AimBot::aimkey);
    Vars::AimBot::Range = cfg.GetLongValue("Aim", "Distance", Vars::AimBot::Range);
    Vars::AimBot::Activate = cfg.GetBoolValue("Aim", "Enable", Vars::AimBot::Activate);
    Vars::AimBot::Fov = cfg.GetLongValue("Aim", "Fov", Vars::AimBot::Fov);
    
    //Vars::AimBot::FastReload = cfg.GetLongValue("Aim","FastReload");
    Vars::AimBot::RCS = cfg.GetBoolValue("Aim", "Recoil Control System", Vars::AimBot::RCS);
    Vars::AimBot::Standalone = cfg.GetBoolValue("Aim", "RCS Standalone", Vars::AimBot::Standalone);
    Vars::AimBot::DrawFov = cfg.GetBoolValue("Aim", "Show Fov", Vars::AimBot::DrawFov);
    Vars::AimBot::VisibleCheck = cfg.GetBoolValue("Aim", "Visible Check", Vars::AimBot::VisibleCheck);
#pragma endregion

#pragma region SilentAim
    Vars::AimBot::SilentClear = cfg.GetBoolValue("Silent", "SilentClear", Vars::AimBot::SilentClear);
    Vars::AimBot::silentclearkey = cfg.GetBoolValue("Silent", "SilentClear Key", Vars::AimBot::silentclearkey);
    Vars::AimBot::ThroughWall = cfg.GetBoolValue("Silent", "ThroughWall", Vars::AimBot::ThroughWall);
    Vars::AimBot::EnableSilentAim = cfg.GetBoolValue("Silent", "Enable Silent Aim", Vars::AimBot::EnableSilentAim);
    Vars::AimBot::SilentTarget = cfg.GetBoolValue("Silent", "Target Line", Vars::AimBot::SilentTarget);
    Vars::AimBot::DrawSilentFov = cfg.GetBoolValue("Silent", "Show Silent Fov", Vars::AimBot::DrawSilentFov);
    Vars::AimBot::SilentFov = cfg.GetBoolValue("Silent", "Fov", Vars::AimBot::SilentFov);
#pragma endregion

#pragma region PlayerMisk
    cfg.SetLongValue("Misc", "Always Day", Vars::Visuals::AlwaysDay);
    cfg.SetBoolValue("Misc", "High Jump", Vars::Misc::HighJump);
    cfg.SetLongValue("Misc", "High Jump Value", Vars::Misc::JumpValue);
    cfg.SetBoolValue("Misc", "Jump Aiming", Vars::Misc::JumpAiming);
    cfg.SetBoolValue("Misc", "Swiming", Vars::Misc::SetSwim);
    cfg.SetBoolValue("Misc", "Speed Hack", Vars::Misc::SpeedHack);
    cfg.SetBoolValue("Misc", "Fake Admin", Vars::Misc::FakeAdmin);
    cfg.SetBoolValue("Misc", "Spider Man", Vars::Misc::SpiderMan);
    //cfg.SetBoolValue("Misc", "Custom Fov", Vars::Misc::CustomFov);
  

    Vars::Visuals::AlwaysDay = cfg.GetLongValue("Misc", "Always Day", Vars::Visuals::AlwaysDay);
    Vars::Misc::HighJump = cfg.GetLongValue("Misc", "High Jump", Vars::Misc::HighJump);
    Vars::Misc::JumpValue = cfg.GetBoolValue("Misc", "High Jump Value", Vars::Misc::JumpValue);
    Vars::Misc::JumpAiming = cfg.GetBoolValue("Misc", "Jump Aiming", Vars::Misc::JumpAiming);
    Vars::Misc::FakeAdmin = cfg.GetBoolValue("Misc", "Fake Admin", Vars::Misc::FakeAdmin);
    Vars::Misc::SpeedHack = cfg.GetBoolValue("Misc", "Speed Hack", Vars::Misc::SpeedHack);
    Vars::Misc::SpiderMan = cfg.GetBoolValue("Misc", "Spider Man", Vars::Misc::SpiderMan);
   // Vars::Misc::CustomFov = cfg.GetBoolValue("Misc", "Custom Fov", Vars::Misc::CustomFov);
   
#pragma endregion

#pragma region WeaponMisk
    Vars::Misc::NoRecoil = cfg.GetBoolValue("Weapn", "No Recoil", Vars::Misc::NoRecoil);
    Vars::Misc::AntiSpread = cfg.GetBoolValue("Weapn", "No Spread", Vars::Misc::AntiSpread);
    Vars::Misc::Automatic = cfg.GetBoolValue("Weapn", "Automatic", Vars::Misc::Automatic);
    Vars::Misc::canHoldItems = cfg.GetBoolValue("Weapons", "CanHoldItems", Vars::Misc::canHoldItems);
    Vars::Misc::NoSway = cfg.GetBoolValue("Weapn", "No Sway", Vars::Misc::NoSway);
    Vars::Misc::SuperEoka = cfg.GetBoolValue("Weapn", "100% EOKA", Vars::Misc::SuperEoka);
    Vars::Misc::ShotGunTochka = cfg.GetBoolValue("Weapn", "Shot Gun No Spread", Vars::Misc::ShotGunTochka);
#pragma endregion

#pragma region Player ESP
    Vars::Visuals::PlayerESP = cfg.GetLongValue("Player", "Enable", Vars::Visuals::PlayerESP);
    Vars::Visuals::ShowPlayerBox = cfg.GetLongValue("Player", "Box", Vars::Visuals::ShowPlayerBox);
    Vars::Visuals::ShowPlayerHealth = cfg.GetLongValue("Player", "Health", Vars::Visuals::ShowPlayerHealth);
    Vars::Visuals::InfoTopLeft = cfg.GetBoolValue("Player", "Target Player Info [top left]", Vars::Visuals::InfoTopLeft);
    Vars::Visuals::ShowPlayerDist = cfg.GetLongValue("Player", "Distance", Vars::Visuals::ShowPlayerDist);
    Vars::Visuals::ShowPlayerWeapon = cfg.GetLongValue("Player", "Weapon", Vars::Visuals::ShowPlayerWeapon);
    Vars::Visuals::SkeletonPlayer = cfg.GetLongValue("Player", "Skeleton", Vars::Visuals::SkeletonPlayer);
    Vars::Visuals::Corpse = cfg.GetLongValue("Player", "Corpse", Vars::Visuals::Corpse);
    Vars::Visuals::IgnoreSleepers = cfg.GetBoolValue("Player", "Ignore Sleepers", Vars::Visuals::IgnoreSleepers);
#pragma endregion

#pragma region Bots ESP
    Vars::Visuals::BotsESP = cfg.GetLongValue("Bots", "Enable", Vars::Visuals::BotsESP);
    Vars::Visuals::SkeletonBots = cfg.GetLongValue("Bots", "Skeleton", Vars::Visuals::SkeletonBots);
#pragma endregion

#pragma region Resources ESP

    cfg.SetBoolValue("Resources", "Sulphur", Vars::Visuals::Sulphur);
    cfg.SetBoolValue("Resources", "Metal", Vars::Visuals::Metal);
    cfg.SetBoolValue("Resources", "Stone", Vars::Visuals::Stone);
    cfg.SetLongValue("Resources", "Stash", Vars::Visuals::Stash);
    cfg.SetBoolValue("Resources", "MiniCopter", Vars::Visuals::Minicopter);
    cfg.SetLongValue("Resources", "Patrol Helicopter", Vars::Visuals::Patrul);
    cfg.SetBoolValue("Resources", "Traps", Vars::Visuals::Traps);
    cfg.SetLongValue("Resources", "Hemp", Vars::Visuals::Hemp);
    cfg.SetLongValue("Resources", "Supply", Vars::Visuals::Supply);

    Vars::Visuals::Sulphur = cfg.GetBoolValue("Resources", "Sulphur", Vars::Visuals::Sulphur);
    Vars::Visuals::Metal = cfg.GetBoolValue("Resources", "Metal", Vars::Visuals::Metal);
    Vars::Visuals::Stone = cfg.GetBoolValue("Resources", "Stone", Vars::Visuals::Stone);
    Vars::Visuals::Stash = cfg.GetLongValue("Resources", "Stash", Vars::Visuals::Stash);
    Vars::Visuals::Minicopter = cfg.GetBoolValue("Resources", "MiniCopter", Vars::Visuals::Minicopter);
    Vars::Visuals::Patrul = cfg.GetLongValue("Resources", "Patrol Helicopter", Vars::Visuals::Patrul);
    Vars::Visuals::Traps = cfg.GetBoolValue("Resources", "Traps", Vars::Visuals::Traps);
    Vars::Visuals::Hemp = cfg.GetLongValue("Resources", "Hemp", Vars::Visuals::Hemp);
    Vars::Visuals::Supply = cfg.GetLongValue("Resources", "Supply", Vars::Visuals::Supply);
#pragma endregion

#pragma region Radar
      /*Bools::Visual::Radar::Enable = cfg.GetBoolValue("Radar", "Enable", Bools::Visual::Radar::Enable);
      Bools::Visual::Radar::ShowRadarStoneOre = cfg.GetBoolValue("Radar", "Show Radar Stone Ore", Bools::Visual::Radar::ShowRadarStoneOre);
      Bools::Visual::Radar::ShowRadarMettalOre = cfg.GetBoolValue("Radar", "Show Radar Mettal Ore", Bools::Visual::Radar::ShowRadarMettalOre);
      Bools::Visual::Radar::ShowRadarSulfureOre = cfg.GetBoolValue("Radar", "Show Radar Sulfure Ore", Bools::Visual::Radar::ShowRadarSulfureOre);
      Bools::Visual::Radar::ShowRadarBackground = cfg.GetBoolValue("Radar", "Show Radar Background", Bools::Visual::Radar::ShowRadarBackground);
      Bools::Visual::Radar::ShowRadarPlayer = cfg.GetBoolValue("Radar", "Show Radar Player", Bools::Visual::Radar::ShowRadarPlayer);
      Bools::Visual::Radar::ShowRadarSleeper = cfg.GetBoolValue("Radar", "Show Radar Sleeper", Bools::Visual::Radar::ShowRadarSleeper);
      Bools::Visual::Radar::EnableDinamicRadar = cfg.GetBoolValue("Radar", "Enable Dinamic Radar", Bools::Visual::Radar::EnableDinamicRadar);
      Bools::Visual::Radar::Pos_X = cfg.GetLongValue("Radar", "Pos X", Bools::Visual::Radar::Pos_X);
      Bools::Visual::Radar::Pos_Y = cfg.GetLongValue("Radar", "Pos Y", Bools::Visual::Radar::Pos_Y);
      Bools::Visual::Radar::Radar_Size = cfg.GetLongValue("Radar", "Radar Size", Bools::Visual::Radar::Radar_Size);
      Bools::Visual::Radar::Radar_Range = cfg.GetLongValue("Radar", "Radar Range", Bools::Visual::Radar::Radar_Range);*/
#pragma endregion

#pragma region Construction ESP
      /*Bools::ConstructionESP::Enable = cfg.GetBoolValue("Construction - ESP", "Enable", Bools::ConstructionESP::Enable);
       Bools::ConstructionESP::ShowCupboard = cfg.GetBoolValue("Construction - ESP", "Show Cupboard", Bools::ConstructionESP::ShowCupboard);
       Bools::ConstructionESP::CupboardDistation = cfg.GetLongValue("Construction - ESP", "Cupboard Distation", Bools::ConstructionESP::CupboardDistation);
       Bools::ConstructionESP::ShowLargeWoodBox = cfg.GetBoolValue("Construction - ESP", "Show Large Wood Box", Bools::ConstructionESP::ShowLargeWoodBox);
       Bools::ConstructionESP::LargeWoodBoxDistation = cfg.GetLongValue("Construction - ESP", "Large Wood Box Distation", Bools::ConstructionESP::LargeWoodBoxDistation);
       Bools::ConstructionESP::SmallStashDistance = cfg.GetLongValue("Construction - ESP", "Small Stash Distation", Bools::ConstructionESP::SmallStashDistance);
       Bools::ConstructionESP::ShowSmallStash = cfg.GetBoolValue("Construction - ESP", "Show Small Stash", Bools::ConstructionESP::ShowSmallStash);*/
#pragma endregion 

#pragma region Aim Color
       LoadColorValue("Aim - Color", "Fov Color", Vars::Color::Fov);
       LoadColorValue("Aim - Color", "Target Line Color", Vars::Color::SilentColor);
#pragma endregion

#pragma region Radar Color
       /* LoadColorValue("Radar - Color", "Radar Background Color", Bools::RadarColor::RadarBackground);
        LoadColorValue("Radar - Color", "Radar Player Color", Bools::RadarColor::RadarPlayerColor);
        LoadColorValue("Radar - Color", "Radar Player Sleeper Color", Bools::RadarColor::RadarPlayerSleeperColor);
        LoadColorValue("Radar - Color", "Radar Stone Ore Color", Bools::RadarColor::RadarStoneOreColor);
        LoadColorValue("Radar - Color", "Radar Mettal Ore Color", Bools::RadarColor::RadarMettalOreColor);
        LoadColorValue("Radar - Color", "Radar Sulfure Sleeper Color", Bools::RadarColor::RadarSulfureOreColor);*/

#pragma endregion

#pragma region Bots Color
        /* LoadColorValue("Bots - Color", "Bots Render String Color", Bools::BotsColor::BotRenderStringColor);
         LoadColorValue("Bots - Color", "Bots Skeleton Color", Bools::BotsColor::BotSkeletonColor);
         LoadColorValue("Bots - Color", "Bots Box Color", Bools::BotsColor::BotBoxColor);
         LoadColorValue("Bots - Color", "Bots Fill Box Color", Bools::BotsColor::BotFillBoxColor);*/
#pragma endregion

#pragma region Player Color
         /*LoadColorValue("Player - Color", "Player Render String Color", Bools::PlayerColor::PlayerRenderStringColor);
         LoadColorValue("Player - Color", "Player Skeleton Color", Bools::PlayerColor::PlayerSkeletonColor);
         LoadColorValue("Player - Color", "Player Box Color", Bools::PlayerColor::PlayerBoxColor);
         LoadColorValue("Player - Color", "Player Sleeper Color", Bools::PlayerColor::PlayerSleeperColor);
         LoadColorValue("Player - Color", "Player Wounded Color", Bools::PlayerColor::PlayerWoundedColor);
         LoadColorValue("Player - Color", "Player Fill Box Color", Bools::PlayerColor::PlayerFillBoxColor);
         LoadColorValue("Player - Color", "Player Dead Color", Bools::PlayerColor::PlayerDeadColor);
         LoadColorValue("Player - Color", "Player Backpack Color", Bools::PlayerColor::PlayerBackpackColor);*/
#pragma endregion

#pragma region Resourse Color
         /*LoadColorValue("Resourse - Color", "Stone - Ore Color", Bools::ResourcesColor::StoneOreColor);
         LoadColorValue("Resourse - Color", "Mettal - Ore Color", Bools::ResourcesColor::MettalOreColor);
         LoadColorValue("Resourse - Color", "Sulfure - Ore Color", Bools::ResourcesColor::SulfureOreColor);*/
#pragma endregion

#pragma region Construction Color
         /*LoadColorValue("Construction - Color", "Cupboard Color", Bools::ConstructionColor::CupboardColor);
         LoadColorValue("Construction - Color", "Large Wood Box Color", Bools::ConstructionColor::LargeWoodBoxColor);
         LoadColorValue("Construction - Color", "Small Stash Color", Bools::ConstructionColor::SmallStashColor);*/
#pragma endregion 
};