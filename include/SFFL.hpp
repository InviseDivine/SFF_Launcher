#pragma once
#include "font/Inter-Regular.h"
#include "font/Inter-Bold.h"
inline ImVec2 windowSize = ImVec2(1280, 720);
inline ImFont* regular;
inline ImFont* bold;
inline ImFont* bigBold;
class SFFLauncher{
public:
    void render();
    void init();
};