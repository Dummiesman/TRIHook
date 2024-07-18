#include "EVOMiscPatchHandler.h"
#include <engine\engine_platform_windows.h>
#include "CallbacksHandler.h"

void EVOMiscPatchHandler::getVideoMemory(int* pMemory, int* pAGPMemory, int* pFoo)
{
    // Unreliable on modern systems, lets just tell the game we have ~250mb
    *pMemory = 256000000;
    *pAGPMemory = 256000000;
    *pFoo = 0;
}

void EVOMiscPatchHandler::PostInit()
{
    hook_output("EVOMiscPatchHandler::PostInit");
    // Install a wndproc hook
#if defined(TRIHOOK_GAME_EVO)
        addWindowsMessageHook(WndProc);
#endif
}

LRESULT __cdecl EVOMiscPatchHandler::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (message == WM_KILLFOCUS) 
    {
        hook_output("WM_KILLFOCUS");
    }
    else if (message == WM_SETFOCUS)
    {
        hook_output("WM_SETFOCUS");
    }
    return 0; // forward
}

bool EVOMiscPatchHandler::IsGameSupported(GameType gameType)
{
    return gameType == GameType::Game_EVO || gameType == GameType::Game_EVO2 || gameType == GameType::Game_EVO_ED;
}

void EVOMiscPatchHandler::Install(GameType gameType)
{
    // kill getVideoMemory
    if (gameType == GameType::Game_EVO)
    {
        InstallCallback("getVideoMemory",
            &getVideoMemory, {
                cb::call(0x47CA08),
            }
        );
    }
    else if (gameType == GameType::Game_EVO_ED)
    {
        InstallCallback("getVideoMemory",
            &getVideoMemory, {
                cb::call(0x4BC14D),
            }
        );
    }

    CallbacksHandler::RegisterEnginePostInitCallback(PostInit);

    // Kill the swap space warning
    if (gameType == GameType::Game_EVO)
    {
        mem::write<byte, byte, byte, byte, byte, byte>(0x474474, 0XE9, 0xA3, 0x01, 0x00, 0x00, 0x90);
    }
    else if (gameType == GameType::Game_EVO2)
    {
        mem::write<byte, byte, byte, byte, byte, byte>(0x48E3B6, 0XE9, 0x7B, 0x01, 0x00, 0x00, 0x90);
    }
    else if (gameType == GameType::Game_EVO_ED)
    {
        mem::write<byte, byte, byte, byte, byte, byte>(0x4B2F61, 0XE9, 0xA3, 0x01, 0x00, 0x00, 0x90);
    }
}
