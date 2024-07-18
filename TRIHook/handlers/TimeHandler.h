#pragma once
#include <trihook/trihook.h>

class TimeHandler
{
public:
    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

