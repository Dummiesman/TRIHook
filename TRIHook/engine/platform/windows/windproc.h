#pragma once
#include <trihook/trihook.h>

#if defined(TRIHOOK_GAME_EVO) || defined(TRIHOOK_GAME_EVO2)
static void addWindowsMessageHook(LRESULT (__cdecl*fn)(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam))
{
#if defined(TRIHOOK_GAME_EVO2)
    using func = hook::StaticThunk<0x60B210>;
#else
    using func = hook::StaticThunk<0x59BEB0>;
#endif
    func::Call<void>(fn);
}
#endif