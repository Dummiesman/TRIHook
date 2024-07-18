#pragma once
#include <trihook\trihook.h>
#include <engine\engine_input.h>
#include <engine\engine_time.h>
#include <engine\engine_editortools.h>

class TestHooks
{
private:
    void __cdecl componentList_paint3d();
    static void processCheatCode_Shared();
    static void processCheatCode_EVO();
    static void processCheatCode_EVO2();
public:
    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

