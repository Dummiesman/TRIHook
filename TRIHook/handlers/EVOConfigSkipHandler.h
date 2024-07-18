#pragma once
#include <trihook\trihook.h>

class EVOConfigSkipHandler
{
private:
    static void goToMenu();
public:
    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

