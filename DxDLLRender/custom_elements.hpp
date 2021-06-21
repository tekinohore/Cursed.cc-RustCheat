#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS
#include <windows.h>
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

using namespace ImGui;

class c_gui
{
public:
    bool tab(const char* icon, const char* label, const char* description, bool selected);
    bool sub(const char* label, bool selected);
};

extern c_gui gui;
