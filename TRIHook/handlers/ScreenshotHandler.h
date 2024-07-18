#pragma once
#include <trihook\trihook.h>

class ScreenshotHandler
{
public:
    static void PostInit();
    static void screenShot();
public:
    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

