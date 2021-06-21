#include <d3d9.h>
#include "cheat_funcs/Entity.h"
#include "../ImGUI/imgui_internal.h"

inline void CornerBox(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF color)
{
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 2.5f, Entity_y }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 2.5f, Entity_y }, color);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 2.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 2.5f }, color);

	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 2.5f, Entity_y }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 2.5f, Entity_y }, color);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 2.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 2.5f }, color);

	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 2.5f, Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 2.5f, Entity_y + Entity_h }, color);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 2.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 2.5f }, color);

	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 2.5f, Entity_y + Entity_h }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 2.5f, Entity_y + Entity_h }, color);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 2.5f }, D2D1::ColorF::Black, 3.f);
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 2.5f }, color);
	if (Vars::Visuals::FillBox)
		GUI::Render.FillRectangle(Vector2(Entity_x, Entity_y), Vector2(Entity_w, Entity_h), D2D1::ColorF::Black);
}

inline void PlayerBoxK(float Entity_x, float Entity_y, float Entity_w, float Entity_h, D2D1::ColorF color)
{
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x + Entity_w / 2.f,Entity_y }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor));
	GUI::Render.Line({ Entity_x, Entity_y }, { Entity_x,Entity_y + Entity_h / 2.f }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor));
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { (Entity_x + Entity_w) - Entity_w / 2.f,Entity_y }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor));
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y }, { Entity_x + Entity_w,Entity_y + Entity_h / 2.f }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor));
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { (Entity_x + Entity_w) - Entity_w / 2.f,Entity_y + Entity_h }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor));
	GUI::Render.Line({ Entity_x + Entity_w, Entity_y + Entity_h }, { Entity_x + Entity_w,(Entity_y + Entity_h) - Entity_h / 2.f }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor));
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x + Entity_w / 2.f,Entity_y + Entity_h }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor));
	GUI::Render.Line({ Entity_x, Entity_y + Entity_h }, { Entity_x,(Entity_y + Entity_h) - Entity_h / 2.f }, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor));
}

D3DCOLOR rainbow() {

	static float x = 0, y = 0;
	static float r = 0, g = 0, b = 0;

	if (y >= 0.0f && y < 255.0f) {
		r = 255.0f;
		g = 0.0f;
		b = x;
	}
	else if (y >= 255.0f && y < 510.0f) {
		r = 255.0f - x;
		g = 0.0f;
		b = 255.0f;
	}
	else if (y >= 510.0f && y < 765.0f) {
		r = 0.0f;
		g = x;
		b = 255.0f;
	}
	else if (y >= 765.0f && y < 1020.0f) {
		r = 0.0f;
		g = 255.0f;
		b = 255.0f - x;
	}
	else if (y >= 1020.0f && y < 1275.0f) {
		r = x;
		g = 255.0f;
		b = 0.0f;
	}
	else if (y >= 1275.0f && y < 1530.0f) {
		r = 255.0f;
		g = 255.0f - x;
		b = 0.0f;
	}

	x += Vars::GG::time;//скорость изменения цветов
	if (x >= 255.0f)
		x = 0.0f;

	y += Vars::GG::time; //скорость изменения цветов
	if (y > 1530.0f)
		y = 0.0f;


	return D3DCOLOR_ARGB((int)r, (int)g, (int)b, 255);
}


