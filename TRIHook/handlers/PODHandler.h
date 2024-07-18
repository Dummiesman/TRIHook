#pragma once
#include <trihook/trihook.h>

class PODHandler
{
public:
#if defined(TRIHOOK_GAME_EVO) || defined(TRIHOOK_GAME_EVO2)
    void __cdecl mountDefaultPodFiles(); // watcom
#else
    void mountDefaultPodFiles();
#endif

    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

