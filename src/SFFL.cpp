#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <Windows.h>
#include <filesystem>
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#include <SFFL.hpp>
#include <utils.hpp>
#include <ui.hpp>
#include <bit7z/bitfileextractor.hpp>
int x, y, w, h, xx, yy;

GLuint bg, button, line, games, kolyah35, invisedivine;
ImVec2 iconSize = ImVec2(84, 60);
ImVec2 lineSize = ImVec2(1280, 1);
ImVec2 gamesSize = ImVec2(59, 23);
ImVec2 invisedivineSize = ImVec2(146, 151);
ImVec2 kolyah35Size = ImVec2(149, 141);
int currentButton = 1, currentGame = 0;
using namespace bit7z;
Bit7zLibrary lib{"7z.dll"};
std::string url = "https://podvalgdsherov.fun/sfflauncher/archive/EscapeFromAmina2.0/EFA20.7z";
std::string path = "Games/EFA20.7z";
bool isDownloaded = 0;
// Невидимые кнопки

BitFileExtractor extractor{lib, BitFormat::SevenZip};

void pushInvisibleStyle() {
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0));
}
void SFFLauncher::init() {

    ImGuiIO &io = ImGui::GetIO();

    ImGuiStyle &style = ImGui::GetStyle();
    style.WindowBorderSize = 0.f;
    style.WindowPadding = {0, 0};
    LoadTextureFromFile("Resources/icon.png", &bg, &x, &y);
    LoadTextureFromFile("Resources/line.png", &line, &w, &h);
    LoadTextureFromFile("Resources/Kolyah35.png", &kolyah35, &w, &h);
    LoadTextureFromFile("Resources/InviseDivine.png", &invisedivine, &w, &h);
}
void SFFLauncher::render() {

    ImGui::Begin("Test Window", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings);
    ImGui::SetWindowSize(windowSize);
    ImGui::SetWindowPos({0, 0});
    ImGui::SetCursorPos({0, 1});
    ImGui::Image((void *)(uintptr_t)bg, iconSize);
    ImGui::SetCursorPos({0, 61});
    ImGui::Image((void *)(uintptr_t)line, lineSize);

    ImGui::PushFont(bold);
    ImGui::SetCursorPos({102, 22});
    pushInvisibleStyle();

    if (ImGui::Button("Игры", {59, 23})) {
        currentButton = 1;
    }

    ImGui::PopStyleColor(3);
    ImGui::PopFont();
    ImGui::PushFont(bold);
    ImGui::SetCursorPos({170, 4});
    pushInvisibleStyle();

    if (ImGui::Button("Архив", {60, 60})) {
        ShellExecute(0, 0, "https://sffnetwork.su/sfflauncher/archive/", 0, 0, SW_SHOW);
    }
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::PushFont(bold);
    ImGui::SetCursorPos({250, 14});
    pushInvisibleStyle();

    if (ImGui::Button("Настройки", {100, 40})) {
        currentButton = 3;
    }

    ImGui::PopStyleColor(3);
    ImGui::PopFont();

    ImGui::PushFont(bold);
    ImGui::SetCursorPos({350, 14});
    pushInvisibleStyle();

    if (ImGui::Button("Credits", {100, 40})) {
        currentButton = 4;
    }

    ImGui::PopStyleColor(3);
    ImGui::PopFont();
    // свитч всех кнопок
    switch (currentButton) {
    case 1:

        std::filesystem::create_directory("Games/");
        if (ImGui::Button("Escape From Amina 2.0")) {
            currentGame = 1;
        }
        // свитч игр
        switch (currentGame)
        {
        case 1:

            if (!std::filesystem::exists("Games/EscapeFromAmina2.0/Escape from Amina.exe")) {
                if (ImGui::Button("Скачать")) {
                    download(url, path);
                    extractor.extract("Games/EFA20.7z", "Games/EscapeFromAmina2.0/");
                    remove("Games/EFA20.7z");
                }
            }
            else {
                if (ImGui::Button("Играть")) {
                    system("\"Games\\EscapeFromAmina2.0\\Escape From Amina.exe\"");
                }
            }
            break;
        }
        // std::filesystem::create_directory("Games/EscapeFromAmina2.0");
        // if(ImGui::Button("test11")) {
        //     system("\"Games\\EscapeFromAmina2.0\\Escape From Amina.exe\"");
        // }
        // if(ImGui::Button("test2") && !std::filesystem::exists("Games/EscapeFromAmina2.0/Escape from Amina.exe")) {
        // download(url,path);
        // extractor.extract("Games/EFA20.7z", "Games/EscapeFromAmina2.0/" );
        // }

        break;

    case 3:
        ImGui::PushFont(bigBold);
        ImGui::Text("Выбор темы: ");
        pushInvisibleStyle();
        if (ImGui::Button("Тёмная")) {
            ImGui::StyleColorsDark();
        }
        if (ImGui::Button("Светлая")) {

            ImGui::StyleColorsLight();
        }
        ImGui::PopStyleColor(3);
        ImGui::PopFont();
        break;

    case 4:
        ImGui::SetCursorPos({0, 91});
        ImGui::Image((void *)(uintptr_t)invisedivine, invisedivineSize);
        ImGui::SetCursorPos({0, 261});
        ImGui::Image((void *)(uintptr_t)kolyah35, kolyah35Size);
        ImGui::PushFont(bigBold);
        ImGui::SetCursorPos({161, 139});
        ImGui::Text(" InviseDivine - разработка лаунчера и \n дизайна для него");
        ImGui::SetCursorPos({161, 325});
        ImGui::Text("Kolyah35 - помощь в создании лаунчера");
        ImGui::SetCursorPos({891, 106});
        ImGui::Text(" Отдельное спасибо:\n CITRIM \n Jaan \n mixvy (Амина) \n FullHarmony(_Sycorax_) \n njuyse \n Karbafosus \n Festr \n Nixonit \n Весь SFF");
        ImGui::PopFont();
        break;
    };
    ImGui::End();
};