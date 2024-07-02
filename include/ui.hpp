#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace UI {
    bool button(const char* label, ImVec2 pos, ImVec2 size, bool centered);
};