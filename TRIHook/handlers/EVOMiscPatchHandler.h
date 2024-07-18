#pragma once
#include <trihook\trihook.h>
#include <engine\engine_input.h>

class EVOMiscPatchHandler
{
private:
    static void getVideoMemory(int* a1, int* a2, int* a3);
    static void PostInit();
    static LRESULT __cdecl WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
public:
    static bool IsGameSupported(GameType gameType);
    static void Install(GameType gameType);
};