D3DCOLOR FLOAT4TOD3DCOLOR(float Col[])
{
	ImU32 col32_no_alpha = ImGui::ColorConvertFloat4ToU32(ImVec4(Col[0], Col[1], Col[2], Col[3]));
	float a = (col32_no_alpha >> 24) & 255;
	float r = (col32_no_alpha >> 16) & 255;
	float g = (col32_no_alpha >> 8) & 255;
	float b = col32_no_alpha & 255;
	return D3DCOLOR_ARGB((int)a, (int)b, (int)g, (int)r);
}
void Skeleton(BasePlayer* BasePlayer)
{
	BoneList Bones[15] = {
		/*LF*/l_foot, l_knee, l_hip,
		/*RF*/r_foot, r_knee, r_hip,
		/*BD*/spine1, neck, head,
		/*LH*/l_upperarm, l_forearm, l_hand,
		/*RH*/r_upperarm, r_forearm, r_hand
	}; Vector2 BonesPos[15];

	//get bones screen pos
	for (int j = 0; j < 15; j++) {
		if (!LocalPlayer.WorldToScreen(BasePlayer->GetBoneByID(Bones[j]), BonesPos[j]))
			return;
	}

	//draw main lines
	for (int j = 0; j < 15; j += 3) {
		GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
		GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
		GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Black, true);
		GUI::Render.Line(Vector2{ BonesPos[j].x, BonesPos[j].y }, Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, D2D1::ColorF::Black, true);

		GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
		GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
		GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Black, true);
		GUI::Render.Line(Vector2{ BonesPos[j + 1].x, BonesPos[j + 1].y }, Vector2{ BonesPos[j + 2].x, BonesPos[j + 2].y }, D2D1::ColorF::Black, true);

	}

	//draw add lines
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Black, true);
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Black, true);
	GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
	GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Black, true);

	GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
	GUI::Render.Line(Vector2{ BonesPos[5].x, BonesPos[5].y }, Vector2{ BonesPos[6].x, BonesPos[6].y }, D2D1::ColorF::Black, true);
	GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
	GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Black, true);

	GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
	GUI::Render.Line(Vector2{ BonesPos[9].x, BonesPos[9].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Black, true);

	GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
	GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Black, true);
	GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, FLOAT4TOD3DCOLOR(Vars::Color::SkeletonColor));
	GUI::Render.Line(Vector2{ BonesPos[12].x, BonesPos[12].y }, Vector2{ BonesPos[7].x, BonesPos[7].y }, D2D1::ColorF::Black, true);
}

void MemeBox(const D2D1::ColorF& PlayerClr, BasePlayer* BasePlayer)
{
	BoneList Bones[4] = {
		/*UP*/l_upperarm, r_upperarm,
		/*DOWN*/r_foot, l_foot
	}; Vector2 BonesPos[4];

	//get bones screen pos
	for (int j = 0; j < 4; j++) {
		if (!LocalPlayer.WorldToScreen(BasePlayer->GetBoneByID(Bones[j]), BonesPos[j]))
			return;
	}

	//draw main lines
	GUI::Render.Line(Vector2{ BonesPos[0].x, BonesPos[0].y }, Vector2{ BonesPos[1].x, BonesPos[1].y }, rainbow(), Vars::HvH::Tick2);
	GUI::Render.Line(Vector2{ BonesPos[0].x, BonesPos[0].y }, Vector2{ BonesPos[3].x, BonesPos[3].y }, rainbow(), Vars::HvH::Tick2);
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[1].x, BonesPos[1].y }, rainbow(), Vars::HvH::Tick2);
	GUI::Render.Line(Vector2{ BonesPos[2].x, BonesPos[2].y }, Vector2{ BonesPos[3].x, BonesPos[3].y }, rainbow(), Vars::HvH::Tick2);
}
inline void InventoryRender(BasePlayer* BP)
{
	for (int i = 0; i < 6; i++)
	{
		WeaponData* ActWeapon = BP->GetWeaponInfo(i);
		if (!ActWeapon)
		{
			const wchar_t* ActiveWeaponName = BP->GetWeaponInfo(i)->GetName();
			if (wcslen(ActiveWeaponName) < 20)
			{
				GUI::Render.String(Vector2(15, 80), ActiveWeaponName, D2D1::ColorF(255.f, 255.f, 255.f));
			}
		}
		else
		{
			GUI::Render.String(Vector2(15, 20), L"Nothing", D2D1::ColorF(255.f, 255.f, 255.f));
		}
	}
}
__forceinline float Distance2D(const Vector2& Src, const Vector2& Dst)
{
	return sqrt(powf(Src.x - Dst.x, 2) + powf(Src.y - Dst.y, 2));
}
inline float SlotRender(BasePlayer* Entity, BoneList Bone)
{
	Vector2 ScreenPos;
	if (!LocalPlayer.WorldToScreen(Entity->GetBoneByID(Bone), ScreenPos)) return 1000.f;
	return Distance2D(Vector2(Vars::Global::ScreenWidth1 / 2, Vars::Global::ScreenHigh1 / 2), ScreenPos);
}
void Crosshair()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	if (Vars::Misc::rainbow)
	{
		GUI::Render.Line(Vector2{ xs, ys - 6 }, Vector2{ xs , ys + 6 }, rainbow(), Vars::HvH::Tick2);
		GUI::Render.Line(Vector2{ xs - 6, ys }, Vector2{ xs + 6, ys }, rainbow(), Vars::HvH::Tick2);
	}
	else
	{
		GUI::Render.Line(Vector2{ xs, ys - 6 }, Vector2{ xs , ys + 6 }, FLOAT4TOD3DCOLOR(Vars::Color::CrosshairColors), Vars::HvH::Tick2);
		GUI::Render.Line(Vector2{ xs - 6, ys }, Vector2{ xs + 6, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CrosshairColors), Vars::HvH::Tick2);
	}
}
void Crosshair1()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;
	if (Vars::Misc::Crosshair1)
	{
		GUI::Render.Line(Vector2{ xs, ys - 5 }, Vector2{ xs , ys + 5 }, FLOAT4TOD3DCOLOR(Vars::Color::CrosshairColors));
		GUI::Render.Line(Vector2{ xs - 5, ys }, Vector2{ xs + 5, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CrosshairColors));
	}
}

