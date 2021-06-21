
#define get_keycode_name(vk, name)\
switch (vk) {\
case VK_CONTROL: name = "control"; break;\
case VK_SHIFT: name = "shift"; break;\
case VK_LSHIFT: name = "shift"; break;\
case VK_MENU: name = "alt"; break;\
case VK_TAB: name = "tab"; break;\
case VK_LBUTTON: name = "mouse 1"; break;\
case VK_RBUTTON: name = "mouse 2"; break;\
case VK_MBUTTON: name = "mouse 3"; break;\
case VK_XBUTTON1: name = "mouse 4"; break;\
case VK_XBUTTON2: name = "mouse 5"; break;\
case VK_PRIOR: name = "page up"; break;\
case VK_NEXT: name = "page down"; break;\
case VK_END: name = "end"; break;\
case VK_HOME: name = "home"; break;\
case VK_LEFT: name = "left arrow"; break;\
case VK_UP: name = "up arrow"; break;\
case VK_RIGHT: name = "right arrow"; break;\
case VK_DOWN: name = "down arrow"; break;\
case VK_INSERT: name = "insert"; break;\
case VK_DELETE: name = "delete"; break;\
case 'A': name = "a"; break;\
case 'B': name = "b"; break;\
case 'C': name = "c"; break;\
case 'D': name = "d"; break;\
case 'E': name = "e"; break;\
case 'F': name = "f"; break;\
case 'G': name = "g"; break;\
case 'H': name = "h"; break;\
case 'I': name = "i"; break;\
case 'J': name = "j"; break;\
case 'K': name = "k"; break;\
case 'L': name = "l"; break;\
case 'M': name = "m"; break;\
case 'N': name = "n"; break;\
case 'O': name = "o"; break;\
case 'P': name = "p"; break;\
case 'Q': name = "q"; break;\
case 'R': name = "r"; break;\
case 'S': name = "s"; break;\
case 'T': name = "t"; break;\
case 'U': name = "u"; break;\
case 'V': name = "v"; break;\
case 'W': name = "w"; break;\
case 'X': name = "x"; break;\
case 'Y': name = "y"; break;\
case 'Z': name = "z"; break;\
case VK_NUMPAD0: name = "numpad 0"; break;\
case VK_NUMPAD1: name = "numpad 1"; break;\
case VK_NUMPAD2: name = "numpad 2"; break;\
case VK_NUMPAD3: name = "numpad 3"; break;\
case VK_NUMPAD4: name = "numpad 4"; break;\
case VK_NUMPAD5: name = "numpad 5"; break;\
case VK_NUMPAD6: name = "numpad 6"; break;\
case VK_NUMPAD7: name = "numpad 7"; break;\
case VK_NUMPAD8: name = "numpad 8"; break;\
case VK_NUMPAD9: name = "numpad 9"; break;\
case VK_F1: name = "F1"; break;\
case VK_F2: name = "F2"; break;\
case VK_F3: name = "F3"; break;\
case VK_F4: name = "F4"; break;\
case VK_F5: name = "F5"; break;\
case VK_F6: name = "F6"; break;\
case VK_F7: name = "F7"; break;\
case VK_F8: name = "F8"; break;\
case VK_F9: name = "F9"; break;\
case VK_F10: name = "F10"; break;\
case VK_F11: name = "F11"; break;\
case VK_F12: name = "F12"; break;\
default: name = "unknown";\
}



bool Tab(const char* icon, const char* label, const char* desc, const ImVec2& size_arg, const bool selected)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	static float sizeplus = 0.f;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;

	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

	if (selected)
		window->DrawList->AddRectFilled(bb.Min, bb.Max, ImColor(25, 30, 35));

	//	ImGui::PushFont(big);
	window->DrawList->AddText(ImVec2(bb.Min.x + 35, bb.Min.y + 13), ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), label);
	//	ImGui::PopFont();

	window->DrawList->AddText(ImVec2(bb.Min.x + 35, bb.Min.y + 26), ImColor(100 / 255.f, 100 / 255.f, 100 / 255.f, 255.f / 255.f), desc);

	//	ImGui::PushFont(icons);
	window->DrawList->AddText(ImVec2(bb.Min.x + 5, bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(icon).y / 2), ImColor(84 / 255.f, 182 / 255.f, 225 / 255.f, 255.f / 255.f), icon);
	//	ImGui::PopFont();

	return pressed;
}

void RenderCheckMar1k(ImVec2 pos, ImU32 col, float sz)
{
	ImGuiContext& g = *GImGui;
	ImGuiWindow* window = g.CurrentWindow;

	float thickness = ImMax(sz / 5.0f, 1.0f);
	sz -= thickness * 0.5f;
	pos = ImVec2(pos.x + thickness * 0.25f, pos.y + thickness * 0.25f);

	float third = sz / 3.0f;
	float bx = pos.x + third;
	float by = pos.y + sz - third * 0.5f;
	window->DrawList->PathLineTo(ImVec2(bx - third, by - third));
	window->DrawList->PathLineTo(ImVec2(bx, by));
	window->DrawList->PathLineTo(ImVec2(bx + third * 2, by - third * 2));
	window->DrawList->PathStroke(col, false, thickness);
}

