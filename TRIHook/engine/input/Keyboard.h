#pragma once
#include <trihook/trihook.h>

class Keyboard
{
private:
#if defined(TRIHOOK_GAME_EVO2) || defined(TRIHOOK_GAME_EVO)
    static hook::Type<char[256]> keyset;
#endif
public:
    static bool checkKeyPressed(byte keycode);
    static void clearKeyPressed(byte keycode);
};