void Collaps1()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;
	GUI::Render.Line(Vector2{ xs, ys - -11 }, Vector2{ xs , ys + 2 }, D2D1::ColorF::Black, 3.6f);
	GUI::Render.Line(Vector2{ xs - -11, ys }, Vector2{ xs + 2, ys }, D2D1::ColorF::Black, 3.6f);
	GUI::Render.Line(Vector2{ xs, ys - 2 }, Vector2{ xs , ys + -11 }, D2D1::ColorF::Black, 3.6f);
	GUI::Render.Line(Vector2{ xs - 2, ys }, Vector2{ xs + -11, ys }, D2D1::ColorF::Black, 3.6f);
	GUI::Render.Line(Vector2{ xs, ys - -10 }, Vector2{ xs , ys + 3 }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
	GUI::Render.Line(Vector2{ xs - -10, ys }, Vector2{ xs + 3, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
	GUI::Render.Line(Vector2{ xs, ys - 3 }, Vector2{ xs , ys + -10 }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
	GUI::Render.Line(Vector2{ xs - 3, ys }, Vector2{ xs + -10, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
}


void circlecrosshair()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	if (Vars::Visuals::CircleCrosshair)
	{
		GUI::Render.FillCircle(Vector2{ xs - 1, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor), Vars::HvH::Tick2);
	}
}

void Collapse()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;
	GUI::Render.Line(Vector2{ xs, ys - -21 }, Vector2{ xs , ys + 4 }, D2D1::ColorF::Black, 3.6f);
	GUI::Render.Line(Vector2{ xs - -21, ys }, Vector2{ xs + 4, ys }, D2D1::ColorF::Black, 3.6f);
	GUI::Render.Line(Vector2{ xs, ys - 4 }, Vector2{ xs , ys + -21 }, D2D1::ColorF::Black, 3.6f);
	GUI::Render.Line(Vector2{ xs - 4, ys }, Vector2{ xs + -21, ys }, D2D1::ColorF::Black, 3.6f);
	GUI::Render.Line(Vector2{ xs, ys - -20 }, Vector2{ xs , ys + 5 }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
	GUI::Render.Line(Vector2{ xs - -20, ys }, Vector2{ xs + 5, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
	GUI::Render.Line(Vector2{ xs, ys - 5 }, Vector2{ xs , ys + -20 }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
	GUI::Render.Line(Vector2{ xs - 5, ys }, Vector2{ xs + -20, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
}

void SEXCrosshair()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	GUI::Render.Line(Vector2{ xs - 3, ys  -3 }, Vector2{ xs , ys + 3 }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
	GUI::Render.Line(Vector2{ xs - 3, ys -3}, Vector2{ xs + 3, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
}

void Crosshair11()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	if (Vars::Misc::rainbow)
	{
		GUI::Render.Line(Vector2{ xs, ys - 6 }, Vector2{ xs , ys + 6 }, rainbow(), Vars::HvH::Tick2);
		GUI::Render.Line(Vector2{ xs - 6, ys }, Vector2{ xs + 6, ys }, rainbow(), Vars::HvH::Tick2);
	}
	else
	{
		GUI::Render.Line(Vector2{ xs, ys - 4 }, Vector2{ xs , ys + 4 }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor), Vars::HvH::Tick2);
		GUI::Render.Line(Vector2{ xs - 4, ys }, Vector2{ xs + 4, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor), Vars::HvH::Tick2);
		GUI::Render.Line(Vector2{ xs, ys - 4 }, Vector2{ xs , ys + 4 }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor), Vars::HvH::Tick2);
		GUI::Render.Line(Vector2{ xs - 4, ys }, Vector2{ xs + 4, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor), Vars::HvH::Tick2);
	}

	if (Vars::Misc::rainbow)
	{
		GUI::Render.Line(Vector2{ xs, ys - 6 }, Vector2{ xs , ys + 6 }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
		GUI::Render.Line(Vector2{ xs - 6, ys }, Vector2{ xs + 6, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
	}
	else
	{
		GUI::Render.Line(Vector2{ xs, ys - 4 }, Vector2{ xs , ys + 4 }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
		GUI::Render.Line(Vector2{ xs - 4, ys }, Vector2{ xs + 4, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
		GUI::Render.Line(Vector2{ xs, ys - 4 }, Vector2{ xs , ys + 4 }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
		GUI::Render.Line(Vector2{ xs - 4, ys }, Vector2{ xs + 4, ys }, FLOAT4TOD3DCOLOR(Vars::Color::CollapseColor));
	}
}

void SEXXCrosshair()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;

	Vector2 top = Vector2(xs, ys + 10);
	Vector2 right = Vector2(xs + 10, ys);
	Vector2 bottom = Vector2(xs, ys - 10);
	Vector2 left = Vector2(xs - 10, ys);

	GUI::Render.Line(Vector2{ xs, ys - 11 }, Vector2{ xs , ys + 11 }, rainbow(), Vars::HvH::Tick2);
	GUI::Render.Line(Vector2{ xs - 11, ys }, Vector2{ xs + 11, ys }, rainbow(), Vars::HvH::Tick2);



	GUI::Render.Line(top, Vector2(top.x + 10, top.y), rainbow(), Vars::HvH::Tick2);
	GUI::Render.Line(right, Vector2(right.x, right.y - 10), rainbow(), Vars::HvH::Tick2);
	GUI::Render.Line(bottom, Vector2(bottom.x - 10, bottom.y), rainbow(), Vars::HvH::Tick2);
	GUI::Render.Line(left, Vector2(left.x, left.y + 10), rainbow(), Vars::HvH::Tick2);
}

void DrawFOV()
{
	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;
	GUI::Render.Сircle(Vector2{ xs, ys }, FLOAT4TOD3DCOLOR(Vars::Color::Fov), Vars::AimBot::Fov, 0.7f);
	GUI::Render.FillCircle(Vector2{ xs, ys }, D2D1::ColorF(0, 0, 0, 0.45), Vars::AimBot::Fov / Vars::Visuals::FillFov);
}

void DrawSilentFOV()
{
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

	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;
	GUI::Render.Сircle(Vector2{ xs, ys }, D2D1::ColorF(r, g, b, 1.f), Vars::AimBot::SilentFov, 0.5f);
	GUI::Render.Сircle(Vector2{ xs, ys }, D2D1::ColorF(r, g, b, 1.f), Vars::AimBot::SilentFov, 0.5f);
}

inline void HpBar(BasePlayer* player)
{                                         
	Vector2 tempFeetR, tempFeetL, tempHead;

	if (LocalPlayer.WorldToScreen(player->GetBoneByID(r_foot), tempFeetR) && LocalPlayer.WorldToScreen(player->GetBoneByID(l_foot), tempFeetL) && LocalPlayer.WorldToScreen(player->GetBoneByID(jaw) + Vector3(0.f, 0.22f, 0.f), tempHead))
	{
		Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
		float Entity_h = tempHead.y - tempFeet.y;
		float w = Entity_h / 4;
		float Entity_x = tempFeet.x - w;
		float Entity_y = tempFeet.y;
		float Entity_w = Entity_h / 2;
		float health = player->GetHealth();
		float maxheal = 100.f;
		D2D1::ColorF HpColor = D2D1::ColorF::Green;
		if (health > 75)
			HpColor = D2D1::ColorF::Green;
		else
		{
			if (health < 45)
				HpColor = D2D1::ColorF::Red;
			else
				HpColor = D2D1::ColorF::Orange;
		}

		GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5 ,Entity_h * (health / maxheal) }, HpColor);
		GUI::Render.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5 ,Entity_h }, D2D1::ColorF::Black, 0.5f);
	}
}

//void DrawPSilentFov()
//{
//	float xs = Vars::Global::ScreenWidth / 2, ys = Vars::Global::ScreenHigh / 2;
//	GUI::Render.Сircle(Vector2{ xs, ys }, FLOAT4TOD3DCOLOR(Vars::Color::SilentFovColor), Vars::AimBot::SilentFov, 0.7f);
//	GUI::Render.Сircle(Vector2{ xs, ys }, FLOAT4TOD3DCOLOR(Vars::Color::SilentFovColor), Vars::AimBot::SilentFov);
//}

#pragma region Player ESP

#pragma region Player ESP

void ESP(BasePlayer* BP, BasePlayer* LP)
{
	bool PlayerSleeping = BP->HasFlags(16);
	if (Vars::Visuals::IgnoreSleepers && PlayerSleeping)
		return;

	if (Vars::Visuals::SkeletonPlayer && BP->GetSteamID() > 1000000000)
	{
		Skeleton(BP);
	}

	else if (Vars::Visuals::SkeletonBots && BP->GetSteamID() < 1000000000)
	{
		Skeleton(BP);
	}

	Vector2 tempFeetR, tempFeetL;
	if (LocalPlayer.WorldToScreen(BP->GetBoneByID(r_foot), tempFeetR) && LocalPlayer.WorldToScreen(BP->GetBoneByID(l_foot), tempFeetL))
	{
		Vector2 tempHead;
		if (LocalPlayer.WorldToScreen(BP->GetBoneByID(jaw) + Vector3(0.f, 0.16f, 0.f), tempHead))
		{
			Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
			float Entity_h = tempHead.y - tempFeet.y;
			float w = Entity_h / 4;
			float Entity_x = tempFeet.x - w;
			float Entity_y = tempFeet.y;
			float Entity_w = Entity_h / 2;
			Vector2 middlePointPlayerFeet;
			bool PlayerWounded = BP->HasFlags(64);
			D2D1::ColorF::Enum PlayerClr = PlayerSleeping ? D2D1::ColorF::BlueViolet : PlayerWounded ? D2D1::ColorF::DarkOrange : D2D1::ColorF::Gold;

			int CurPos = 0;

			if (Vars::Visuals::PlayerESP && BP->GetSteamID() > 1000000000)
			{
				const float PlayerDist = Math::Calc3D_Dist(LocalPlayer.BasePlayer->GetBoneByID(head), BP->GetBoneByID(head));
				wchar_t ActivePlayer[64];

				if (wcslen(BP->GetName()) > 0)
				{
					if (Vars::Visuals::ShowPlayerName && Vars::Visuals::ShowPlayerDist)
					{
						_swprintf(ActivePlayer, L"%s [%d m]", BP->GetName(), static_cast<int>(PlayerDist));
					}
					else if (Vars::Visuals::ShowPlayerDist)
					{
						_swprintf(ActivePlayer, L"%d m", static_cast<int>(PlayerDist));
					}
					else if (Vars::Visuals::ShowPlayerName)
					{
						_swprintf(ActivePlayer, L"%s", BP->GetName());
					}
					GUI::Render.RenderString(Vector2{ Entity_x, Entity_y + Entity_h - 6 }, ActivePlayer, true, D2D1::ColorF::Black, true);
					GUI::Render.RenderString(Vector2{ Entity_x, Entity_y + Entity_h - 6 }, ActivePlayer, true, FLOAT4TOD3DCOLOR(Vars::Color::NameColor));
				}

				const Color BoxVisibleColor = Color(0.16, 0.55, 0.25, 1); //green
				const Color BoxInVisibleColor = Color(1, 0, 0.08, 1); //red
				const Color BoxTeammateColor = Color(0, 0.23, 1, 1); //blue
				const Color BoxFillColor = Color(0.33, 0.33, 0.33, 0.5); //gray
				if(Vars::Visuals::boxxuina)
				{ 
					if (!PlayerWounded && !PlayerSleeping)
					{
						CornerBox(Entity_x, Entity_y, Entity_w, Entity_h, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor));
					}	
					if (Vars::Visuals::ShowPlayerHealth)
					{
						Vector2 tempFeetR, tempFeetL, tempHead;

						if (LocalPlayer.WorldToScreen(BP->GetBoneByID(r_foot), tempFeetR) && LocalPlayer.WorldToScreen(BP->GetBoneByID(l_foot), tempFeetL) && LocalPlayer.WorldToScreen(BP->GetBoneByID(jaw) + Vector3(0.f, 0.22f, 0.f), tempHead))
						{
							Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
							float Entity_h = tempHead.y - tempFeet.y;
							float w = Entity_h / 4;
							float Entity_x = tempFeet.x - w;
							float Entity_y = tempFeet.y;
							float Entity_w = Entity_h / 2;
							float health = BP->GetHealth();
							float maxheal = 100.f;
							D2D1::ColorF HpColor = D2D1::ColorF::Green;
							if (health > 75)
								HpColor = D2D1::ColorF::Green;
							else
							{
								if (health < 45)
									HpColor = D2D1::ColorF::Red;
								else
									HpColor = D2D1::ColorF::Orange;
							}

							{
								GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 3 ,Entity_h * (health / maxheal) }, HpColor);
								GUI::Render.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 3 ,Entity_h }, D2D1::ColorF::Black, 0.5f);
							}
							if ((int)BP->GetHealth() <= 33)
							{
								GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5 ,Entity_h * (health / maxheal) }, HpColor);
							}
							if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66)
							{
								GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5 ,Entity_h * (health / maxheal) }, HpColor);
							}
							if ((int)BP->GetHealth() >= 67)
							{
								GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5 ,Entity_h * (health / maxheal) }, HpColor);
							}
							GUI::Render.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
						}
					}
					if (Vars::Visuals::ShowPlayerWeapon)
					{
						const wchar_t* active_weapon;
						float TextPos_Y = 10.f;
						WeaponData* ActWeapon = BP->GetActiveWeapon();
						if (!ActWeapon)
						{
							active_weapon = L"";

						}
						else
						{
							active_weapon = ActWeapon->GetName();
						}
						GUI::Render.RenderString(Vector2{ Entity_x, Entity_y + TextPos_Y }, active_weapon, true, D2D1::ColorF::Black, true);
						GUI::Render.RenderString(Vector2{ Entity_x,Entity_y + TextPos_Y }, active_weapon, true, FLOAT4TOD3DCOLOR(Vars::Color::WeaponColor));
					}
				}

				if (Vars::Visuals::ShowPlayerBox)
				{			
					if (!PlayerWounded && !PlayerSleeping)
					{
						PlayerBoxK(Entity_x, Entity_y, Entity_w, Entity_h, FLOAT4TOD3DCOLOR(Vars::Color::BoxColor));
					}
					if (Vars::Visuals::ShowPlayerHealth)
					{
						Vector2 tempFeetR, tempFeetL, tempHead;

						if (LocalPlayer.WorldToScreen(BP->GetBoneByID(r_foot), tempFeetR) && LocalPlayer.WorldToScreen(BP->GetBoneByID(l_foot), tempFeetL) && LocalPlayer.WorldToScreen(BP->GetBoneByID(jaw) + Vector3(0.f, 0.22f, 0.f), tempHead))
						{
							Vector2 tempFeet = (tempFeetR + tempFeetL) / 2.f;
							float Entity_h = tempHead.y - tempFeet.y;
							float w = Entity_h / 4;
							float Entity_x = tempFeet.x - w;
							float Entity_y = tempFeet.y;
							float Entity_w = Entity_h / 2;
							float health = BP->GetHealth();
							float maxheal = 100.f;
							D2D1::ColorF HpColor = D2D1::ColorF::Green;
							if (health > 75)
								HpColor = D2D1::ColorF::Green;
							else
							{
								if (health < 45)
									HpColor = D2D1::ColorF::Red;
								else
									HpColor = D2D1::ColorF::Orange;
							}

							if ((int)BP->GetHealth() <= 33)
							{
								GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5 ,Entity_h * (health / maxheal) }, HpColor);
							}
							if ((int)BP->GetHealth() >= 34 && (int)BP->GetHealth() <= 66)
							{
								GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5 ,Entity_h * (health / maxheal) }, HpColor);
							}
							if ((int)BP->GetHealth() >= 67)
							{
								GUI::Render.FillRectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5 ,Entity_h * (health / maxheal) }, HpColor);
							}
							GUI::Render.Rectangle(Vector2{ Entity_x + Entity_w - 8.f, Entity_y }, Vector2{ 5, Entity_h }, D2D1::ColorF::Black, 0.5f);
						}
					}
					if (Vars::Visuals::ShowPlayerWeapon)
					{
						const wchar_t* active_weapon;
						float TextPos_Y = 10.f;
						WeaponData* ActWeapon = BP->GetActiveWeapon();
						if (!ActWeapon)
						{
							active_weapon = L"";

						}
						else
						{
							active_weapon = ActWeapon->GetName();
						}
						GUI::Render.RenderString(Vector2{ Entity_x, Entity_y + TextPos_Y }, active_weapon, true, D2D1::ColorF::Black, true);
						GUI::Render.RenderString(Vector2{ Entity_x,Entity_y + TextPos_Y }, active_weapon, true, FLOAT4TOD3DCOLOR(Vars::Color::WeaponColor));
					}					
				}
				else if (Vars::Visuals::BotsESP && BP->GetSteamID() < 1000000000)
				{
					GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h) }, L"Bots", FLOAT4TOD3DCOLOR(Vars::Color::BotColor));
					CurPos += 15;
					GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h + CurPos) }, FC_FORMAT_W(L"%d : HP", (int)BP->GetHealth()), FLOAT4TOD3DCOLOR(Vars::Color::BotColor));
					CurPos += 15;
					GUI::Render.String(Vector2{ (Entity_x + 7), (Entity_y + Entity_h + CurPos) }, FC_FORMAT_W(L"%d.f", (int)Math::Calc3D_Dist(LP->GetBoneByID(head), BP->GetBoneByID(head))), FLOAT4TOD3DCOLOR(Vars::Color::BotColor));
					CurPos += 15;
				}
				if (Vars::Visuals::ShowPlayerActiveSlot)
				{
					if (Vars::Visuals::ShowPlayerActiveSlot && SlotRender(BP, head) <= 150)
						InventoryRender(BP);
				}				
			}
		}
	}
}