bool CheckboxD(const char* label, bool* v)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	const float square_sz = ImGui::GetFrameHeight();
	const ImVec2 pos = window->DC.CursorPos;
	const ImRect total_bb(pos, ImVec2(pos.x + square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), pos.y + label_size.y + style.FramePadding.y * 2.0f));
	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(total_bb, id, &hovered, &held);
	if (pressed)
	{
		*v = !(*v);
		ImGui::MarkItemEdited(id);
	}

	const ImRect check_bb(pos, ImVec2(pos.x + square_sz, pos.y + square_sz));

	float t = *v ? 1.0f : 0.0f;

	float ANIM_SPEED = 0.05f;
	if (g.LastActiveIdTimer == g.CurrentWindow->GetID(label))// && g.LastActiveIdTimer < ANIM_SPEED)
	{
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = *v ? (t_anim) : (1.0f - t_anim);
	}

	ImU32 col_bg = ImGui::GetColorU32(ImVec4(120 / 255.f, 120 / 255.f, 120 / 255.f, 120 / 255.f));
	ImU32 col_bg2;
	ImU32 col_bg3;

	col_bg2 = ImGui::GetColorU32(ImLerp(ImVec4(190 / 255.f, 190 / 255.f, 190 / 255.f, 0 / 255.f), ImVec4(5 / 255.f, 193 / 255.f, 245 / 255.f, 255.f / 255.f), t));
	col_bg3 = ImGui::GetColorU32(ImLerp(ImVec4(190 / 255.f, 190 / 255.f, 190 / 255.f, 0 / 255.f), ImVec4(255, 255, 255, 255), t));

	window->DrawList->AddRect(check_bb.Min, check_bb.Max, col_bg, 4.f, 15, 2.f);
	window->DrawList->AddRectFilled(check_bb.Min, check_bb.Max, col_bg2, 4.f);

	if (*v)
	{
		RenderCheckMar1k(ImVec2{ check_bb.Min.x + 4,check_bb.Min.y + 4 }, col_bg3, square_sz - 8);
	}

	if (label_size.x > 0.0f)
		ImGui::RenderText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y), label);

	return pressed;
}

bool SubTab(const char* label, const ImVec2& size_arg, const bool selected)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	static float sizeplus = 0.f;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

	ImVec2 pos = window->DC.CursorPos;

	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, ImVec2(pos.x + size.x, pos.y + size.y));
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, 0);

	if (selected)
		window->DrawList->AddRectFilled({ bb.Min.x,bb.Min.y }, { bb.Max.x,bb.Max.y }, ImColor(30, 35, 40, 200));

	if (selected)
		window->DrawList->AddRectFilled({ bb.Max.x,bb.Max.y }, { bb.Max.x - 3,bb.Min.y }, ImColor(84 / 255.f, 182 / 255.f, 225 / 255.f, 255.f / 255.f));

	//	ImGui::PushFont(big);
	window->DrawList->AddText(ImVec2(bb.Min.x + 5, bb.Min.y + size_arg.y / 2 - ImGui::CalcTextSize(label).y / 2), ImColor(255 / 255.f, 255 / 255.f, 255 / 255.f, 255.f / 255.f), label);
	//	ImGui::PopFont();


	return pressed;
}

static bool IsKeyPressedMap(ImGuiKey key, bool repeat)
{
	const int key_index = GImGui->IO.KeyMap[key];
	return (key_index >= 0) ? ImGui::IsKeyPressed(key_index, repeat) : false;
}

bool Hotkey(const char* label, int* k, const ImVec2& size_arg)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 2.0f);
	const ImRect frame_bb(window->DC.CursorPos + ImVec2(label_size.x + style.ItemInnerSpacing.x, 0.0f), window->DC.CursorPos + size);
	const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id);
	const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);
	const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

	const bool hovered = ImGui::ItemHoverable(frame_bb, id);

	if (hovered) {
		ImGui::SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool user_clicked = hovered && io.MouseClicked[0];

	if (focus_requested || user_clicked) {
		if (g.ActiveId != id) {
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			*k = 0;
		}
		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}
	else if (io.MouseClicked[0]) {
		// Release focus when we click outside
		if (g.ActiveId == id)
			ImGui::ClearActiveID();
	}

	bool value_changed = false;
	int key = *k;

	if (g.ActiveId == id) {
		for (auto i = 0; i <= 6; i++) {
			if (io.MouseDown[i] || GetAsyncKeyState(VK_XBUTTON1) || GetAsyncKeyState(VK_XBUTTON2)) {
				switch (i) {
				case 0:
					key = VK_LBUTTON;
					break;
				case 1:
					key = VK_RBUTTON;
					break;
				case 2:
					key = VK_MBUTTON;
					break;
				}
				if (GetAsyncKeyState(VK_XBUTTON2))
					key = VK_XBUTTON2;
				if (GetAsyncKeyState(VK_XBUTTON1))
					key = VK_XBUTTON1;

				value_changed = true;
				ImGui::ClearActiveID();
			}
		}
		if (!value_changed) {
			for (auto i = VK_BACK; i <= VK_RMENU; i++) {
				if (io.KeysDown[i]) {
					key = i;
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
		}

		if (IsKeyPressedMap(ImGuiKey_Escape, false)) {
			*k = 0;
			ImGui::ClearActiveID();
		}
		else {
			*k = key;
		}
	}

	// Render
	// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

	const char* buf_display = "None";

	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImVec4(0.20f, 0.25f, 0.30f, 1.0f)), true, style.FrameRounding);


	if (*k != 0 && g.ActiveId != id) {
		const char* key_name;
		get_keycode_name(*k, buf_display);
	}
	else if (g.ActiveId == id) {
		buf_display = "Press";
		std::this_thread::sleep_for(std::chrono::milliseconds(80));
	}

	const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = frame_bb.Min + style.FramePadding;
	ImGui::RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);
	//RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, GetColorU32(ImGuiCol_Text), style.ButtonTextAlign, &clip_rect);
	//draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos, GetColorU32(ImGuiCol_Text), buf_display, NULL, 0.0f, &clip_rect);

	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(total_bb.Min.x, frame_bb.Min.y + style.FramePadding.y), label);

	return value_changed;
}