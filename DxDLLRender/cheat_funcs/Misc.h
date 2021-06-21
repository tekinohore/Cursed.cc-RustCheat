void Misc()
{
	if (Vars::Misc::HighJump) {
		if (FC(user32, GetAsyncKeyState, Vars::Misc::highkey))
			LocalPlayer.BasePlayer->SetGravity(Vars::Misc::JumpValue);
		else LocalPlayer.BasePlayer->SetGravity(3.0f);
	}

	//air stuck
	if (Vars::Misc::AirStuck) {
		if (FC(user32, GetAsyncKeyState, VK_XBUTTON1))
			LocalPlayer.BasePlayer->AirStuck(true);
		else LocalPlayer.BasePlayer->AirStuck(false);
	}

	if (Vars::Misc::CustomFov)
		LocalPlayer.BasePlayer->SetFov();

	if (Vars::Misc::Zoom)
		LocalPlayer.BasePlayer->Zoom();

	//boost speed on water
	if (Vars::Misc::WaterBoost)
		LocalPlayer.BasePlayer->WaterBoost();

	if (Vars::Misc::Antiafk)
		LocalPlayer.BasePlayer->SetRemoveFlag(4);

	if (Vars::Misc::DebugBypass)
		LocalPlayer.BasePlayer->PatchDebug();

	if (Vars::Misc::swiming && GetAsyncKeyState(0x58))
		LocalPlayer.BasePlayer->Swim();

	if (Vars::Misc::CustomFov)
		LocalPlayer.BasePlayer->mouse_move();

	if (Vars::Misc::LongNeck) {
		if (FC(user32, GetAsyncKeyState, Vars::Misc::LongNeckkey))
			LocalPlayer.BasePlayer->LongNeck(Vars::AimBot::LongNeckvolue);
		//else LocalPlayer.BasePlayer->LongNeck(3);
	}

	//on aim on kastrulya
	if (Vars::Misc::AntiKastrulya)
		LocalPlayer.BasePlayer->NoBlockAiming();

	//boost speed on heavy armor
	if (Vars::Misc::NoHeavyReduct)
		LocalPlayer.BasePlayer->NoHeavyReduct();

	//fakebench
	if (Vars::Misc::WorkBench)
		LocalPlayer.BasePlayer->FakeWorkBench(4194304);

	if (Vars::Misc::ThirdPersone)
		LocalPlayer.BasePlayer->FakeThirdPerson(1024);

	if (Vars::Misc::AirStuck) {
		if (FC(user32, GetAsyncKeyState, VK_XBUTTON1))
			LocalPlayer.BasePlayer->AirStuck(true);
		else LocalPlayer.BasePlayer->AirStuck(false);
	}
	//boost speed on water
	if (Vars::Misc::WaterBoost)
		LocalPlayer.BasePlayer->WaterBoost();
	//spider man
	if (Vars::Misc::SpiderMan)
		LocalPlayer.BasePlayer->SpiderMan();

	if (Vars::Misc::InfinityJump)
		if (FC(user32, GetAsyncKeyState, VK_SPACE))
			LocalPlayer.BasePlayer->InfinityJump();
	//remove weapon sway
	if (Vars::Misc::NoSway)
		LocalPlayer.BasePlayer->NoSway();
	if (Vars::Misc::FakeAdmin)
		LocalPlayer.BasePlayer->FakeAdmin(4);


	if (Vars::Visuals::NightMode) {
		LocalPlayer.BasePlayer->Pizda228();
		return;
	}
}