__forceinline float Distance3D(const Vector3& Src, const Vector3& Dst)
{
	return sqrtf(pow((Src.x - Dst.x), 2) + pow((Src.y - Dst.y), 2) + pow((Src.z - Dst.z), 2));
}


inline void RadarPlayer(BasePlayer* player)
{
	if (LocalPlayer.BasePlayer && Vars::Radar::Enable && (Vars::Radar::ShowRadarPlayer || Vars::Radar::ShowRadarSleeper))
	{
		if (!player->IsDead() && player->GetHealth() >= 0.2f)
		{
			ImGui::SetNextWindowSize(ImVec2(Vars::Radar::Radar_Size, Vars::Radar::Radar_Size));
			ImGui::Begin("Lancer Loshara", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
			ImVec2 pos = ImGui::GetWindowPos();
			GUI::Render.Сircle({ pos.x + Vars::Radar::Radar_Size / 2, pos.y + Vars::Radar::Radar_Size / 2 }, ConverToRGB(20, 15, 52), Vars::Radar::Radar_Size / 2, 3.f);
			const Vector3 LocalPos = LocalPlayer.BasePlayer->GetPosition();
			const Vector3 PlayerPos = player->GetPosition();
			const float Distance = Distance3D(LocalPos, PlayerPos);
			const float y = LocalPos.x - PlayerPos.x;
			const float x = LocalPos.z - PlayerPos.z;
			Vector3 LocalEulerAngles;
			if (Vars::Radar::EnableDinamicRadar)
			{
				LocalEulerAngles = LocalPlayer.BasePlayer->GetEulerAngles();
			}
			else
			{
				LocalEulerAngles = LocalPlayer.BasePlayer->GetPosition();
			}
			const float num = atan2(y, x) * 57.29578f - 270.f - LocalEulerAngles.y;
			float PointPos_X = Distance * cos(num * 0.0174532924f);
			float PointPos_Y = Distance * sin(num * 0.0174532924f);
			PointPos_X = PointPos_X * (Vars::Radar::Radar_Size / Vars::Radar::Radar_Range) / 2.f;
			PointPos_Y = PointPos_Y * (Vars::Radar::Radar_Size / Vars::Radar::Radar_Range) / 2.f;
			GUI::Render.Сircle({ pos.x + Vars::Radar::Radar_Size / 2, pos.y + Vars::Radar::Radar_Size / 2 }, ConverToRGB(20, 15, 25), 5, 3.f);
			if (!player->HasFlags(16) && Vars::Radar::ShowRadarPlayer)
			{
				if (Distance <= Vars::Radar::Radar_Range)
				{
					GUI::Render.FillCircle({ pos.x + Vars::Radar::Radar_Size / 2.f + PointPos_X - 3.f, pos.y + Vars::Radar::Radar_Size / 2.f + PointPos_Y - 3.f }, D2D1::ColorF::Lime, 3.f);
				}
			}
			else if (player->HasFlags(16) && Vars::Radar::ShowRadarSleeper)
			{
				if (Distance <= Vars::Radar::Radar_Range)
				{
					GUI::Render.FillCircle({ pos.x + Vars::Radar::Radar_Size / 2.f + PointPos_X - 3.f, pos.y + Vars::Radar::Radar_Size / 2.f + PointPos_Y - 3.f }, D2D1::ColorF::Red, 3.f);
				}
			}
			ImGui::End();
		}
	}
}

inline void RenderActiveSlot(BasePlayer* player, float Pos_x, float Pos_Y)
{
	ImGui::SetNextWindowSize(ImVec2(260, 160));
	ImGui::Begin("EEE", NULL, ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);
	ImVec2 pos = ImGui::GetWindowPos();
	const float Height = 195.f;
	const float With = 170.f;
	GUI::Render.FillRoundedRectangle({ pos.x, pos.y }, { With, Height }, D2D1::ColorF::Black, 2);
	GUI::Render.RenderString({ pos.x + (With / 2), pos.y + 5 }, player->GetName(), true, FLOAT4TOD3DCOLOR(Vars::Color::Name));
	float Pos = 0;
	GUI::Render.Line({ pos.x, pos.y + 20 }, { pos.x + With, pos.y + 20 }, FLOAT4TOD3DCOLOR(Vars::Color::Line));
	for (int i = 0; i < 6; i++)
	{
		WeaponData* GetWeaponInfo = player->GetWeaponInfo(i);
		if (GetWeaponInfo)
		{
			const wchar_t* Item = player->GetWeaponInfo(i)->GetName();
			if (wcslen(Item) < 20)
			{
				GUI::Render.RenderString({ pos.x + (With / 2), pos.y + 40 + Pos }, Item, true, FLOAT4TOD3DCOLOR(Vars::Color::weaponactivslot));
			}
		}
		else
		{
			GUI::Render.RenderString({ pos.x + (With / 2), pos.y + 40 + Pos }, L"(--)", true, FLOAT4TOD3DCOLOR(Vars::Color::unactiv));
		}
		Pos += 15;
	}
	float health = player->GetHealth();
	float maxheal = 100.f;
	D2D1::ColorF::Enum colorf;
	if (health > 75 && health < 100)
		colorf = D2D1::ColorF::Green;
	else if (health > 50 && health < 75)
		colorf = D2D1::ColorF::Yellow;
	else if (health > 25 && health < 50)
		colorf = D2D1::ColorF::Orange;
	else if (health > 0 && health < 25)
		colorf = D2D1::ColorF::Red;

	GUI::Render.Rectangle({ pos.x + (With / 2) - 50, pos.y + 40 + Pos }, { 100, 15 }, D2D1::ColorF::LightSlateGray);
	GUI::Render.FillRectangle({ pos.x + (With / 2) + -49, pos.y + 41 + Pos }, { 96 * (health / maxheal), 13 }, colorf);

	ImGui::End();
}


inline void WaterMark(BasePlayer* player, float Pos_x, float Pos_Y)
{
	const float Height =320.f;
	const float With = 40.f;
	GUI::Render.FillRoundedRectangle({ Pos_x, Pos_Y }, { With, Height }, D2D1::ColorF::Black, 2);
}

inline void RenderRadarBackground(float Pos_x, float Pos_Y, float Rad)
{
	if (Vars::Radar::ShowRadarBackground)
     GUI::Render.FillCircle({ Pos_x + Rad / 2, Pos_Y + Rad / 2 }, FLOAT4TOD3DCOLOR(Vars::RadarColor::RadarBackground), Rad / 2);
	 GUI::Render.Сircle({ Pos_x + Rad / 2, Pos_Y + Rad / 2 }, ConverToRGB(20, 15, 52), Rad / 2, 3.f);
	 GUI::Render.Line({ Pos_x + Rad / 2, Pos_Y }, { Pos_x + Rad / 2,Pos_Y + Rad }, D2D1::ColorF::BlueViolet);
	 GUI::Render.Line({ Pos_x, Pos_Y + Rad / 2 }, { Pos_x + Rad, Pos_Y + Rad / 2 }, D2D1::ColorF::BlueViolet);
}

#pragma endregion

