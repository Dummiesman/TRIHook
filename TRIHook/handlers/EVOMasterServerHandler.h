#pragma once
#include <trihook/trihook.h>

class EVOMasterServerHandler
{
public:
    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

