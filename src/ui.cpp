#include "ui.hpp"
namespace UI {
    bool button(const char* label, ImVec2 pos, ImVec2 size, bool centered){
        auto cursorPos = ImGui::GetCursorPos();
        ImGui::SetCursorPos((centered) ? ImVec2(pos.x - (size.x / 2), pos.y - (size.y / 2)) : pos);
        auto ret = ImGui::Button(label, size);
        ImGui::SetCursorPos(cursorPos);
        return ret;
    }
};

