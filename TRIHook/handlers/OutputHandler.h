#pragma once
#include <trihook/trihook.h>

class OutputHandler
{
public:
    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

