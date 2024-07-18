#pragma once
#include <trihook\trihook.h>
#include <engine\engine_input.h>

class EVOInputPatchHandler
{
public:
    bool __cdecl EVO1_CDIInterface_updateDevices();
    bool __cdecl EVO2_CDIInterface_updateDevices();
    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

