#pragma once
#include <trihook\trihook.h>

class EVOSoundHandler
{
public:
    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};