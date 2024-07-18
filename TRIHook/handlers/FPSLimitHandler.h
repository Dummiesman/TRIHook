#pragma once
#include <trihook\trihook.h>

class FPSLimitHandler
{
public:
    static void LimitFPS();
    static void RenderGameScreen(float a1);
    void __cdecl BaseUI_paintAndProcessOneFrame();

    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

