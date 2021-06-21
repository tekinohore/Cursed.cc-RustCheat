#include "custom_elements.hpp"
c_gui gui;
extern ImFont* iconfont;
extern ImFont* gilroy_big;
extern ImFont* gilroy_mini;
extern ImFont* gilroy;

bool c_gui::tab(const char* icon, const char* label, const char* description, bool selected)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
    const ImVec2 icon_size = ImGui::CalcTextSize(icon, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size = ImGui::CalcItemSize(ImVec2(204, 46), label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, pos + size);
    ImGui::ItemSize(size, style.FramePadding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

    if (hovered || held)
        ImGui::SetMouseCursor(7);

    static float alpha;
    if (selected)
    {
        alpha += 0.05;
        if (alpha >= 1)
            alpha = 1;
    }
    if (pressed && !selected)
        alpha = 0;

    if (selected)
        window->DrawList->AddRectFilled(bb.Min, bb.Max, GetColorU32(ImGuiCol_TabActive, alpha));
    if (hovered)
        window->DrawList->AddRectFilled(bb.Min, bb.Max, GetColorU32(ImGuiCol_TabActive, 0.5));

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(100 / 255.f, 184 / 255.f, 222 / 255.f, 1));
    ImGui::PushFont(iconfont);
    RenderText(ImVec2(bb.Min.x + 10, bb.Min.y + size.y / 2 - icon_size.y / 2), icon);
    ImGui::PopFont();
    ImGui::PopStyleColor();
    RenderText(ImVec2(bb.Min.x + 40, bb.Min.y + size.y / 2 - 13), label);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(75 / 255.f, 79 / 255.f, 85 / 255.f, 1));
    ImGui::PushFont(gilroy_mini);
    RenderText(ImVec2(bb.Min.x + 40, bb.Min.y + size.y / 2 + 2), description);
    ImGui::PopStyleColor();
    ImGui::PopFont();
    return pressed;
}

bool c_gui::sub(const char* label, bool selected)
{
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems)
        return false;

    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);

    ImVec2 pos = window->DC.CursorPos;
    ImVec2 size = ImGui::CalcItemSize(ImVec2(label_size.x, label_size.y), label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

    const ImRect bb(pos, pos + size);
    ImGui::ItemSize(size, style.FramePadding.y);
    if (!ImGui::ItemAdd(bb, id))
        return false;

    bool hovered, held;
    bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, NULL);

    if (hovered || held)
        ImGui::SetMouseCursor(7);

    static float alpha;
    if (selected)
    {
        alpha += 0.05;
        if (alpha >= 1)
            alpha = 1;
    }
    if (pressed && !selected)
        alpha = 0;

    if (selected) {
        window->DrawList->AddRectFilled(ImVec2(bb.Min.x, bb.Max.y + 2), ImVec2(bb.Max.x, bb.Max.y + 4), GetColorU32(ImGuiCol_CheckboxActive, alpha));
        RenderText(bb.Min, label);
    }
    else {
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(75 / 255.f, 79 / 255.f, 85 / 255.f, 1));
        RenderText(bb.Min, label);
        ImGui::PopStyleColor();
    }

    return pressed;

}
