#pragma once
#include <trihook\trihook.h>
#include <engine\engine_memory.h>
#include <engine\engine_font.h>
#include <engine\engine_math.h>
#include <engine\engine_3d.h>
#include <engine\engine_gfx.h>
#include <engine\engine_editortools.h>

class EVOWidescreenHandler
{
private:
    static void initFonts();
    void __cdecl setWindowHook();
    void __cdecl setSizeHook();
public:
    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

