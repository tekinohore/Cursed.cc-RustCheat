void EspPreview()
{
	static bool enabled = true;
	ImGui::SetNextWindowSize(ImVec2(200, 400));
	ImGui::Begin("ESP Preview", &enabled, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	{
		auto cur_window = ImGui::GetCurrentWindow();
		ImVec2 w_pos = cur_window->Pos;
		if (Vars::Visuals::Box)
		{
			cur_window->DrawList->AddRect(ImVec2(w_pos.x + 40, w_pos.y + 60), ImVec2(w_pos.x + 200, w_pos.y + 360), ImColor(Vars::Color::BoxColor));
		}
		if (Vars::Visuals::Name)
		{
			cur_window->DrawList->AddText(ImVec2{ w_pos.x + 210, w_pos.y + 75 }, ImColor(Vars::Color::NameColor), "NAME");
		}
		if (Vars::Visuals::Dist)
		{
			cur_window->DrawList->AddText(ImVec2{ w_pos.x + 210, w_pos.y + 105 }, ImColor(Vars::Color::DistanceColor), "228 M");
		}
		if (Vars::Visuals::Weapon)
		{
			cur_window->DrawList->AddText(ImVec2{ w_pos.x + 210, w_pos.y + 120 }, ImColor(Vars::Color::WeaponColor), "WEAPON");
		}
	}
	ImGui::End();
}

void InitCheat()
{
	float Y = GetSystemMetrics(SM_CYSCREEN);

	Vector2 kek = GUI::Render.CanvasSize();
	Vars::Global::ScreenWidth = kek.x;
	Vars::Global::ScreenHigh = kek.y;


	if (Vars::AimBot::BodyAim) Vars::Global::BoneToAim = 1;
	else Vars::Global::BoneToAim = BoneList(neck);

	if (Vars::Visuals::Crosshair)
		Crosshair();

	if (Vars::Visuals::CircleCrosshair)
		circlecrosshair();

	if (Vars::Visuals::SEXCrosshair)
		SEXCrosshair();

	if (Vars::Visuals::Collapse)
		Collapse();

	if (Vars::Visuals::Colapse1)
		Collaps1();

	if (Vars::Visuals::SEXXCrosshair)
		SEXXCrosshair();

	if (Vars::AimBot::DrawFov)
		DrawFOV();

	if (Vars::AimBot::DrawSilentFov)
		DrawSilentFOV();

	if (GetAsyncKeyState(Vars::AimBot::silentclearkey) && Vars::AimBot::SilentClear)
		TargetSilentPlayer = NULL;

	if (GetAsyncKeyState(Vars::AimBot::Psilentclearkey) && Vars::AimBot::PSilentClear)
		TargetPSilentPlayer = NULL;

	static float r = 1.00f, g = 0.00f, b = 1.00f;
	static int cases = 0;
	switch (cases)
	{
	case 0: { r -= 0.005f; if (r <= 0) cases += 1; break; }
	case 1: { g += 0.005f; b -= 0.005f; if (g >= 1) cases += 1; break; }
	case 2: { r += 0.005f; if (r >= 1) cases += 1; break; }
	case 3: { b += 0.005f; g -= 0.005f; if (b >= 1) cases = 0; break; }
	default: { r = 1.00f; g = 0.00f; b = 1.00f; break; }
	}
	GUI::Render.String({ 20.f, 10.f }, (L"Cursed.cc itsukami#3544" "[" __DATE__ "]"), D2D1::ColorF(r, g, b, 111.f));

	Entity();
}
